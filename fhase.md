
## ゴール

最終形はこんな感じです。

```text
Windowsデスクトップ

  🐟        🐠
        🐡

- 背景は透明
- 魚が常に泳ぐ
- デスクトップ操作の邪魔をしない
- 複数匹存在
- 画面端で方向転換
- 魚ごとに速度が違う
- アニメーションする
- マウスや餌に反応する
- タスクトレイから終了・設定できる
```

技術構成は最初は、

```text
C++
Win32 API
GDI+ または Direct2D
CMake
PNG画像
```

で進めるのが良いです。

---

# 全体ロードマップ

## Phase 0：開発環境を作る

まず「C++アプリとして普通にビルドできる状態」を作ります。

やることは、

* CMake導入
* `src/` と `assets/` の構成
* Windows用C++プロジェクト作成
* Git管理
* Hello Worldをビルド

最初はこの程度です。

```text
desktop-fish/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── assets/
```

### ここで学ぶC++

* コンパイル
* リンク
* CMake
* プロジェクト構成
* ヘッダとcppの分離

ここは**自分でやる部分多め**でいいです。

---

# Phase 1：Windowsにウィンドウを出す

まず魚は出しません。

```text
+----------------------+
|                      |
|      Hello Fish      |
|                      |
+----------------------+
```

これを出します。

Win32 APIを使って、

```cpp
WinMain
RegisterClass
CreateWindow
WndProc
ShowWindow
```

あたりを触ります。

### 目標

「Windowsアプリってこう動くんだ」

を理解することです。

### Codexに任せてもいい部分

Win32の定型コードはかなり冗長なので、

* `WNDCLASS`
* ウィンドウ生成
* メッセージループ

あたりはCodexに土台を作らせてもいいです。

ただし、

> コードを読んで何をしているか説明できる

状態にはします。

---

# Phase 2：四角を動かす

ここから一気に面白くなります。

まず魚ではなく、

```text
+---------------------------+

      ■ → → → →

+---------------------------+
```

四角を動かします。

例えば、

```cpp
struct Object {
    float x;
    float y;
    float vx;
    float vy;
};
```

として、

```cpp
x += vx * dt;
```

します。

### ここで学ぶこと

かなり重要です。

* struct / class
* 状態
* update
* 描画
* 座標
* 速度
* `delta time`
* ゲームループ

ここは**できる限り自分で書く**のがおすすめです。

---

# Phase 3：Fishクラスを作る

ここで初めて魚という概念を作ります。

例えば、

```text
Fish

position
velocity
size
direction

update()
draw()
```

という設計にします。

イメージは、

```cpp
class Fish {
private:
    float x_;
    float y_;
    float speed_;

public:
    void update(float dt);
    void draw();
};
```

です。

### ここはC++学習として超重要

このPhaseでは、

* `private`
* `public`
* コンストラクタ
* const
* 参照
* メンバ関数
* カプセル化
* ライフタイム

をちゃんとやります。

ここは**Codexに実装させすぎない**方がいいです。

---

# Phase 4：魚を複数匹にする

次に、

```text
🐟

          🐠

    🐡
```

にします。

内部的には、

```cpp
std::vector<Fish>
```

です。

### 学ぶこと

* `std::vector`
* オブジェクトのコピー
* move
* range-based for
* 参照
* コンテナ

この辺から、今まで勉強してきたC++がかなり生きてきます。

---

# Phase 5：魚画像を描画する

四角卒業です。

PNGを読み込んで、

```text
■
↓
🐟
```

にします。

ここでGDI+かDirect2Dを使います。

最初はGDI+でもいいです。

### 学ぶこと

* 外部リソース
* ファイル読み込み
* RAII
* リソース解放
* ハンドル
* ポインタ
* 所有権

ここは**かなり実務C++っぽい**です。

---

# Phase 6：透明ウィンドウ化

ここで一気に完成形っぽくなります。

```text
通常ウィンドウ

+----------------------+
| 🐟                   |
|                      |
+----------------------+

↓

透明化

Desktop上を🐟が泳ぐ
```

ここでは、

```text
Layered Window
Transparent Window
Topmost Window
```

あたりを扱います。

さらに、

```text
魚のウィンドウ
↓
マウスクリック
↓
背後のChromeやVSCodeに届く
```

ようにします。

### 学ぶこと

C++というより、

**OS・ウィンドウシステム**

の勉強です。

ここはCodexにかなり補助してもらっていいです。

---

# Phase 7：魚らしい動きにする

ここから「アプリ」から「生き物」になります。

例えば、

```text
一定時間直進
↓
ランダムに方向転換
↓
少し上下する
↓
また泳ぐ
```

とします。

さらに、

```text
FishBehavior
```

を作ってもいいです。

### 学ぶこと

* 状態管理
* 乱数
* 時間
* enum
* state machine

例えば、

```cpp
enum class FishState {
    Swimming,
    Turning,
    Eating
};
```

とかです。

これはかなり良いC++題材です。

---

# Phase 8：魚アニメーション

PNG1枚ではなく、

```text
fish_0.png
fish_1.png
fish_2.png
fish_3.png
```

を切り替えます。

```text
🐟
🐟
🐟
🐟
```

尾びれが動く感じです。

### 学ぶこと

* sprite animation
* vector
* timer
* animation state
* リソース管理

ここまで来るとかなりゲームプログラミング寄りです。

---

# Phase 9：ユーザー操作

ここから遊びを入れます。

例えばクリックで、

```text
     🍞
      ↓

🐟 → 🍞 ← 🐠
```

餌を出す。

または、

```text
マウスカーソル
        ↓

🐟 ← 逃げる
```

など。

### 学ぶこと

* マウス座標
* イベント処理
* 距離計算
* ベクトル
* インタラクション

ここは楽しいです。

---

# Phase 10：設定・タスクトレイ

実用アプリにします。

例えば、

```text
🐟 Fish App

右クリック
├─ 魚を追加
├─ 魚を減らす
├─ 速度
├─ 常に最前面
└─ 終了
```

### 学ぶこと

* Windowsイベント
* メニュー
* 設定管理
* ファイルI/O
* JSON

設定ファイルも、

```json
{
  "fishCount": 5,
  "speed": 1.2
}
```

みたいにできます。

---

# Phase 11：設計を整理する

ここで一度リファクタリングします。

最終的には例えば、

```text
App
├── FishManager
│   └── vector<Fish>
│
├── Renderer
│   └── ImageManager
│
├── InputManager
│
└── Settings
```

みたいな構造を目指します。

ディレクトリも、

```text
desktop-fish/
├── CMakeLists.txt
├── assets/
│   ├── fish1.png
│   └── fish2.png
│
├── src/
│   ├── main.cpp
│   ├── App.cpp
│   ├── App.hpp
│   ├── Fish.cpp
│   ├── Fish.hpp
│   ├── Renderer.cpp
│   ├── Renderer.hpp
│   ├── FishManager.cpp
│   └── FishManager.hpp
│
└── README.md
```

くらいになります。

---

# C++学習としての重点

今回、特に身につけたい順番はこれです。

```text
① class / struct
↓
② 参照・const
↓
③ vector
↓
④ オブジェクトの寿命
↓
⑤ RAII
↓
⑥ smart pointer
↓
⑦ copy / move
↓
⑧ 設計
↓
⑨ Windows API
↓
⑩ 描画
```

特に今回は、

**ポインタやRAIIを「本当に必要だから使う」**

という経験ができるのが大きいです。

教科書で、

```cpp
std::unique_ptr<T>
```

を見るのと、

```text
画像リソースを誰が所有する？

Renderer？
Fish？
ImageManager？

↓

unique_ptr / shared_ptrどうする？
```

と悩むのでは、理解度が全然違います。

---

# Codexとの役割分担

このプロジェクトでは、

**自分で書く**

```text
Fish
FishManager
update処理
状態管理
vector
クラス設計
```

**Codexを使う**

```text
Win32の定型処理
CMakeトラブル
GDI+/Direct2DのAPI
ビルドエラー調査
レビュー
```

くらいがちょうど良いです。

Codexに、

> 「全部実装して」

はしない。

代わりに、

> 「このエラーの原因だけ調べて」

> 「Win32部分だけ実装して」

> 「この設計に問題があるかレビューして」

という使い方にします。

---

## 最初のマイルストーン

まず目標はかなり小さくします。

**Milestone 1**

```text
Windowsウィンドウを出す
↓
四角を1個描く
↓
四角が左から右へ移動する
↓
端まで行ったら反転する
```

これができれば、魚アプリの根幹はすでにできています。

なので、次は **Phase 0から実際に開始** するのがよいです。
最初に「VSCode + CMake + C++でWindowsアプリを作る環境」を整えて、`main.cpp` 1個から始めましょう。
