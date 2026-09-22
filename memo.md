1. Window はウィンドウを管理するクラス
2. HWND はWindows上のウィンドウを表す識別子
3. CreateWindowEx でウィンドウを作る
4. WindowProc がWindowsからイベントを受ける
5. run() のメッセージループがイベントを回している

## 将来的にやること
- aquariumクラスを作って、windowとFishの間に

## ランダム性の設計

```
std::mt19937 : 乱数を生成するエンジン
std::random_device: 乱数エンジンの初期化に使用
std::uniform_real_distribution: 一様分布(実数)
std::uniform_int_distribution: 一様分布(整数)
std::bernoulli_distribution: ベルヌーイ分布 ⇒ true or false
```

1. 泳ぐ速度(0.0f ~ 5.0f)
2. 泳ぐ向き(とりあえず左右、最終的には360°)
3. 次更新までの時間（0.5s ~ 5.0s）

