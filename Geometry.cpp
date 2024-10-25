#include "Geometry.h"

//どこでも0初期化できるように定義しておく
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Boxcollider Boxcollider::zero = Boxcollider(0.0f, 0.0f, 0.0f, 0.0f);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    /*Vector2(座標をfloat型 x, yで管理するクラス)*/

// 引数付きコンストラクタ
 Vector2::Vector2(float x, float y) : x(x), y(y) {}

//================================================================
// ベクトルの長さを計算
//================================================================
 float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

//================================================================
// ベクトルを正規化（長さを1にする）
//================================================================
 Vector2 Vector2::normalized() const {
    float mag = magnitude();
    if (mag == 0) {
        return Vector2(0, 0);  // ベクトルの長さが0の場合、(0,0)を返す
    }
    return Vector2(x / mag, y / mag);  // 正規化したベクトルを返す
}

//================================================================
// ベクトルの加算
//================================================================
 Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

//================================================================
// ベクトルの減算
//================================================================
 Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

//================================================================
// スカラーとの乗算（掛け算）
//================================================================
 Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

//================================================================
// スカラーとの除算（割り算）
//================================================================
 Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

//================================================================
// 
//================================================================
 void Vector2::CenterPositionSync(Vector2 centerpos, int size)
{
    float pic_size_half = ((float)size / 2 - 1);				//RECTの半分の長さ()

    /*スプライトの左上座標設定*/
    x = (centerpos.x) - pic_size_half;	//中心座標 - 画像サイズの半径 - 1(補正)
    y = (centerpos.y) - pic_size_half;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /*Boxcollider(四角形の頂点をfloat型 left , right ,top , bottomで管理する)*/

//================================================================
// 矩形同士の衝突判定
//================================================================

 bool Boxcollider::BoxCollision(const Boxcollider& other) const {
    return !(right < other.left || left > other.right || bottom < other.top || top > other.bottom);
}

//================================================================
// 指定された点がこの矩形の中にあるかを判定
//================================================================
 bool Boxcollider::PosCollision(Vector2 pos) const {
    return (pos.x >= left && pos.x <= right && pos.y >= top && pos.y <= bottom);
}

//================================================================
// 中心座標から頂点の位置をセットする
//================================================================
 void Boxcollider::CenterPositionSync(Vector2 centerpos, int size)
{
    float hitbox_size_half = ((float)size / 2);		//ステータスの当たり判定の半分の長さ()

    /*当たり判定の同期*/
    left = (centerpos.x) - hitbox_size_half;
    top = (centerpos.y) - hitbox_size_half;
    right = (centerpos.x) + hitbox_size_half;
    bottom = (centerpos.y) + hitbox_size_half;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     /*StringText(文字列を保持し、場合によっては Cスタイルのchar[]に変換する)*/


//================================================================
// std::string を char[] に変換して外部に渡す関数
//================================================================
 const char* StringText::toCharArray() const {
    return str.c_str();  // std::string の Cスタイル文字列へのポインタを返す
}

//================================================================
// テキストを動的に更新する関数
//================================================================
 void StringText::updateText(const std::string& newText) {
    str = newText;  // 新しい文字列で更新
}

//================================================================
// テキストに追記する関数
//================================================================
 void StringText::appendText(const std::string& additionalText) {
    str += additionalText;  // 文字列を追記
}

//================================================================
// テキストの内容を表示（デバッグ用）
//================================================================
 void StringText::printString() const {
    std::cout << "std::string: " << str << std::endl;
}
