
//----------------------------------------------------------------------------------------------------
//                              テスト用InputManager
// 
// 入力を管理するクラス
// 方向キー、Zキー、Xキー、Enterキー、ESCキーなどの入力に応じてフラグをON/OFFする
// InputPritfでpress,pushdown,pushup,triggerなどのフラグ状態を確認できる
// GameManagerでInputReception関数を一度動かせば、その時の入力に応じてフラグが切り替わる。
//		そのため、他のクラスはIsFlagSetで確認したいフラグを指定してboolの返り値で入力の有無がわかる
//----------------------------------------------------------------------------------------------------

#include "TestInputManager.h"
#include "conioex.h"
#include "Geometry.h"
#include "common.h"
#include "conioex.h"

//=======================================================
//		キー入力をするためのセットアップ
//=======================================================
void TestInputManager::GetKeySetup()
{
	GetKeyAll();	//全てのキー入力。
}

//=======================================================
//			入力に対してflagsをセットする
// 
// 関数の初めに前回の入力フラグを全て初期化する
// activeがfalseなら入力を受け付けず、関数を終了する
//=======================================================
int TestInputManager::InputReception()
{
	InputManager::InputReception();

#if TestMode
	if (DebugOn) {				//
		if (ChkKeyEdge(PK_D)) {
			DebugEnable = DebugEnable ? false : true;
		}
	}
#endif

	return 0;
}

//=======================================================
//		方向キーの入力をVector2で返す
// 
// 値の大きさは'1'
//=======================================================
Vector2 TestInputManager::Dirctionkeyinput(InputMode mode)
{
	auto dirction = InputManager::Dirctionkeyinput(mode);

}


//==============================================================================================================
//						方向キーの入力を0～1の間をfloat値で管理する
//  
// 第三引数が1フレームに増加する値で、入力を検知したら入力方向によってその値を増減させる
//==============================================================================================================
Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	InputManager::DirctionkeyinputAxis(x_value, y_value, maxspeed);
}

//=======================================================
//			左方向入力
//=======================================================
void TestInputManager::left()
{
	InputManager::left();
}

//=======================================================
//			右方向入力
//=======================================================
void TestInputManager::right()
{
	InputManager::right();
}

//=======================================================
//			上方向入力
//=======================================================
void TestInputManager::up()
{
	InputManager::up();

}
//=======================================================
//			下方向入力
//=======================================================
void TestInputManager::down()
{
	InputManager::down();
}
//=======================================================
//				セレクトボタン
//=======================================================
void  TestInputManager::select()
{
	InputManager::select();
}

//=======================================================
//			キャンセルボタン
//=======================================================
void  TestInputManager::cancel()
{
	InputManager::cancel();
}

//=======================================================
//			ESC(ゲームの終了)
//=======================================================	
void  TestInputManager::esc()
{
	InputManager::esc();
}


bool TestInputManager::DebugSwitch()
{
	return ChkKeyEdge(PK_D);
}
bool TestInputManager::DebugCreateAirEnemy()
{
	return ChkKeyEdge(PK_A);

}
bool TestInputManager::DebugCreateEnemyShot()
{
	return ChkKeyEdge(PK_F);

}
//=======================================================
//			ショットの発射
//=======================================================
void  TestInputManager::shot()
{
	InputManager::shot();
}
//=======================================================
//				ボム発射
//=======================================================
void  TestInputManager::bom()
{
	InputManager::bom();
}

//=======================================================
//				ポーズ(一時停止)
//=======================================================
void  TestInputManager::pose()
{
	InputManager::pose();
}

/////--------------------------------------------------------------------------------------------------------------

//=======================================================
//			フラグの設定（ビットOR）
//=======================================================
void TestInputManager::SetFlag(InputFlag flag, InputMode mode) {
	InputManager::SetFlag(flag, mode);
}

//=======================================================
//			フラグの解除（ビットAND NOT）
//=======================================================
void TestInputManager::ClearFlag(InputFlag flag, InputMode mode) {
	InputManager::ClearFlag(flag, mode);
}

//=======================================================
//			 フラグのトグル（ビットXOR）
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	InputManager::ToggleFlag(flag);
}

//=======================================================
//			フラグが設定されているか確認（ビットAND）
//=======================================================
bool TestInputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
	InputManager::IsFlagSet(flag, mode);
}

//=======================================================
//ビット同士で比較
//=======================================================
bool TestInputManager::FlagsCompare(int a, int b, InputFlag flag) {
	InputManager::FlagsCompare(a, b, flag);
}


//==============================================================================================================
//				一つのキーに対して押し続ける、押した瞬間、離した瞬間、トグルのフラグを管理する
// 
// 押した瞬間（pushdown)  : 入力が 1 で前回のフラグが 0 だった
// 離した瞬間（pushup）	  : 入力が 0 で前回のフラグが 1 だった
// トグル（toggle）		  : 入力と前回のフラグが違うなら
// 押されている間（press) : 入力が 1 である限り
//==============================================================================================================
void TestInputManager::InputFlagsControl(InputFlag flag, bool inputley)
{
	InputManager::InputFlagsControl(flag, inputley);
}

//=======================================================
//			全てのフラグをクリア
//=======================================================
void TestInputManager::ClearAll() {
	InputManager::ClearAll();
}

//=======================================================
//			フラグを取得（必要に応じて）
//=======================================================
int TestInputManager::GetFlags(InputMode mode) const {
	if (InputManager::GetFlags(mode) == -1)
	{
		//エラー
	}
}


