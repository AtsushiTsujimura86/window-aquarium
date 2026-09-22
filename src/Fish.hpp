#pragma once
#include <random>

class Fish{
public:
    Fish(float x, float y, float vx, float turnInterval);

    void update(float clientWidth, float deltaTime, std::mt19937& randomEngine);

    float get_x() const;
    float get_y() const;
    float get_width() const;
    float get_height() const;

    // ランダムな速度を生成する関数
    float get_random_xv_();
    // ランダムな進行方向を生成する関数
    bool get_random_direction_();
    // ランダムな次回更新までの時間を生成する関数
    float get_random_turnInterval_();


private:
    // 魚の位置と速度
    float x_;
    float y_;
    float vx_;
    // 魚のサイズ
    float width_ = 50.0f;
    float height_ = 50.0f;
    //経過時間
    float elapsedTime_ = 0.0f;
    float turnInterval_ = 2.0f; // 2秒ごとに方向転換
};