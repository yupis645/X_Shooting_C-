#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              ���͂��Ǘ�����N���X
// 
// ���͂��Ǘ�����N���X
// �����L�[�AZ�L�[�AX�L�[�AEnter�L�[�AESC�L�[�Ȃǂ̓��͂ɉ����ăt���O��ON/OFF����
// GameManager��InputReception�֐�����x�������΁A���̎��̓��͂ɉ����ăt���O���؂�ւ��B
//		���̂��߁A���̃N���X��IsFlagSet�Ŋm�F�������t���O���w�肵��bool�̕Ԃ�l�œ��̗͂L�����킩��
//----------------------------------------------------------------------------------------------------

#include "IInputManager.h"

class InputManager : public IInputManager {
public:
	InputManager() : active(true), gamemode(0), pressFlags(0), triggerFlags(0), releaseFlags(0), toggleFlags(0), directionkeyaxis(Vector2::zero) {}
	~InputManager() {}

	int InputReception()override;
	void GetKeySetup() override;
	Vector2 Dirctionkeyinput(InputMode mode) override;
	Vector2 DirctionkeyinputAxis(float x_value, float y_value,float maxspeed) override;
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

	// �S�Ẵt���O���N���A
	void ClearAll()override;

	// �t���O���擾
	int GetFlags(InputMode mode) const override;

	// �t���O�̐ݒ�i�r�b�gOR�j
	void SetFlag(InputFlag flag, InputMode mode)override;

	// �t���O�̉����i�r�b�gAND NOT�j
	void ClearFlag(InputFlag flag, InputMode mode)override;

	// �t���O�̃g�O���i�r�b�gXOR�j
	void ToggleFlag(InputFlag flag)override;

	// �t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
	bool IsFlagSet(InputFlag flag, InputMode mode) const;

	//�r�b�g���m�Ŕ�r���A�����r�b�g�񂪗����Ă���Ȃ�true,�Ȃ��Ȃ�false��Ԃ�
	bool FlagsCompare(int a, int b,InputFlag flag);

	void InputFlagsControl(InputFlag flag, bool inputley);

	void SetActive(bool ac)override { active = ac; }
	bool Active()const override { return active; }
	void SetGamemode(int mode)override { gamemode = mode; }
	int Gamemode() const override { return gamemode; }
	Vector2 GetAxis()const  override { return directionkeyaxis; };

private:
	bool active;
	int gamemode;
	int pressFlags = 0;       // �L�[��������Ă���Ԃ̃t���O
	int triggerFlags = 0;     // �����̏u�Ԃ̃t���O
	int releaseFlags = 0;     // �������u�Ԃ̃t���O
	int toggleFlags = 0;      // �g�O����Ԃ̃t���O
	Vector2 directionkeyaxis;
};


#endif // INPUTMANAGER_H