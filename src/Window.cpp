#include "Window.hpp"
#include <random>

// コンストラクタ
Window::Window(HINSTANCE hInstance)
    : hInstance_(hInstance),
    randomEngine_(std::mt19937(std::random_device{}())) {
    // ランダムな数（1-5）だけFishオブジェクトを生成、fishes_に追加する(aquariumに移行予定)
    std::uniform_int_distribution<int> distFishNum(1, 5);
    int numFishes = distFishNum(randomEngine_); //魚の数
    std::uniform_real_distribution<float> distX(0.0f, 800.0f); //魚の初期位置x
    std::uniform_real_distribution<float> distY(0.0f, 600.0f); //魚の初期位置y
    std::uniform_real_distribution<float> distV(0.0f, 5.0f); //魚の初期速度
    std::uniform_real_distribution<float> distTurn(0.5f, 5.0f); //魚の初期方向転換間隔
    for(int i=0; i<numFishes; ++i){
        float x = distX(randomEngine_);
        float y = distY(randomEngine_);
        float vx = distV(randomEngine_);
        float turnInterval = distTurn(randomEngine_);
        fishes_.emplace_back(new Fish(x, y, vx, turnInterval));
    }
    
}

bool Window::create() {
    // ウィンドウクラスを登録してから、そのクラスのウィンドウを生成する。
    const char CLASS_NAME[] = "WindowAquariumClass";

    WNDCLASS wc{};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance_;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // ウィンドウの背景色を設定する。
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);

    RegisterClass(&wc);

    hwnd_ = CreateWindowEx(
        0,
        CLASS_NAME,
        "Window Aquarium",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        nullptr,
        nullptr,
        hInstance_,
        this
    );
    if (hwnd_ == nullptr) {
        return false;
    }

    // 約 60 FPS で WM_TIMER を発生させ、魚の位置を更新する。
    SetTimer(hwnd_, 1, 16, nullptr);

    return true;
}

void Window::show(int nCmdShow) {
    ShowWindow(hwnd_, nCmdShow);
}

int Window::run() {
    MSG msg{};

    // WM_QUIT が投稿されるまで、OS からのイベントを順番に処理する。
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

void Window::update() {
    RECT clientRect{};
    GetClientRect(hwnd_, &clientRect);

    constexpr float width = 50.0f;
    const auto now = std::chrono::steady_clock::now();
    //前回の更新から経過した時間
    const float deltaTime = std::chrono::duration<float>(now - lastUpdate_).count();
    lastUpdate_ = now;

    //Fishオブジェクトの状態を更新する
    for(Fish* fish: fishes_){
        fish->update(static_cast<float>(clientRect.right), deltaTime, randomEngine_);
    }

    // 次の WM_PAINT で更新後の位置を描画させる。
    InvalidateRect(hwnd_, nullptr, TRUE);
}

void Window::paint() {
    PAINTSTRUCT ps{};
    HDC hdc = BeginPaint(hwnd_, &ps);

    // 現在位置に魚を表す四角形を描画する。
    // Fishから座標とサイズを取得して描画する
    for(Fish* fish: fishes_){
        Rectangle(
            hdc,
            static_cast<int>(fish->get_x()),
            static_cast<int>(fish->get_y()),
            static_cast<int>(fish->get_x() + fish->get_width()),
            static_cast<int>(fish->get_y() + fish->get_height())
        );
    }

    EndPaint(hwnd_, &ps);
}

LRESULT CALLBACK Window::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    Window* window = nullptr;

    if (uMsg == WM_NCCREATE) {
        // CreateWindowEx に渡した this ポインターをウィンドウへ関連付ける。
        auto* createStruct =
            reinterpret_cast<CREATESTRUCT*>(lParam);

        window =
            static_cast<Window*>(createStruct->lpCreateParams);

        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(window)
        );

        window->hwnd_ = hwnd;
    } else {
        window = reinterpret_cast<Window*>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA)
        );
    }

    if (window != nullptr) {
        switch (uMsg) {
        case WM_TIMER:
            // タイマーごとに位置を更新し、再描画を要求する。
            window->update();
            return 0;

        case WM_PAINT:
            // OS が要求した描画範囲を処理する。
            window->paint();
            return 0;

        case WM_DESTROY:
            // ウィンドウ終了時にタイマーを停止し、メッセージループを終了する。
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}