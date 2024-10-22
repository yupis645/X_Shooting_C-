
#ifndef TESTINPUTMANAGER_H
#define TESTINPUTMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              テスト用InputManager
// 
// 入力を管理するクラス
// 方向キー、Zキー、Xキー、Enterキー、ESCキーなどの入力に応じてフラグをON/OFFする
// InputPritfでpress,pushdown,pushup,triggerなどのフラグ状態を確認できる
// GameManagerでInputReception関数を一度動かせば、その時の入力に応じてフラグが切り替わる。
//		そのため、他のクラスはIsFlagSetで確認したいフラグを指定してboolの返り値で入力の有無がわかる
//----------------------------------------------------------------------------------------------------

#include "IInputManager.h"
#include "Geometry.h"

class TestInputManager: public IInputManager {
	public:
		TestInputManager() : active(true), pressFlags(0), triggerFlags(0), releaseFlags(0), toggleFlags(0), directionkeyaxis(Vector2::zero) {}
		~TestInputManager() {}

		int InputReception()override;							//入力受け付ける
		void ClearAll()override;								// 全てのフラグをクリア
		int GetFlags(InputMode mode) const override;			// フラグを取得
		void SetFlag(InputFlag flag, InputMode mode)override;	// フラグの設定（ビットOR）
		void ClearFlag(InputFlag flag, InputMode mode)override;	// フラグの解除（ビットAND NOT）
		void ToggleFlag(InputFlag flag)override;				// フラグのトグル（ビットXOR）
		bool IsFlagSet(InputFlag flag, InputMode mode) const;	// フラグが設定されているか確認（ビットAND）
		bool FlagsCompare(int a, int b, InputFlag flag);		//ビット同士で比較し、同じビット列が立っているならtrue,ないならfalseを返す
		void SetActive(bool ac)override { active = ac; }		//入力の有効状態を設定する
		bool Active()const override { return active; }			//入力の有効状態か確認する
		Vector2 GetAxis()const  override { return directionkeyaxis; };

		void InputPritf();			//テスト用の描画


		void GetKeySetup() override;		//キーの入力状態を許可する

		Vector2 Dirctionkeyinput(InputMode mode) override;		//方向キーの入力をvectorの値で取得する
		Vector2 DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) override;		//方向キーの入力を0～1の間で受け取る

		void left() override;
		void right() override;
		void up() override;
		void down() override;
		void select() override;
		void cancel() override;
		void shot() override;
		void bom() override;
		void pose() override;
		void esc() override;


		void InputFlagsControl(InputFlag flag, bool inputley);		//４つのビットのON/OFFをする

private:
	bool active;
	int pressFlags = 0;       // キーが押されている間のフラグ
	int triggerFlags = 0;     // 押下の瞬間のフラグ
	int releaseFlags = 0;     // 離した瞬間のフラグ
	int toggleFlags = 0;      // トグル状態のフラグ
	Vector2 directionkeyaxis;


};


#endif // TESTINPUTMANAGER_H