
#ifndef TESTINPUTMANAGER_H
#define TESTINPUTMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              �e�X�g�pInputManager
// 
// ���͂��Ǘ�����N���X
// �����L�[�AZ�L�[�AX�L�[�AEnter�L�[�AESC�L�[�Ȃǂ̓��͂ɉ����ăt���O��ON/OFF����
// InputPritf��press,pushdown,pushup,trigger�Ȃǂ̃t���O��Ԃ��m�F�ł���
// GameManager��InputReception�֐�����x�������΁A���̎��̓��͂ɉ����ăt���O���؂�ւ��B
//		���̂��߁A���̃N���X��IsFlagSet�Ŋm�F�������t���O���w�肵��bool�̕Ԃ�l�œ��̗͂L�����킩��
//----------------------------------------------------------------------------------------------------

#include "IInputManager.h"
#include "Geometry.h"

class TestInputManager: public IInputManager {
	public:
		TestInputManager() : active(true), pressFlags(0), triggerFlags(0), releaseFlags(0), toggleFlags(0), directionkeyaxis(Vector2::zero) {}
		~TestInputManager() {}

		int InputReception()override;							//���͎󂯕t����
		void ClearAll()override;								// �S�Ẵt���O���N���A
		int GetFlags(InputMode mode) const override;			// �t���O���擾
		void SetFlag(InputFlag flag, InputMode mode)override;	// �t���O�̐ݒ�i�r�b�gOR�j
		void ClearFlag(InputFlag flag, InputMode mode)override;	// �t���O�̉����i�r�b�gAND NOT�j
		void ToggleFlag(InputFlag flag)override;				// �t���O�̃g�O���i�r�b�gXOR�j
		bool IsFlagSet(InputFlag flag, InputMode mode) const;	// �t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
		bool FlagsCompare(int a, int b, InputFlag flag);		//�r�b�g���m�Ŕ�r���A�����r�b�g�񂪗����Ă���Ȃ�true,�Ȃ��Ȃ�false��Ԃ�
		void SetActive(bool ac)override { active = ac; }		//���̗͂L����Ԃ�ݒ肷��
		bool Active()const override { return active; }			//���̗͂L����Ԃ��m�F����
		Vector2 GetAxis()const  override { return directionkeyaxis; };

		void InputPritf();			//�e�X�g�p�̕`��


		void GetKeySetup() override;		//�L�[�̓��͏�Ԃ�������

		Vector2 Dirctionkeyinput(InputMode mode) override;		//�����L�[�̓��͂�vector�̒l�Ŏ擾����
		Vector2 DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) override;		//�����L�[�̓��͂�0�`1�̊ԂŎ󂯎��

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


		void InputFlagsControl(InputFlag flag, bool inputley);		//�S�̃r�b�g��ON/OFF������

private:
	bool active;
	int pressFlags = 0;       // �L�[��������Ă���Ԃ̃t���O
	int triggerFlags = 0;     // �����̏u�Ԃ̃t���O
	int releaseFlags = 0;     // �������u�Ԃ̃t���O
	int toggleFlags = 0;      // �g�O����Ԃ̃t���O
	Vector2 directionkeyaxis;


};


#endif // TESTINPUTMANAGER_H