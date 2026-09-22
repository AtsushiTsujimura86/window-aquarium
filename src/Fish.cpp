#include "Fish.hpp"
#include <random>


Fish::Fish(float x, float y, float vx, float turnInterval)
    :x_(x), y_(y), vx_(vx), turnInterval_(turnInterval){
        
        // //ランダムな速度を0.0fから5.0fの範囲で生成する
        // std::uniform_real_distribution<float> dist1(0.0f, 5.0f);
        // vx_ = dist1(gen);
        // // ランダムな進行方向を生成する
        // std::bernoulli_distribution dist2(0.5);
        // if(dist2(gen)) vx_ = -vx_;
        // // ランダムな次回更新までの時間を生成する
        // std::uniform_real_distribution<float> dist3(0.5f, 5.0f);
        // turnInterval_ = dist3(gen);
    }

void Fish::update(float clientWidth, float deltaTime, std::mt19937& randomEngine) {
    // 経過時間を更新する
    elapsedTime_ += deltaTime;
    // 一定時間ごとに方向転換する
    if(elapsedTime_ >= turnInterval_){
        // 方向転換する
        vx_ = -vx_;
        elapsedTime_ = 0.0f; // 経過時間をリセットする
    }
    x_ += vx_;
    // ★右端または左端まで来たら進行方向を反転する
    if(x_ + width_ >= clientWidth || x_ <= 0){
        vx_ = -vx_;
    }
}

float Fish::get_x() const{
    return x_;
}
float Fish::get_y() const{
    return y_;
}
float Fish::get_width() const{
    return width_;
}
float Fish::get_height() const{
    return height_;
}
