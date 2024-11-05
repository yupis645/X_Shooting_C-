
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

using InputFlag = IInputManager::InputFlag;

//=======================================================
//		�L�[���͂����邽�߂̃Z�b�g�A�b�v
//=======================================================
void TestInputManager::GetKeySetup()
{
	InputManager::GetKeySetup();	//�S�ẴL�[���́B
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


	DebugSwitch();
	DebugCreateA_Enemy();
	DebugCreateA_EnemyNumberUpdate();
	DebugCreateG_Enemy();
	DebugCreateG_EnemyNumberUpdate();
	DebugCreateEnemyShot();


	return 0;
}

//=======================================================
//		�����L�[�̓��͂�Vector2�ŕԂ�
// 
// �l�̑傫����'1'
//=======================================================
Vector2 TestInputManager::Dirctionkeyinput(InputMode mode)
{
	return InputManager::Dirctionkeyinput(mode);


}


//==============================================================================================================
//						�����L�[�̓��͂�0�`1�̊Ԃ�float�l�ŊǗ�����
//  
// ��O������1�t���[���ɑ�������l�ŁA���͂����m��������͕����ɂ���Ă��̒l�𑝌�������
//==============================================================================================================
Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	return InputManager::DirctionkeyinputAxis(x_value, y_value, maxspeed);
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
	return InputManager::SetFlag(flag, mode);
}

//=======================================================
//			�t���O�̉����i�r�b�gAND NOT�j
//=======================================================
void TestInputManager::ClearFlag(InputFlag flag, InputMode mode) {
	return InputManager::ClearFlag(flag, mode);
}

//=======================================================
//			 �t���O�̃g�O���i�r�b�gXOR�j
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	return InputManager::ToggleFlag(flag);

	
}

//=======================================================
//			�t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
//=======================================================
bool TestInputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
	return InputManager::IsFlagSet(flag, mode);
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
//											�������u��
// 
// �������u�ԁipushdown)  : ���͂� 1 �őO��̃t���O�� 0 ������
//==============================================================================================================

void TestInputManager::DebugInputFlagsControl(DebugInputFlag flag, bool inputley)
{
	bool toggle = inputley != DebugIsFlagSet(flag);	//press��O��̓��͂Ƃ��Ďg���A���݂̓��͂Ɣ�r����

	int bit = static_cast<int>(flag);


	// �������u�ԁipushdown�j
	if (inputley && toggle) debugtriggerFlags |= bit;
	else					debugtriggerFlags &= ~bit;
}


//=======================================================
//			�t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
//=======================================================

bool TestInputManager::DebugIsFlagSet(DebugInputFlag flag) const {
	int bit = static_cast<int>(flag);

	return (debugtriggerFlags & bit) != 0;

}