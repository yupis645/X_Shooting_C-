
//----------------------------------------------------------------------------------------------------
//                              �e�X�g�pInputManager
// 
// ���͂��Ǘ�����N���X
// �����L�[�AZ�L�[�AX�L�[�AEnter�L�[�AESC�L�[�Ȃǂ̓��͂ɉ����ăt���O��ON/OFF����
// InputPritf��press,pushdown,pushup,trigger�Ȃǂ̃t���O��Ԃ��m�F�ł���
// GameManager��InputReception�֐�����x�������΁A���̎��̓��͂ɉ����ăt���O���؂�ւ��B
//		���̂��߁A���̃N���X��IsFlagSet�Ŋm�F�������t���O���w�肵��bool�̕Ԃ�l�œ��̗͂L�����킩��
//----------------------------------------------------------------------------------------------------

#include "TestInputManager.h"
#include "conioex.h"
#include "Geometry.h"
#include "common.h"
#include "conioex.h"

//=======================================================
//		�L�[���͂����邽�߂̃Z�b�g�A�b�v
//=======================================================
void TestInputManager::GetKeySetup()
{
	GetKeyAll();	//�S�ẴL�[���́B
}

//=======================================================
//			���͂ɑ΂���flags���Z�b�g����
// 
// �֐��̏��߂ɑO��̓��̓t���O��S�ď���������
// active��false�Ȃ���͂��󂯕t�����A�֐����I������
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
//		�����L�[�̓��͂�Vector2�ŕԂ�
// 
// �l�̑傫����'1'
//=======================================================
Vector2 TestInputManager::Dirctionkeyinput(InputMode mode)
{
	auto dirction = InputManager::Dirctionkeyinput(mode);

}


//==============================================================================================================
//						�����L�[�̓��͂�0�`1�̊Ԃ�float�l�ŊǗ�����
//  
// ��O������1�t���[���ɑ�������l�ŁA���͂����m��������͕����ɂ���Ă��̒l�𑝌�������
//==============================================================================================================
Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	InputManager::DirctionkeyinputAxis(x_value, y_value, maxspeed);
}

//=======================================================
//			����������
//=======================================================
void TestInputManager::left()
{
	InputManager::left();
}

//=======================================================
//			�E��������
//=======================================================
void TestInputManager::right()
{
	InputManager::right();
}

//=======================================================
//			���������
//=======================================================
void TestInputManager::up()
{
	InputManager::up();

}
//=======================================================
//			����������
//=======================================================
void TestInputManager::down()
{
	InputManager::down();
}
//=======================================================
//				�Z���N�g�{�^��
//=======================================================
void  TestInputManager::select()
{
	InputManager::select();
}

//=======================================================
//			�L�����Z���{�^��
//=======================================================
void  TestInputManager::cancel()
{
	InputManager::cancel();
}

//=======================================================
//			ESC(�Q�[���̏I��)
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
//			�V���b�g�̔���
//=======================================================
void  TestInputManager::shot()
{
	InputManager::shot();
}
//=======================================================
//				�{������
//=======================================================
void  TestInputManager::bom()
{
	InputManager::bom();
}

//=======================================================
//				�|�[�Y(�ꎞ��~)
//=======================================================
void  TestInputManager::pose()
{
	InputManager::pose();
}

/////--------------------------------------------------------------------------------------------------------------

//=======================================================
//			�t���O�̐ݒ�i�r�b�gOR�j
//=======================================================
void TestInputManager::SetFlag(InputFlag flag, InputMode mode) {
	InputManager::SetFlag(flag, mode);
}

//=======================================================
//			�t���O�̉����i�r�b�gAND NOT�j
//=======================================================
void TestInputManager::ClearFlag(InputFlag flag, InputMode mode) {
	InputManager::ClearFlag(flag, mode);
}

//=======================================================
//			 �t���O�̃g�O���i�r�b�gXOR�j
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	InputManager::ToggleFlag(flag);
}

//=======================================================
//			�t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
//=======================================================
bool TestInputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
	InputManager::IsFlagSet(flag, mode);
}

//=======================================================
//�r�b�g���m�Ŕ�r
//=======================================================
bool TestInputManager::FlagsCompare(int a, int b, InputFlag flag) {
	InputManager::FlagsCompare(a, b, flag);
}


//==============================================================================================================
//				��̃L�[�ɑ΂��ĉ���������A�������u�ԁA�������u�ԁA�g�O���̃t���O���Ǘ�����
// 
// �������u�ԁipushdown)  : ���͂� 1 �őO��̃t���O�� 0 ������
// �������u�ԁipushup�j	  : ���͂� 0 �őO��̃t���O�� 1 ������
// �g�O���itoggle�j		  : ���͂ƑO��̃t���O���Ⴄ�Ȃ�
// ������Ă���ԁipress) : ���͂� 1 �ł������
//==============================================================================================================
void TestInputManager::InputFlagsControl(InputFlag flag, bool inputley)
{
	InputManager::InputFlagsControl(flag, inputley);
}

//=======================================================
//			�S�Ẵt���O���N���A
//=======================================================
void TestInputManager::ClearAll() {
	InputManager::ClearAll();
}

//=======================================================
//			�t���O���擾�i�K�v�ɉ����āj
//=======================================================
int TestInputManager::GetFlags(InputMode mode) const {
	if (InputManager::GetFlags(mode) == -1)
	{
		//�G���[
	}
}


