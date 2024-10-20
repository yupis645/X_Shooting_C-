#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include	"conioex.h" 
#include "Geometry.h"
#include "Game.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <array>
#include <iostream>
#include <vector>
#include <map>
#include "di.hpp"


namespace di = boost::di;

// ----------------------------------------------------------------
// �A�v�����ʂ̒�`
// ----------------------------------------------------------------


#define TestMode true			//�^�C�g����|�[�Y��ʂɑ���������o�� & �f�o�b�N���[�h���g�p�ł���悤�ɂȂ�B

// DebugOn �� StageRupe �� TestMode �L�����̂ݍ쓮����
#define DebugOn true			//TestMode��true�̎��̂ݎg�p�ł���f�o�b�N���[�h�̃t���O�Bfalse�ɂ���ƃf�o�b�N���[�h�ɓ���Ȃ��Ȃ�
#define StageRupe false			//true�Ȃ�w�肵���X�e�[�W���烋�[�v����Bfalse�Ȃ�{�X��|�����n�_�ŏI��
//�����܂�


//==============================================================
//					��ʊ֘A�̒�`
// 
//==============================================================
namespace ScreenConfig {
	constexpr int PXW = 1;		//�T�C�Y�䗦(����)
	constexpr int PXH = 1;		//�T�C�Y�䗦(����)
	constexpr int WIN_W = 200 * 3;	//(8*25*4)	//�E�B���h�E�T�C�Y(����)
	constexpr int WIN_H = 260 * 3;		//(8*25*3)	//�E�B���h�E�T�C�Y(�c��)
	constexpr int SRN_W = WIN_W / PXW;			//��ʃT�C�Y(����)
	constexpr int SRN_H = WIN_H / PXH;			//��ʃT�C�Y(����)
	constexpr int CENTER_X = SRN_W / 2;		//��ʂ̒���X���W
	constexpr int CENTER_Y = SRN_H / 2;		//��ʂ̒���Y���W
	constexpr int WORD_W = 8;					//1�����̉���
	constexpr int HALFWORD_W = 4;				//���p�����̉���
	constexpr int WORD_H = 15;				//1�����̍���
}

//==============================================================
//				���ID�F���݂̉�ʂ̏�Ԃ�\��
// 
//==============================================================
enum SceneID {
	TITLE = 1,     // �^�C�g��
	GAME = 2,      // �Q�[��
	RESULT = 3,    // ����
	OPTION = 4,    // �I�v�V����
	APP_EXIT = 999 // �A�v���I��
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//==============================================================
//					�}�b�v�֘A�̒�`
// 
//==============================================================
namespace MapConfig {
	constexpr int MAP_W = ScreenConfig::SRN_W / 31;	//�}�b�v�̃T�C�Y(��ʂ̑傫�� / �}�b�v�`�b�v�̃T�C�Y)	
	constexpr int MAP_H = ScreenConfig::SRN_H / 31;	//�}�b�v�̃T�C�Y(��ʂ̑傫�� / �}�b�v�`�b�v�̃T�C�Y)
	constexpr int CHIP_SIZE = 32;			//�}�b�v�`�b�v�̃T�C�Y(�����`)
	constexpr int SCROLL_SPEED = 1;		//�X�N���[���̃X�s�[�h
	constexpr int MAX_STAGE = 3;		//�X�e�[�W��
}
//==============================================================
//					���w
// 
//==============================================================
//#define ABS(num) ((num) > 0 ? (num) : -(num))		//�������O�����l��Ԃ�
//#define REPEAT(num,min,max) if(num > max){num = min;} else if(num < min){num = max;}		

template<typename T>
T ABS(T num) {
	return num > 0 ? num : -num;
}

template<typename T>
void Clamp(T & num, T min, T max) {
	if (num > max) {
		num = min;
	}
	else if (num < min) {
		num = max;
	}
}
//
//Vector2 LeftTopPos(Vector2 centerpos, int size) {
//	return Vector2(centerpos.x - (size / 2), centerpos.y - (size / 2));
//}
//


//==============================================================
//					�V�[���\����
//			�e��ʂŎg���ϐ����`����
// 
//==============================================================
class Scenestatus {
public :

	void FrameCountUpdate(int value) {
		framecount += value;
		if (framecount > 10000) framecount = 0;
	}

	void framecountReset() { framecount = 0; }
	int Getframecount() const { return framecount; }

	POINT Getcarsor()const { return carsor; }
	void movecarsor_x(LONG value, int min, int max) { carsor.x = carsorclamp(carsor.x + value,min , max); }
	void movecarsor_y(LONG value, int min, int max) { carsor.y = carsorclamp(carsor.y + value, min, max); }

	LONG carsorclamp(LONG value, int min, int max) {
		if (value < min) { return max; }
		else if (value > max) { return min; }

		return value;
	}

	bool SceneChangeSignal() { return currentsceneID != nextsceneID; }

	int Getcurrentscene()const { return currentsceneID; }
	void Setnextscene(int value) { nextsceneID = value; }
	int Getnextscene() { return nextsceneID; }
	
	
	
private:
	int framecount;
	int currentsceneID;
	int	nextsceneID;		//���̑J�ڐ�̉��ID
	POINT carsor;		//�J�[�\���̈ʒu

};



////
//class ParttitionMap {
//public:
//	bool drawFlag;
//	std::array<int, MapConfig::MAP_H* MapConfig::MAP_H > data;
//	int x, y;
//
//	ParttitionMap() : drawFlag(false), x(0), y(0), data({}) {}
//	~ParttitionMap() {}
//};
//
//// �}�b�v�f�[�^���Ǘ�����N���X
//class WholeMap {
//public:
//
//	int stage;
//	int currentparttition_num;
//	int x, y;
//	std::array<ParttitionMap, MapConfig::MAP_PARTITION_SUM> frontmap;
//	std::array<ParttitionMap, MapConfig::MAP_PARTITION_SUM> backmap;
//
//	Bmp* pics[MapConfig::MAP_PARTITION_SUM];
//	const wchar_t* filenames[MapConfig::MAP_PARTITION_SUM];
//
//	WholeMap() : stage(0), currentparttition_num(0), x(0), y(0) {}
//	~WholeMap() {}
//
//};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

													/*�ϐ��錾*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//��ʂ̒[�����̍��W�B��ʓ��ɉf���Ă��邩���肷��

			
extern bool DebugEnable;



#endif // GAME_DEFINITIONS_H