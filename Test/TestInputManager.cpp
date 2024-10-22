
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

//=======================================================
//		キーの入力状態を画面に表示する
//=======================================================
void TestInputManager::InputPritf()
{
	auto is = [this](InputFlag flag,InputMode mode) { return IsFlagSet(flag, mode); };
	auto f = [this, is](InputFlag flag, InputMode mode) {return is(flag, mode) ? "true" : "false";};

	//方向キーをfloat値で0～1を取得する
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 28), 0,
		"		GetAxis ( %f , %f )", this->GetAxis().x, this->GetAxis().y);
	//各ビットフラグの状態の目次。下に同じカテゴリが続く
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 25), 0, 
		"Input Flags Bit = press:%d , pushdown:%d , pushup:%d , toggle:%d ,  ", GetFlags(InputMode::press), GetFlags(InputMode::pushdown), GetFlags(InputMode::pushup), GetFlags(InputMode::toggle));

	
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 22), 0, "left   = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::left,InputMode::press),f(InputFlag::left,InputMode::pushdown),f(InputFlag::left,InputMode::pushup),f(InputFlag::left,InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 20), 0, "right  = %5s ,%5s ,%5s ,%5s \n ",
		f(InputFlag::right, InputMode::press), f(InputFlag::right, InputMode::pushdown), f(InputFlag::right, InputMode::pushup), f(InputFlag::right, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 18), 0, "down   = %5s,%5s ,%5s ,%5s  \n ", 
	f(InputFlag::down, InputMode::press), f(InputFlag::down, InputMode::pushdown), f(InputFlag::down, InputMode::pushup), f(InputFlag::down, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 16), 0, "up     = %5s,%5s ,%5s ,%5s  \n ", 
	f(InputFlag::up, InputMode::press), f(InputFlag::up, InputMode::pushdown), f(InputFlag::up, InputMode::pushup), f(InputFlag::up, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 14), 0, "select = %5s ,%5s ,%5s ,%5s \n ",
	f(InputFlag::select, InputMode::press), f(InputFlag::select, InputMode::pushdown), f(InputFlag::select, InputMode::pushup), f(InputFlag::select, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 12), 0, "cancel = %5s ,%5s ,%5s ,%5s \n ", 
	f(InputFlag::cancel, InputMode::press), f(InputFlag::cancel, InputMode::pushdown), f(InputFlag::cancel, InputMode::pushup), f(InputFlag::cancel, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 10), 0, "pose   = %5s,%5s ,%5s ,%5s  \n ",
	f(InputFlag::pose, InputMode::press), f(InputFlag::pose, InputMode::pushdown), f(InputFlag::pose, InputMode::pushup), f(InputFlag::pose, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 8), 0, "shot   = %5s ,%5s ,%5s ,%5s \n ",
	f(InputFlag::shot, InputMode::press), f(InputFlag::shot, InputMode::pushdown), f(InputFlag::shot, InputMode::pushup), f(InputFlag::shot, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 6), 0, "bom     = %5s ,%5s ,%5s ,%5s \n ",
	f(InputFlag::bom, InputMode::press), f(InputFlag::bom, InputMode::pushdown), f(InputFlag::bom, InputMode::pushup), f(InputFlag::bom, InputMode::toggle));
	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 4), 0, "esc    = %5s ,%5s ,%5s ,%5s \n ",
	f(InputFlag::esc, InputMode::press), f(InputFlag::esc, InputMode::pushdown), f(InputFlag::esc, InputMode::pushup), f(InputFlag::esc, InputMode::toggle));
}

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
	if (active == false) return 1;		//もしactiveがfalseなら入力を受け付けず終了する

	GetKeySetup();	//キー入力の準備

	//キーの入力受付
	left();
	right();
	up();
	down();
	select();
	cancel();
	shot();
	bom();
	pose();
	esc();


	InputPritf();
	directionkeyaxis = DirctionkeyinputAxis(0.01f, 0.01f, 1);

	//テストモード有効時のみ作用

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
	Vector2 vec = Vector2::zero;


	if (IsFlagSet(InputFlag::left, InputMode::press))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::press)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::press))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::press))  vec.y += 1;


	return vec;
}


//==============================================================================================================
//						方向キーの入力を0～1の間をfloat値で管理する
//  
// 第三引数が1フレームに増加する値で、入力を検知したら入力方向によってその値を増減させる
//==============================================================================================================
Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	// 初期化：キー入力に基づく方向ベクトル
	Vector2 empty = directionkeyaxis;

	// 減速処理ラムダ：指定の閾値以下なら0に補正
	auto zerooffset = [](float value, float minvalue) { return (std::abs(value) < minvalue) ? 0.0f : value * 0.9f; };

	//方向キーの入力を取得する
	bool left = IsFlagSet(InputFlag::left, InputMode::press);
	bool right = IsFlagSet(InputFlag::right, InputMode::press);
	bool up = IsFlagSet(InputFlag::up, InputMode::press);
	bool down = IsFlagSet(InputFlag::down, InputMode::press);

	// X軸の処理
	if (left)			empty.x -= x_value;							//xを左方向にいくようにy_value減算する
	if (right)			empty.x += x_value;							//xを右方向にいくようにx_value減算する									
	if (!left && !right)	empty.x = zerooffset(empty.x, x_value);		// 操作がない場合の減速処理


	// Y軸の処理
	if (up)				empty.y -= y_value;										//yを上方向にいくようにy_value減算する
	if (down)			empty.y += y_value;										//yを下方向にいくようにy_Valueを加算する
	if (!up && !down)	empty.y = zerooffset(empty.y, y_value); // 操作がない場合の減速処理


	// 最大速度の制限
	if (std::abs(empty.x) > maxspeed)	empty.x = (empty.x > 0 ? 1 : -1) * maxspeed;
	if (std::abs(empty.y) > maxspeed) 	empty.y = (empty.y > 0 ? 1 : -1) * maxspeed;

	return empty;
}

//=======================================================
//			左方向入力
//=======================================================
void TestInputManager::left()
{
	TestInputManager::InputFlagsControl(InputFlag::left, ChkKeyPress(PK_LEFT));
}

//=======================================================
//			右方向入力
//=======================================================
void TestInputManager::right()
{
	TestInputManager::InputFlagsControl(InputFlag::right, ChkKeyPress(PK_RIGHT));
}

//=======================================================
//			上方向入力
//=======================================================
void TestInputManager::up()
{
	TestInputManager::InputFlagsControl(InputFlag::up, ChkKeyPress(PK_UP));

}
//=======================================================
//			下方向入力
//=======================================================
void TestInputManager::down()
{
	TestInputManager::InputFlagsControl(InputFlag::down, ChkKeyPress(PK_DOWN));
}
//=======================================================
//				セレクトボタン
//=======================================================
void  TestInputManager::select()
{
	bool input = ChkKeyEdge(VK_RETURN) || ChkKeyEdge(PK_Z);

	TestInputManager::InputFlagsControl(InputFlag::select, input);
}

//=======================================================
//			キャンセルボタン
//=======================================================
void  TestInputManager::cancel()
{
	TestInputManager::InputFlagsControl(InputFlag::cancel, ChkKeyPress(PK_X));
}

//=======================================================
//			ESC(ゲームの終了)
//=======================================================	
void  TestInputManager::esc()
{
	TestInputManager::InputFlagsControl(InputFlag::esc, ChkKeyPress(VK_ESCAPE));
}
//=======================================================
//			ショットの発射
//=======================================================
void  TestInputManager::shot()
{

	TestInputManager::InputFlagsControl(InputFlag::shot, ChkKeyPress(PK_Z));
}
//=======================================================
//				ボム発射
//=======================================================
void  TestInputManager::bom()
{

	TestInputManager::InputFlagsControl(InputFlag::bom, ChkKeyPress(PK_X));
}

//=======================================================
//				ポーズ(一時停止)
//=======================================================
void  TestInputManager::pose()
{
	TestInputManager::InputFlagsControl(InputFlag::pose, ChkKeyPress(PK_SP));
}

/////--------------------------------------------------------------------------------------------------------------

//=======================================================
//			フラグの設定（ビットOR）
//=======================================================
void TestInputManager::SetFlag(InputFlag flag, InputMode mode) {
	int bit = static_cast<int>(flag);

	switch (mode) {
	case InputMode::press:
		pressFlags |= bit;
		break;
	case InputMode::pushdown:
		triggerFlags |= bit;
		break;
	case InputMode::pushup:
		releaseFlags |= bit;
		break;
	case InputMode::toggle:
		toggleFlags ^= bit;  // トグル状態の反転
		break;
	}
}

//=======================================================
//			フラグの解除（ビットAND NOT）
//=======================================================
void TestInputManager::ClearFlag(InputFlag flag, InputMode mode) {
	int bit = static_cast<int>(flag);

	switch (mode) {
	case InputMode::press:
		pressFlags &= ~bit;
		break;
	case InputMode::pushdown:
		triggerFlags &= ~bit;
		break;
	case InputMode::pushup:
		releaseFlags &= ~bit;
		break;
	case InputMode::toggle:
		toggleFlags &= ~bit;
		break;
	}
}

//=======================================================
//			 フラグのトグル（ビットXOR）
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	toggleFlags ^= static_cast<int>(flag);
}

//=======================================================
//			フラグが設定されているか確認（ビットAND）
//=======================================================
bool TestInputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
	int bit = static_cast<int>(flag);

	switch (mode) {
	case InputMode::press:
		return (pressFlags & bit) != 0;
	case InputMode::pushdown:
		return (triggerFlags & bit) != 0;
	case InputMode::pushup:
		return (releaseFlags & bit) != 0;
	case InputMode::toggle:
		return (toggleFlags & bit) != 0;
	}
	return false;
}

//=======================================================
//ビット同士で比較
//=======================================================
inline bool TestInputManager::FlagsCompare(int a, int b, InputFlag flag) {
	return ((a & static_cast<int>(flag)) != 0) == ((b & static_cast<int>(flag)) != 0);
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
	bool toggle = inputley != IsFlagSet(flag, InputMode::press);	//pressを前回の入力として使い、現在の入力と比較する


	// 押した瞬間（pushdown）
	if (inputley && toggle) SetFlag(flag, InputMode::pushdown);
	else					ClearFlag(flag, InputMode::pushdown);

	// 離した瞬間（pushup）
	if (!inputley && toggle)SetFlag(flag, InputMode::pushup);
	else					ClearFlag(flag, InputMode::pushup);

	// トグル（toggle）
	if (toggle) {  // 離したときにトグルを切り替え
		ToggleFlag(flag);
	}

	// 押されている間（press）
	if (inputley)	SetFlag(flag, InputMode::press);
	else			ClearFlag(flag, InputMode::press);
}

//=======================================================
//			全てのフラグをクリア
//=======================================================
void TestInputManager::ClearAll() {
	pressFlags = 0;
}

//=======================================================
//			フラグを取得（必要に応じて）
//=======================================================
int TestInputManager::GetFlags(InputMode mode) const {

	if (mode == InputMode::pushdown)	return triggerFlags;
	if (mode == InputMode::pushup)		return releaseFlags;
	if (mode == InputMode::press)		return pressFlags;
	if (mode == InputMode::toggle)		return toggleFlags;

	return -1;
}


