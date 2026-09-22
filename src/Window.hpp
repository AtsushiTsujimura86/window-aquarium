#pragma once

#include <windows.h>
#include "Fish.hpp"
#include <vector>
#include <chrono>
#include <random>

// ウィンドウの生成、メッセージ処理、魚の描画をまとめて管理するクラス。
class Window{
    public:
        // WinMain から渡されたアプリケーションのインスタンスを保持する。
        Window(HINSTANCE hInstance);

        // ウィンドウクラスを登録し、画面に表示するウィンドウを生成する。
        bool create();

        // 指定された表示状態でウィンドウを表示する。
        void show(int nCmdShow);

        // OS のメッセージを処理し、終了までイベントループを実行する。
        int run();

    private:
        // Win32 のメッセージを Window オブジェクトの処理へ振り分ける。
        static LRESULT CALLBACK WindowProc(
            HWND hwnd,
            UINT uMsg,
            WPARAM wParam,
            LPARAM lParam
        );

        void update();
        void paint();

        HINSTANCE hInstance_;
        HWND hwnd_ = nullptr;

        // ランダムエンジン
        std::mt19937 randomEngine_;

        // Fishオブジェクトを5つ生成
        // Fish fish_{10.0f, 100.0f, 3.0f};
        // Fish fish2_{20.0f, 150.0f, 3.0f};
        // Fish fish3_{30.0f, 200.0f, 3.0f};
        // Fish fish4_{40.0f, 250.0f, 3.0f};
        // Fish fish5_{50.0f, 300.0f, 3.0f};
        // Fishオブジェクトのポインタを格納するベクター
        std::vector<Fish*> fishes_{};
        // 最後の更新時刻
        std::chrono::steady_clock::time_point lastUpdate_ = std::chrono::steady_clock::now();


};