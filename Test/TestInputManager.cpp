#include "TestInputManager.h"
#include "conioex.h"
#include "Geometry.h"
#include "common.h"

void TestInputManager::InputPritf()
{
	/*printf("left   = %s \n ", IsFlagSet(InputFlag::left) ? "true" : "false");
	printf("right  = %s \n ", IsFlagSet(InputFlag::right) ? "true" : "false");
	printf("down   = %s \n ", IsFlagSet(InputFlag::down) ? "true" : "false");
	printf("up     = %s \n ", IsFlagSet(InputFlag::up) ? "true" : "false");
	printf("select = %s \n ", IsFlagSet(InputFlag::select) ? "true" : "false");
	printf("cancel = %s \n ", IsFlagSet(InputFlag::cancel) ? "true" : "false");
	printf("pose   = %s \n ", IsFlagSet(InputFlag::pose) ? "true" : "false");
	printf("shot   = %s \n ", IsFlagSet(InputFlag::shot) ? "true" : "false");
	printf("bom	   = %s \n ", IsFlagSet(InputFlag::bom) ? "true" : "false");
	printf("esc    = %s \n ", IsFlagSet(InputFlag::esc) ? "true" : "false");*/

	auto is = [this](InputFlag flag,InputMode mode) { return IsFlagSet(flag, mode); };
	auto f = [this, is](InputFlag flag, InputMode mode) {return is(flag, mode) ? "true" : "false";};


	WriteTextFA(0, ScreenConfig::SRN_H - (ScreenConfig::WORD_H * 28), 0,
		"		GetAxis ( %f , %f )", this->GetAxis().x, this->GetAxis().y);
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
	//ClearAll();						//inputflags������������
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


	InputPritf();
	directionkeyaxis = DirctionkeyinputAxis(0.01f, 0.01, 1);

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
Vector2 TestInputManager::Dirctionkeyinput(InputMode mode)
{
	Vector2 vec = Vector2::zero;


	if (IsFlagSet(InputFlag::left, InputMode::press))  vec.x -= 1;
	if (IsFlagSet(InputFlag::right, InputMode::press)) vec.x += 1;
	if (IsFlagSet(InputFlag::up, InputMode::press))    vec.y -= 1;
	if (IsFlagSet(InputFlag::down, InputMode::press))  vec.y += 1;


	return vec;
}

Vector2 TestInputManager::DirctionkeyinputAxis(float x_value, float y_value, float maxspeed) {
	// �������F�L�[���͂Ɋ�Â������x�N�g��
	Vector2 empty = directionkeyaxis;

	// �������������_�F�w���臒l�ȉ��Ȃ�0�ɕ␳
	auto zerooffset = [](float value, float minvalue) { return (std::abs(value) < minvalue) ? 0.0f : value * 0.9f; };

	bool left = IsFlagSet(InputFlag::left, InputMode::press);
	bool right = IsFlagSet(InputFlag::right, InputMode::press);
	bool up = IsFlagSet(InputFlag::up, InputMode::press);
	bool down = IsFlagSet(InputFlag::down, InputMode::press);

	// X���̏���
	if (left)			empty.x -= x_value;							//x���������ɂ����悤��y_value���Z����
	if (right)			empty.x += x_value;							//x���E�����ɂ����悤��x_value���Z����									
	if (!left && !right)	empty.x = zerooffset(empty.x, x_value);		// ���삪�Ȃ��ꍇ�̌�������


	// Y���̏���
	if (up)				empty.y -= y_value;										//y��������ɂ����悤��y_value���Z����
	if (down)			empty.y += y_value;										//y���������ɂ����悤��y_Value�����Z����
	if (!up && !down)	empty.y = zerooffset(empty.y, y_value); // ���삪�Ȃ��ꍇ�̌�������


	// �ő呬�x�̐���
	if (std::abs(empty.x) > maxspeed)	empty.x = (empty.x > 0 ? 1 : -1) * maxspeed;
	if (std::abs(empty.y) > maxspeed) 	empty.y = (empty.y > 0 ? 1 : -1) * maxspeed;

	return empty;
}

//=======================================================
//			����������
//=======================================================
void TestInputManager::left()
{
	TestInputManager::InputFlagsControl(InputFlag::left, ChkKeyPress(PK_LEFT));
}

//=======================================================
//			�E��������
//=======================================================
void TestInputManager::right()
{
	TestInputManager::InputFlagsControl(InputFlag::right, ChkKeyPress(PK_RIGHT));
}

//=======================================================
//			���������
//=======================================================
void TestInputManager::up()
{
	TestInputManager::InputFlagsControl(InputFlag::up, ChkKeyPress(PK_UP));

}
//=======================================================
//			����������
//=======================================================
void TestInputManager::down()
{
	TestInputManager::InputFlagsControl(InputFlag::down, ChkKeyPress(PK_DOWN));
}
//=======================================================
//				�Z���N�g�{�^��
//=======================================================
void  TestInputManager::select()
{
	bool input = ChkKeyEdge(VK_RETURN) || ChkKeyEdge(PK_Z);

	TestInputManager::InputFlagsControl(InputFlag::select, input);
}

//=======================================================
//			�L�����Z���{�^��
//=======================================================
void  TestInputManager::cancel()
{
	TestInputManager::InputFlagsControl(InputFlag::cancel, ChkKeyPress(PK_X));
}

//=======================================================
//			ESC(�Q�[���̏I��)
//=======================================================	
void  TestInputManager::esc()
{
	TestInputManager::InputFlagsControl(InputFlag::esc, ChkKeyPress(VK_ESCAPE));
}
//=======================================================
//			�V���b�g�̔���
//=======================================================
void  TestInputManager::shot()
{

	TestInputManager::InputFlagsControl(InputFlag::shot, ChkKeyPress(PK_Z));
}
//=======================================================
//				�{������
//=======================================================
void  TestInputManager::bom()
{

	TestInputManager::InputFlagsControl(InputFlag::bom, ChkKeyPress(PK_X));
}

//=======================================================
//				�|�[�Y(�ꎞ��~)
//=======================================================
void  TestInputManager::pose()
{
	TestInputManager::InputFlagsControl(InputFlag::pose, ChkKeyPress(PK_SP));
}

/////--------------------------------------------------------------------------------------------------------------

//=======================================================
//			�t���O�̐ݒ�i�r�b�gOR�j
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
		toggleFlags ^= bit;  // �g�O����Ԃ̔��]
		break;
	}
}

//=======================================================
//			�t���O�̉����i�r�b�gAND NOT�j
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
//			 �t���O�̃g�O���i�r�b�gXOR�j
//=======================================================
void TestInputManager::ToggleFlag(InputFlag flag) {
	toggleFlags ^= static_cast<int>(flag);
}

//=======================================================
//			�t���O���ݒ肳��Ă��邩�m�F�i�r�b�gAND�j
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
//�r�b�g���m�Ŕ�r
//=======================================================
inline bool TestInputManager::FlagsCompare(int a, int b, InputFlag flag) {
	return ((a & static_cast<int>(flag)) != 0) == ((b & static_cast<int>(flag)) != 0);
}

void TestInputManager::InputFlagsControl(InputFlag flag, bool inputley)
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
void TestInputManager::ClearAll() {
	pressFlags = 0;
}

//=======================================================
//			�t���O���擾�i�K�v�ɉ����āj
//=======================================================
int TestInputManager::GetFlags(InputMode mode) const {

	if (mode == InputMode::pushdown)	return triggerFlags;
	if (mode == InputMode::pushup)		return releaseFlags;
	if (mode == InputMode::press)		return pressFlags;
	if (mode == InputMode::toggle)		return toggleFlags;

	return -1;
}


