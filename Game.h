#ifndef GAME_H
#define GAME_H

#include "common.h"
//#include "commonutility.h"
#include "Geometry.h"
//#include "Player.h"
#include <array>
#include <map>
#include <vector>

//-------------------------------------------------------------------------------------------
//			Game�Ŏg���\���̂�v���g�^�C�v�錾�����Ă���
// 
//�\���̂� �E�v���C���[ �E�󒆓G �E�n��G �E�{�X�@�E�}�b�v �E�e��摜�f�[�^ �Ȃ�
// �v���g�^�C�v�錾�� �Q�[�����[�v,�e�I�u�W�F�N�g�̏������A�����A�X�V�A�`��
//-------------------------------------------------------------------------------------------


//==============================================================
//					/*�v���C���[�֌W�̒�`*/
// 
//==============================================================

namespace PlayerConfig {
	constexpr int SPEED = 5;		//�v���C���[�̈ړ����x	
	constexpr int PLAYER_HITBOX_SIZE = 16;		//�摜�̃T�C�Y
	constexpr int PLAYER_PIC_SIZE = 32;		//�摜�̃T�C�Y

	constexpr int SIGHT_HITBOX_SIZE = 32;		//�摜�̃T�C�Y
	constexpr int SIGHT_PIC_SIZE = 32;			//�摜�̃T�C�Y

	constexpr int MAX_SHOT = 3;		//��ʓ��ɕ\���ł���V���b�g�̐�
	constexpr int SHOT_SPEED = 20;	//�V���b�g�̒e��
	constexpr int SHOT_HITBOX_SIZE = 8;		//�摜�̃T�C�Y
	constexpr int SHOT_PIC_SIZE = 8;		//�摜�̃T�C�Y

	constexpr int BOM_SPEED = 5;		//�V���b�g�̒e��
	constexpr int BOM_RANGE = 100;		//�{���̎˒�����
	constexpr int BUNBER_HITBOX_SIZE = 24;		//�摜�̃T�C�Y
	constexpr int BON_PIC_SIZE = 8;		//�摜�̃T�C�Y
}
//==============================================================
//					/*�G�l�~�[���ʂ̒�`*/
// 
//==============================================================
namespace AirEnemyConfig {
	constexpr int PIC_LINE_WIDE = 8;		//�󒆓G�̉摜�̍s�̐�
	constexpr int MAX_ENEMY = 20;			//�G�̍ő�o����( �󒆂ƒn��͕ʃJ�E���g)
}
namespace GroundEnemyConfig {
	constexpr int PIC_LINE_WIDE = 4;		//�󒆓G�̉摜�̍s�̐�
	constexpr int MAX_ENEMY = 20;			//�G�̍ő�o����( �󒆂ƒn��͕ʃJ�E���g)
}
namespace EnemyShotConfig {
	constexpr int SPEED = 4;			//�G�e�̊�{�̑��x
	constexpr int MAX_SHOT = 17;			//�G�e�̊�{�̑��x

}
constexpr int MAX_LEVEL	= 64;			//�G�̏o�����x���̏��

constexpr int BOMBER_PIC_SIZE = 47;			//�G�̏o�����x���̏��


//============================================
//�{�X & �C��A�R�A�̃X�e�[�^�X
//============================================
//typedef struct BOSS {
//	bool F;				//�o���t���O
//	bool down;			//���Ĕ���(�R�A�j��)
//	ENEMY_ST enemy[5];	//�C��~4�ƃR�A�̏��
//	float center_x;		//x�����S���W
//	float center_y;		//y�����S���W
//	int pic_x;			//����x���W(�X�v���C�g�p)
//	int pic_y;			//����y���W(�X�v���C�g�p)
//
//	Bmp* pic[120];				//�{�̂𕪊������X�v���C�g
//	Bmp* pats[5];				//���j�O�̖C��ƃR�A�̉摜
//}BOSS;

//============================================
//�f�o�b�N�p�̍\����
//============================================
struct DenugState {
	bool G_enemy_stop;
	bool A_enemy_stop;
	bool Player_invalid;
};



/////-------------------------------------------------------------

// �G�摜�̃C���f�b�N�X��`
enum Air_EnemyType {
	TOROID = 0,
	TORKAN,
	GIDDOSPARIO,
	ZOSHI,
	JARA,
	KAPI,
	TERRAZI,
	ZAKATO,
	BRAGZAKATO,
	GARUZAKATO,
	BACURA,
	A_ENEMY_SUMS		// �G�̑���
};
enum Ground_EnemyType {
	BARRA = 0,
	ZOLBAK,
	LOGRAM,
	DOMOGRAM,
	DEROTA,
	GROBDA,
	BOZALOGRAM,
	SOL,
	GARUBARRA,
	GARUDEROTA,
	AG_ALG,
	AG_CORE,
	SPECIALFLAG,
	G_ENEMY_SUMS // �G�̑���
};


enum GameModeStateNumber {
	Title = 0,
	Game,
	Option,
	Result,
	GameEnd = 99,

};

//============================================
//  �󒆁A�n�㋤�ʂ̃X�e�[�^�X
//============================================
typedef struct ENEMY_DATA {
	int number;			//�G�l�~�[�̎�ނ���ʂ��邽�߂̔ԍ�
	int hitbox_size;	//�����蔻��̃T�C�Y
	int pic_size;		//�摜�T�C�Y
	int type;		//����̂̈Ⴄ����
	int dir;		//����
	int anim;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	int anim_sum;	//�s���p�^�[���̐�
	int points;		//�|�C���g
	float speed;	//�ړ����x
	float acc;		//�����x
}ENEMY_DATA;





//==============================================================================================
//					�S�̃V�[���Ŏg�p����f�[�^
// 
// �EGame�ŉ��Z����A���U���g�ŕ\������score
// �E�^�C�g����ʂ�1Player��2Player�ǂ��炩��I�Ԃ��ŏ����l���ς��life
//==============================================================================================
class GameStatus {
public:
	GameStatus():Score(0), Life(0) {};
	~GameStatus() {}
	// �X�R�A�̃Q�b�^�[�ƃZ�b�^�[
	int score() const { return Score; }
	void score(int s) { Score = s; }
	// ���C�t�̃Q�b�^�[�ƃZ�b�^�[
	int life() const { return Life; }
	void life(int l) { Life = l; }

private:
	int Score;
	int Life;
};
//==============================================================================================
//					instance�Ƃ��đ��݂���I�u�W�F�N�g�̊��N���X
//==============================================================================================
class GameObject {
public:
	GameObject(): position(0, 0),hitbox(0,0,0,0),active(false) {
		// ���ʂ̏���������
	}

	virtual void InitClear() {
		 position = Vector2::zero;
		 hitbox = Boxcollider::zero;
	}

	virtual Vector2 GetPosition()const {	return position;	}
	virtual void SetPosition(Vector2 pos){	position = pos;	}

	virtual Boxcollider GetHitbox()const {	return hitbox;	}
	virtual void SetHitbox(Boxcollider box){hitbox = box;	}

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	virtual ~GameObject() {}

protected :
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};

class EnemyStatusData {
public:
	EnemyStatusData(int num = 0,int hsize = 0,int psize = 0,int t = 0,int a_num = 0,int a_sum = 0,int p = 0,float sp = 0,float ac = 0) :
		number(num), hitbox_size(hsize), pic_size(psize), type(t), anim_number(a_num), anim_sum(a_sum), points(p), speed(sp), acceleration(ac) {}
	~EnemyStatusData() {}

	virtual int Init()
	{
		number = 0; 
		hitbox_size = 0;
		pic_size = 0;
		type = 0;
		anim_number = 0;
		anim_sum = 0; 
		points = 0;
		speed = 0; 
		acceleration = 0;

		return 0;
	}

	//�f�[�^��A = B�̌`�ő���ł���悤�ɂ��������Z�q
	EnemyStatusData& operator=(const EnemyStatusData& set) {
		if (this != &set) {  // ���ȑ����h��
			this->number = set.number;
			this->hitbox_size = set.hitbox_size;
			this->pic_size = set.pic_size;
			this->type = set.type;
			this->anim_number = set.anim_number;
			this->anim_sum = set.anim_sum;
			this->points = set.points;
			this->speed = set.speed;
			this->acceleration = set.acceleration;
		}
		return *this;		//�l��������������Ԃ�
	}

	int number;			//�G�l�~�[�̎�ނ���ʂ��邽�߂̔ԍ�
	int hitbox_size;	//�����蔻��̃T�C�Y
	int pic_size;		//�摜�T�C�Y
	int type;		//����̂̈Ⴄ����
	int anim_number;		//�s���p�^�[���ԍ�
	int anim_sum;	//�s���p�^�[���̐�
	int points;		//�|�C���g
	float speed;	//�ړ����x
	float acceleration;		//�����x
};

// �G�f�[�^�̔z��
const std::array<EnemyStatusData, 11> A_ENEMY_DATA_ARRAY = {
	EnemyStatusData(0 , 32, 32, 1,  0, 8,   30, 2.0f, 0.04f),  // �g�[���C�h
	EnemyStatusData(1 , 32, 32, 0,  8, 7,   50, 4.0f, 0.0f),   // �^���P��
	EnemyStatusData(2 , 16, 32, 0, 16, 8,   10, 7.0f, 0.0f),  // �M�h�X�p���I
	EnemyStatusData(3 , 32, 32, 2, 24, 4,   70, 3.0f, 0.0f),  // �]�V�[
	EnemyStatusData(4 , 32, 32, 0, 32, 6,  150, 4.0f, 0.04f),// �W�A��
	EnemyStatusData(5 , 32, 32, 0, 40, 7,  300, 4.0f, 0.15f),// �J�s
	EnemyStatusData(6 , 32, 32, 0, 48, 7,  700, 5.0f, 0.08f),// �e���W
	EnemyStatusData(7 , 16, 32, 3, 56, 1,  100, 3.0f, 0.0f), // �U�J�[�g
	EnemyStatusData(8 , 16, 32, 3, 64, 1,  600, 3.0f, 0.0f), // �u���O�U�J�[�g
	EnemyStatusData(9 , 16, 32, 0, 72, 1, 1000, 3.0f, 0.0f),// �K���U�J�[�g
	EnemyStatusData(10, 48, 48, 0, 56, 8,    0, 2.0f, 0.0f)   // �o�L����
};

const std::array<EnemyStatusData, 13> G_ENEMY_DATA_ARRAY = {
	EnemyStatusData(50, 32, 32, 0,  1, 1,  100, 0.0f , 0.0f),      // �o�[��
	EnemyStatusData(51, 32, 32, 0,  4, 4,  200, 0.0f , 0.0f),      // �]���o�O
	EnemyStatusData(52, 32, 32, 4,  8, 4,  300, 0.0f , 0.0f),      // ���O����
	EnemyStatusData(53, 32, 32, 0, 12, 4,  800, 0.75f, 0.5f),   // �h���O����
	EnemyStatusData(54, 32, 32, 0, 16, 4,  200, 0.0f , 0.0f),		    // �f���[�_
	EnemyStatusData(55, 32, 32, 8, 20, 4,  200, 0.5f , 0.5f),   // �O���u�_�[
	EnemyStatusData(56, 32, 32, 0, 24, 1,  600, 0.0f , 0.0f),      // �{�U���O����
	EnemyStatusData(57, 32, 32, 0, 28, 4, 2000, 0.0f , 0.0f),      // �\��
	EnemyStatusData(58, 32, 63, 0, 20, 1,  300, 0.0f , 0.0f),      // �K���o�[��
	EnemyStatusData(59, 32, 64, 0, 24, 4, 2000, 0.0f , 0.0f),      // �K���f���[�^
	EnemyStatusData(60, 16, 48, 0,  4, 0, 1000, 0.0f , 0.0f),      // �A���S
	EnemyStatusData(61, 32, 64, 0,  4, 1, 4000, 0.0f , 0.0f),      // A/G�R�A
	EnemyStatusData(62, 32, 32, 0,  3, 1, 1000, 0.0f , 0.0f)       // SP�t���b�O
};

// �G�̉摜�f�[�^�Ǘ��p�̃}�b�v
//std::map<int, std::vector<Bmp*>> ImageManager::air_enemy;
//std::map<int, std::vector<Bmp*>> ImageManager::ground_enemy;

//
//// �摜�f�[�^�̍\����
//struct PNGDATA {
//	const wchar_t* Title;
//	const wchar_t* Player;
//	const wchar_t* Shot;
//	const wchar_t* A_Enemy;
//	const wchar_t* G_Enemy;
//	const wchar_t* Boss;
//	const wchar_t* BossSub;
//	const wchar_t* bomber;
//	const wchar_t* Map;
//};
//
//class ImageManager {
//public:
//	// �v���C���[��e�̉摜
//	static Bmp* Title;
//	static Bmp* player[12];
//	static Bmp* bullet[3];
//	static Bmp* boss[120];
//	static Bmp* bosspats[5];
//
//	static Bmp* PlayerBomber[6];
//	static Bmp* EnemyBomber[6];
//
//	// �󒆂ƒn��̓G�摜�� map �ŊǗ�
//	static std::map<int, std::vector<Bmp*>> air_enemy;
//	static std::map<int, std::vector<Bmp*>> ground_enemy;
//
//	// PNG�f�[�^���Ǘ�����\���̂̃C���X�^���X
//	static PNGDATA PngData;
//
//	ImageManager() {}
//	~ImageManager() {}
//
//	// �������֐�
//	static void Init() {
//		// �v���C���[�摜�̃��[�h
//		LoadDivBmp(PngData.Player, 0, 0, PlayerConfig::PIC_SIZE, PlayerConfig::PIC_SIZE, 6, 2, player);
//		LoadDivBmp(PngData.Shot, 0, 0, PlayerShotConfig::PIC_SIZE, PlayerShotConfig::PIC_SIZE, 3, 1, bullet);
//
//		// �󒆓G�̉摜�̃��[�h
//		for (int i = 0; i < A_ENEMY_SUMS; i++) {
//			std::vector<Bmp*> enemyPics(AirEnemyConfig::PIC_LINE_WIDE * 11);
//			LoadDivBmp(PngData.A_Enemy, 0, 0, A_ENEMY_DATA_ARRAY[i].pic_size, A_ENEMY_DATA_ARRAY[i].pic_size,
//				AirEnemyConfig::PIC_LINE_WIDE, 11, enemyPics.data());
//			air_enemy[i] = enemyPics;
//		}
//
//		// �n��G�̉摜�̃��[�h
//		for (int i = 0; i < G_ENEMY_SUMS; i++) {
//			std::vector<Bmp*> enemyPics(GroundEnemyConfig::PIC_LINE_WIDE * 11);
//			LoadDivBmp(PngData.G_Enemy, 0, 0, G_ENEMY_DATA_ARRAY[i].pic_size,
//				G_ENEMY_DATA_ARRAY[i].pic_size, AirEnemyConfig::PIC_LINE_WIDE, 9, enemyPics.data());
//			ground_enemy[i] = enemyPics;
//		}
//
//		// �{�X�̃p�[�c�Ɖ摜�̃��[�h
//		LoadDivBmp(PngData.BossSub, 0, 0, 48, 16, 4, 2, bosspats);
//		LoadDivBmp(PngData.Boss, 0, 0, 32, 32, 11, 11, boss);
//		LoadDivBmp(PngData.bomber, 0, 0, 47, 47, 6, 1, PlayerBomber);
//		LoadDivBmp(PngData.bomber, 0, 0, 47, 47, 12, 1, EnemyBomber);
//	}
//};
//
//// PNGDATA �̒�`
//PNGDATA ImageManager::PngData = {
//	L"res/STG_Title.png",
//	L"res/EDGE STG���@.png",
//	L"res/STG �e.png",
//	L"res/STG_A_enemy.png",
//	L"res/STG_G_enemy.png",
//	L"res/BOSS.png",
//	L"res/BOSS_PATS.png",
//	L"res/bomber.png",
//	L"res/Map/MapChip.png"
//};
//
//

#endif // GAME_H
