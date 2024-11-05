
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

using InputFlag = IInputManager::InputFlag;

//=======================================================
//		キー入力をするためのセットアップ
//=======================================================
void TestInputManager::GetKeySetup()
{
	InputManager::GetKeySetup();	//全てのキー入力。
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


	DebugSwitch();
	DebugCreateA_Enemy();
	DebugCreateA_EnemyNumberUpdate();
	DebugCreateG_Enemy();
	DebugCreateG_EnemyNumberUpdate();
	DebugCreateEnemyShot();


	return 0;
}

//=======================================================
//		方向キーの入力をVector2で返す
// 
// 値の大きさは'1'
//=======================================================
Vector2 TestInputManager::Dirctionkeyinput(InputMode mode)
{
	return InputManager::Dirctionkeyinput(mode);


}


//==============================================================================================================
//						方向キーの入力を0～1の間をfloat値で管理する
//  
// 第三引数が1フレームに増加する値で、入力を検知したら入力方向によってその値を増減させる
//==============================================================================================================
Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	return InputManager::DirctionkeyinputAxis(x_value, y_value, maxspeed);
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
	return InputManager::SetFlag(flag, mode);
}

//=======================================================
//			フラグの解除（ビットAND NOT）
//=======================================================
void TestInputManager::ClearFlag(InputFlag flag, InputMode mode) {
	return InputManager::ClearFlag(flag, mode);
}

//=======================================================
//			 フラグのトグル（ビットXOR）
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	return InputManager::ToggleFlag(flag);

	
}

//=======================================================
//			フラグが設定されているか確認（ビットAND）
//=======================================================
bool TestInputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
	return InputManager::IsFlagSet(flag, mode);
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

	return 0;
}




bool TestInputManager::DebugSwitch()
{
	DebugInputFlagsControl(DebugInputFlag::DebugMode, ChkKeyEdge(PK_D));

	return false;
}
bool TestInputManager::DebugCreateA_Enemy()
{
	DebugInputFlagsControl(DebugInputFlag::createA_Enemy, ChkKeyEdge(PK_A));

	return false;

}
bool TestInputManager::DebugCreateA_EnemyNumberUpdate()
{

	DebugInputFlagsControl(DebugInputFlag::updateA_Enemynumber, ChkKeyEdge(PK_Q));

	return false;

}
bool TestInputManager::DebugCreateG_Enemy()
{

	DebugInputFlagsControl(DebugInputFlag::createG_Enemy, ChkKeyEdge(PK_S));

	return false;

}
bool TestInputManager::DebugCreateG_EnemyNumberUpdate()
{

	DebugInputFlagsControl(DebugInputFlag::updateG_Enemynumber, ChkKeyEdge(PK_W));

	return false;

}
bool TestInputManager::DebugCreateEnemyShot()
{
	DebugInputFlagsControl(DebugInputFlag::createE_Shot, ChkKeyEdge(PK_F));

	return false;

}

//==============================================================================================================
//											押した瞬間
// 
// 押した瞬間（pushdown)  : 入力が 1 で前回のフラグが 0 だった
//==============================================================================================================

void TestInputManager::DebugInputFlagsControl(DebugInputFlag flag, bool inputley)
{
	bool toggle = inputley != DebugIsFlagSet(flag);	//pressを前回の入力として使い、現在の入力と比較する

	int bit = static_cast<int>(flag);


	// 押した瞬間（pushdown）
	if (inputley && toggle) debugtriggerFlags |= bit;
	else					debugtriggerFlags &= ~bit;
}


//=======================================================
//			フラグが設定されているか確認（ビットAND）
//=======================================================

bool TestInputManager::DebugIsFlagSet(DebugInputFlag flag) const {
	int bit = static_cast<int>(flag);

	return (debugtriggerFlags & bit) != 0;

}