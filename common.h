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

namespace SceneConfig {
	constexpr int FRAME_COUNT_VALUE = 1;		//�t���[���J�E���g����ۂ�1�t���[���ŉ��Z����l

}


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
//					PNG�f�[�^�֘A
// 
//==============================================================
struct TextureConfig {
	int width;   // 1�̃X���C�X�̉���
	int height;  // 1�̃X���C�X�̏c��
	int rows;    // �s��
	int columns; // ��
	int startindex;
	int indexcount;
};

namespace TextureConfigs {
	constexpr TextureConfig TITLE			{ 198, 58,  1,  1, 0, 1};
	constexpr TextureConfig PLAYER			{  32, 32,  6,  2, 2, 3};
	constexpr TextureConfig TARGETSIGHT		{  32, 32,  6,  2, 0, 2};
	constexpr TextureConfig BULLET			{  8, 8,  3,  1, 0, 2};
	constexpr TextureConfig BOM				{  8, 8,  3,  1, 2, 1};
	constexpr TextureConfig BOSS			{  32, 32, 11, 11, 0, 11*11};
	constexpr TextureConfig BOSSALGO		{  32, 32,  5,  1, 0, 1};
	constexpr TextureConfig COMMON_BOMBER	{  47, 47,  6,  1, 0, 6};
	constexpr TextureConfig AIR_ENEMYBOMBER	{  47, 47,  6,  1, 6, 6};
	constexpr TextureConfig MAP				{  32, 32, 12, 10, 0, 12*10 };

	constexpr TextureConfig TOROID		{ 32, 32, 8, 1 , 0, 8};
	constexpr TextureConfig TORKAN		{ 32, 32, 8, 1 , 8, 7};
	constexpr TextureConfig GIDDOSPARIO	{ 32, 32, 8, 1 ,16, 8};
	constexpr TextureConfig ZOSHI		{ 32, 32, 8, 1 ,24, 4};
	constexpr TextureConfig JARA		{ 32, 32, 8, 1 ,32, 6};
	constexpr TextureConfig KAPI		{ 32, 32, 8, 1 ,40, 7};
	constexpr TextureConfig TERRAZI		{ 32, 32, 8, 1 ,48, 7};
	constexpr TextureConfig ZAKATO		{ 32, 32, 8, 1 ,56, 1};
	constexpr TextureConfig BRAGZAKATO	{ 32, 32, 8, 1 ,64, 1};
	constexpr TextureConfig GARUZAKATO	{ 32, 32, 8, 1 ,72, 1};
	constexpr TextureConfig BACURA		{ 48, 48, 8, 1 ,56, 8};
	
	constexpr TextureConfig BARRA		{ 32, 32, 4, 1 ,0,  2};
	constexpr TextureConfig ZOLBAK		{ 32, 32, 4, 1 ,4,  4};
	constexpr TextureConfig LOGRAM		{ 32, 32, 4, 1 ,8,  4};
	constexpr TextureConfig DOMOGRAM	{ 32, 32, 4, 1 ,12, 4};
	constexpr TextureConfig DEROTA		{ 32, 32, 4, 1 ,16, 4};
	constexpr TextureConfig GROBDA		{ 32, 32, 4, 1 ,20, 4};
	constexpr TextureConfig BOZALOGRAM	{ 32, 32, 4, 1 ,24, 1};
	constexpr TextureConfig SOL			{ 32, 32, 4, 1 ,28, 4};
	constexpr TextureConfig GARUBARRA	{ 64, 64, 4, 1 ,20, 1};
	constexpr TextureConfig GARUDEROTA	{ 64, 64, 4, 1 ,24, 4};
	constexpr TextureConfig ALGO		{ 48, 48, 4, 1 , 0, 4};
	constexpr TextureConfig AD_CORE		{ 64, 64, 4, 1 , 0, 1};
	constexpr TextureConfig SPFLAG		{ 32, 32, 4, 1 , 3, 1};
	
}

namespace EnemyTextureConfig {
	constexpr int S_SIZE_SLICE_WIDTH = 32;      // 1�̃X���C�X�̉���
	constexpr int S_SIZE_SLICE_HEIGHT = 32;     // 1�̃X���C�X�̏c��
	constexpr int M_SIZE_SLICE_WIDTH = 48;      // 1�̃X���C�X�̉���
	constexpr int M_SIZE_SLICE_HEIGHT = 48;     // 1�̃X���C�X�̏c��
	constexpr int L_SIZE_SLICE_WIDTH = 64;      // 1�̃X���C�X�̉���
	constexpr int L_SIZE_SLICE_HEIGHT = 64;     // 1�̃X���C�X�̏c��
	constexpr int AIR_ENEMY_SLICE_ROWS_MAX = 8;          // �s��
	constexpr int GROUND_ENEMY_SLICE_ROWS_MAX = 4;          // �s��
	constexpr int SLICE_COLUMNS = 1;       // ��
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