#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

struct Vector2 {
    float x, y;

    // 引数付きコンストラクタ
    Vector2(float x = 0.0f, float y = 0.0f);

    // ベクトルの長さを計算
    float magnitude() const;

    // ベクトルを正規化（長さを1にする）
    Vector2 normalized() const;

    // ベクトルの加算
    Vector2 operator+(const Vector2& other) const;

    // ベクトルの減算
    Vector2 operator-(const Vector2& other) const;

    // スカラーとの乗算（掛け算）
    Vector2 operator*(float scalar) const;

    // スカラーとの除算（割り算）
    Vector2 operator/(float scalar) const;

    //
    void CenterPositionSync(Vector2 centerpos, int size);

    // 0で初期化する静的な定数
    static const Vector2 zero;   
};

struct Boxcollider {
    float left;
    float top;
    float right;
    float bottom;

    Boxcollider() : left(0), top(0), right(0), bottom(0) {}
    Boxcollider(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
    Boxcollider(float i) : left(i), top(i), right(i), bottom(i) {}

    // 矩形同士の衝突判定
    bool BoxCollision(const Boxcollider& other) const;

    // 指定された点がこの矩形の中にあるかを判定
    bool PosCollision(Vector2 pos) const;

    // 中心座標から頂点の位置をセットする
    void CenterPositionSync(Vector2 centerpos, int size);

  // 0で初期化する静的な定数
    static const Boxcollider zero;
};


struct StringText {
    std::string str;  // 内部で std::string で文字列を管理

    // コンストラクタで初期化
    //StringText(const std::string& input = "") : str(input) {}
    StringText() {}

    // std::string を char[] に変換して外部に渡す関数
    const char* toCharArray() const;

    // テキストを動的に更新する関数
    void updateText(const std::string& newText);

    // テキストに追記する関数
    void appendText(const std::string& additionalText);

    // テキストの内容を表示（デバッグ用）
    void printString() const;

    void WriteTextprintf() {

    }
};


#endif // GEOMETRY_H
