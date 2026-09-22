#include <windows.h>

#include "Window.hpp"

// Windows アプリケーションのエントリーポイント。
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow
) {
    // アプリケーションのインスタンスを使って Window を初期化する。
    Window window(hInstance);

    // ウィンドウの生成に失敗した場合は、メッセージループを開始しない。
    if (!window.create()) {
        return 1;
    }

    // OS から渡された表示状態でウィンドウを表示する。
    window.show(nCmdShow);

    // ウィンドウが閉じられるまでメッセージループを実行する。
    return window.run();
}