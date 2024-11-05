
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

class DebugManager;

#include "InputManager.h"

class TestInputManager: public InputManager {
	public:
		TestInputManager() {}
		~TestInputManager() {}
		enum class DebugInputFlag {
			DebugMode           = 1 << 0,	     
			createA_Enemy       = 1 << 1,	    
			updateA_Enemynumber = 1 << 2,	    
			createG_Enemy       = 1 << 3,	     
			updateG_Enemynumber = 1 << 4,	   
			createE_Shot		= 1 << 5,

		};
		enum class DebugCreateAirEnemyFlag {
			DebugMode     = 1 << 0,	     // 0001
			toroid        = 1 << 1,	     // 0010
			toroid_t2     = 1 << 2,	     // 0100
			torken        = 1 << 3,      // 1000
			giddospario   = 1 << 4,      // 0001 0000
			zoshi         = 1 << 5,      // 0010 0000
			zoshi_t2      = 1 << 6,      // 0100 0000
			zoshi_t3      = 1 << 7,      // 0100 0000
			jara          = 1 << 8,	     // 1000 0000
			jara_t2       = 1 << 9,	     // 1000 0000
			kapi          = 1 << 10,     // 0001 0000 0000
			terrazi       = 1 << 11,      // 0010 0000 0000
			zakato        = 1 << 12,	 // 0100 0000 0000
			zakato_t2     = 1 << 13,	 // 0100 0000 0000
			zakato_t3     = 1 << 14,	 // 0100 0000 0000
			zakato_t4     = 1 << 15,	 // 0100 0000 0000
			bragzakato    = 1 << 16,	 // 0100 0000 0000
			bragzakato_t2 = 1 << 17,	 // 0100 0000 0000
			garuzakato	  = 1 << 18,	 // 0100 0000 0000
			garuzakato_t2 = 1 << 19,	 // 0100 0000 0000
			garuzakato_t3 = 1 << 20,	 // 0100 0000 0000
			garuzakato_t4 = 1 << 21,	 // 0100 0000 0000
			BACURA = 1 << 22,	 // 0100 0000 0000
		};
		enum class DebugCreateGroundEnemyFlag {
			debugmode     = 1 << 0,	     // 0001
			barra         = 1 << 1,	     // 0010
			zolbak        = 1 << 2,	     // 0100
			logram        = 1 << 3,      // 1000
			logram_t2     = 1 << 4,      // 1000
			logram_t3     = 1 << 5,      // 1000
			logram_t4     = 1 << 6,      // 1000
			logram_t5     = 1 << 7,      // 1000
			domogram      = 1 << 9,      // 0001 0000
			derota        = 1 << 10,      // 0010 0000
			grobda        = 1 << 11,      // 0100 0000
			grobda_t2     = 1 << 12,      // 0100 0000
			grobda_t3     = 1 << 13,	     // 1000 0000
			grobda_t4     = 1 << 14,	     // 1000 0000
			grobda_t5     = 1 << 15,     // 0001 0000 0000
			grobda_t6     = 1 << 16,      // 0010 0000 0000
			grobda_t7     = 1 << 17,	 // 0100 0000 0000
			grobda_t8     = 1 << 18,	 // 0100 0000 0000
			grobda_t9     = 1 << 19,	 // 0100 0000 0000
			bozalogram    = 1 << 20,	 // 0100 0000 0000
			sol           = 1 << 21,	 // 0100 0000 0000
			garubarra     = 1 << 22,	 // 0100 0000 0000
			garuderota    = 1 << 23,	 // 0100 0000 0000
			specialflag   = 1 << 24,	 // 0100 0000 0000
		};

		int InputReception()override;
		void GetKeySetup() override;
		Vector2 Dirctionkeyinput(InputMode mode) override;
		Vector2 DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) override;
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


		void InputFlagsControl(InputFlag flag, bool inputley);

		bool DebugSwitch();
		bool DebugCreateA_Enemy();
		bool DebugCreateA_EnemyNumberUpdate();
		bool DebugCreateG_Enemy();
		bool DebugCreateG_EnemyNumberUpdate();
		bool DebugCreateEnemyShot();

		bool DebugIsFlagSet(DebugInputFlag flag) const;
		void DebugInputFlagsControl(DebugInputFlag flag, bool inputley);



private:
	std::shared_ptr<DebugManager> debug_;

	int debugtriggerFlags = 0;     // �����̏u�Ԃ̃t���O
	int debugcreateA_enemyFlags = 0;     // �����̏u�Ԃ̃t���O
	int debugcreateG_enemyFlags = 0;     // �����̏u�Ԃ̃t���O
};


#endif // TESTINPUTMANAGER_H