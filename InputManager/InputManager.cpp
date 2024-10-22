
//----------------------------------------------------------------------------------------------------
//                              ���͂��Ǘ�����N���X
// 
// ���͂��Ǘ�����N���X
// �����L�[�AZ�L�[�AX�L�[�AEnter�L�[�AESC�L�[�Ȃǂ̓��͂ɉ����ăt���O��ON/OFF����
// GameManager��InputReception�֐�����x�������΁A���̎��̓��͂ɉ����ăt���O���؂�ւ��B
//		���̂��߁A���̃N���X��IsFlagSet�Ŋm�F�������t���O���w�肵��bool�̕Ԃ�l�œ��̗͂L�����킩��
//----------------------------------------------------------------------------------------------------

#include "InputManager.h"
#include "conioex.h"
#include "Geometry.h"
#include "Game.h"



//=======================================================
//		�L�[���͂����邽�߂̃Z�b�g�A�b�v
//=======================================================
void InputManager::GetKeySetup()
{
	GetKeyAll();	//�S�ẴL�[���́B
}

//=======================================================
//			���͂ɑ΂���flags���Z�b�g����
// 
// �֐��̏��߂ɑO��̓��̓t���O��S�ď���������
// active��false�Ȃ���͂��󂯕t�����A�֐����I������
//=======================================================
int InputManager::InputReception()
{
	if (active == false) return 1;		//����active��false�Ȃ���͂��󂯕t�����I������

	GetKeySetup();	//�L�[���͂̏���

	//�L�[�̓��͎�t
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

	directionkeyaxis = DirctionkeyinputAxis(0.01f, 0.01f,1);

	directionkeyaxis = DirctionkeyinputAxis(0.01f, 0.01f, 1);

	//�e�X�g���[�h�L�����̂ݍ�p
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
Vector2 InputManager::Dirctionkeyinput(InputMode mode)
{
	Vector2 vec = Vector2::zero;
	
	if (IsFlagSet(InputFlag::left, InputMode::press))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::press)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::press))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::press))  vec.y += 1;

	if (IsFlagSet(InputFlag::left, InputMode::pushdown))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::pushdown)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::pushdown))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::pushdown))  vec.y += 1;

	if (IsFlagSet(InputFlag::left, InputMode::pushup))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::pushup)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::pushup))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::pushup))  vec.y += 1;

	if (IsFlagSet(InputFlag::left, InputMode::toggle))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::toggle)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::toggle))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::toggle))  vec.y += 1;


	

	return vec;
}


//==============================================================================================================
//						�����L�[�̓��͂�0�`1�̊Ԃ�float�l�ŊǗ�����
//  
// ��O������1�t���[���ɑ�������l�ŁA���͂����m��������͕����ɂ���Ă��̒l�𑝌�������
//==============================================================================================================
Vector2 InputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	// �������F�L�[���͂Ɋ�Â������x�N�g��
	Vector2 empty = directionkeyaxis;

	// �������������_�F�w���臒l�ȉ��Ȃ�0�ɕ␳
	auto zerooffset = [](float value , float minvalue) { return (std::abs(value) < minvalue) ? 0.0f : value * 0.9f; };

	bool left = IsFlagSet(InputFlag::left, InputMode::press);
	bool right = IsFlagSet(InputFlag::right, InputMode::press);
	bool up = IsFlagSet(InputFlag::up, InputMode::press);
	bool down = IsFlagSet(InputFlag::down, InputMode::press);

	// X���̏���
	if (left)			empty.x -= x_value;							//x���������ɂ����悤��y_value���Z����
	if (right)			empty.x += x_value;							//x���E�����ɂ����悤��x_value���Z����									
	if(!left && !right)	empty.x = zerooffset(empty.x, x_value);		// ���삪�Ȃ��ꍇ�̌�������
	

	// Y���̏���
	if (up)				empty.y -= y_value;										//y��������ɂ����悤��y_value���Z����
	if (down)			empty.y += y_value;										//y���������ɂ����悤��y_Value�����Z����
	if(!up && !down)	empty.y = zerooffset(empty.y,y_value); // ���삪�Ȃ��ꍇ�̌�������
	

	// �ő呬�x�̐���
	if (std::abs(empty.x) > maxspeed)	empty.x = (empty.x > 0 ? 1 : -1) * maxspeed;
	if (std::abs(empty.y) > maxspeed) 	empty.y = (empty.y > 0 ? 1 : -1) * maxspeed;

	return empty;
}

//=======================================================
//			����������
//=======================================================
void InputManager::left()
{
	InputManager::InputFlagsControl(InputFlag::left, ChkKeyPress(PK_LEFT));
}

//=======================================================
//			�E��������
//=======================================================
void InputManager::right()
{
	InputManager::InputFlagsControl(InputFlag::right, ChkKeyPress(PK_RIGHT));
}

//=======================================================
//			���������
//=======================================================
void InputManager::up()
{
	InputManager::InputFlagsControl(InputFlag::up, ChkKeyPress(PK_UP));

}
//=======================================================
//			����������
//=======================================================
void InputManager::down()
{
	InputManager::InputFlagsControl(InputFlag::down, ChkKeyPress(PK_DOWN));
}
//=======================================================
//				�Z���N�g�{�^��
//=======================================================
void  InputManager::select()
{
	bool input = ChkKeyEdge(VK_RETURN) || ChkKeyEdge(PK_Z);

	InputManager::InputFlagsControl(InputFlag::select, input);
}

//=======================================================
//			�L�����Z���{�^��
//=======================================================
void  InputManager::cancel()
{
	InputManager::InputFlagsControl(InputFlag::cancel, ChkKeyPress(PK_X));
}

//=======================================================
//			ESC(�Q�[���̏I��)
//=======================================================	
void  InputManager::esc()
{
	InputManager::InputFlagsControl(InputFlag::esc, ChkKeyPress(VK_ESCAPE));
}
//=======================================================
//			�V���b�g�̔���
//=======================================================
void  InputManager::shot()
{

	InputManager::InputFlagsControl(InputFlag::shot, ChkKeyPress(PK_Z));
}
//=======================================================
//				�{������
//=======================================================
void  InputManager::bom()
{

	InputManager::InputFlagsControl(InputFlag::bom, ChkKeyPress(PK_X));
}

//=======================================================
//				�|�[�Y(�ꎞ��~)
//=======================================================
void  InputManager::pose()
{
	InputManager::InputFlagsControl(InputFlag::pose, ChkKeyPress(PK_SP));
}

/////--------------------------------------------------------------------------------------------------------------

//=======================================================
//			�t���O�̐ݒ�i�r�b�gOR�j
//=======================================================
void InputManager::SetFlag(InputFlag flag, InputMode mode) {
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
		toggleFlags ^= bit;  // �g�O����Ԃ̔��]
		break;
	}
}

//=======================================================
//			�t���O�̉����i�r�b�gAND NOT�j
//=======================================================
void InputManager::ClearFlag(InputFlag flag, InputMode mode) {
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
//			 �t���O�̃g�O���i�r�b�gXOR�j
//=======================================================
void InputManager::ToggleFlag(InputFlag flag) {
	toggleFlags ^= static_cast<int>(flag);
}

//=======================================================
//			�t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
//=======================================================
bool InputManager::IsFlagSet(InputFlag flag, InputMode mode) const {
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
//�r�b�g���m�Ŕ�r
//=======================================================
inline bool InputManager::FlagsCompare(int a, int b, InputFlag flag) {
	return ((a & static_cast<int>(flag)) != 0) == ((b & static_cast<int>(flag)) != 0);
}


//==============================================================================================================
//				��̃L�[�ɑ΂��ĉ���������A�������u�ԁA�������u�ԁA�g�O���̃t���O���Ǘ�����
// 
// �������u�ԁipushdown)  : ���͂� 1 �őO��̃t���O�� 0 ������
// �������u�ԁipushup�j	  : ���͂� 0 �őO��̃t���O�� 1 ������
// �g�O���itoggle�j		  : ���͂ƑO��̃t���O���Ⴄ�Ȃ�
// ������Ă���ԁipress) : ���͂� 1 �ł������
//==============================================================================================================
void InputManager::InputFlagsControl(InputFlag flag, bool inputley)
{
	bool toggle = inputley != IsFlagSet(flag, InputMode::press);	//press��O��̓��͂Ƃ��Ďg���A���݂̓��͂Ɣ�r����


	// �������u�ԁipushdown�j
	if (inputley && toggle) SetFlag(flag, InputMode::pushdown);
	else					ClearFlag(flag, InputMode::pushdown);

	// �������u�ԁipushup�j
	if (!inputley && toggle)SetFlag(flag, InputMode::pushup);
	else					ClearFlag(flag, InputMode::pushup);

	// �g�O���itoggle�j
	if (!inputley && toggle) {  // �������Ƃ��Ƀg�O����؂�ւ�
		ToggleFlag(flag);
	}

	// ������Ă���ԁipress�j
	if (inputley)	SetFlag(flag, InputMode::press);
	else			ClearFlag(flag, InputMode::press);
}

//=======================================================
//			�S�Ẵt���O���N���A
//=======================================================
void InputManager::ClearAll() {
	pressFlags = 0;
}

//=======================================================
//			�t���O���擾�i�K�v�ɉ����āj
//=======================================================
int InputManager::GetFlags(InputMode mode) const {

	if (mode == InputMode::pushdown)	return triggerFlags;
	if (mode == InputMode::pushup)		return releaseFlags;
	if (mode == InputMode::press)		return pressFlags;
	if (mode == InputMode::toggle)		return toggleFlags;

	return -1;
}


