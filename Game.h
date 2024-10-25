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
	constexpr int SHOT_SPEED_HOLLOW = 8;
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
	constexpr int HITBOX_SIZE = 8;		//�摜�̃T�C�Y
	constexpr int PIC_SIZE = 8;		//�摜�̃T�C�Y
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
		 active = false;
	}

	virtual Vector2 GetPosition()const {	return position;	}
	virtual void SetPosition(Vector2 pos){	position = pos;	}

	virtual Boxcollider GetHitbox()const {	return hitbox;	}
	virtual void SetHitbox(Boxcollider box){hitbox = box;	}

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	~GameObject() = default;

protected :
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};


#endif // GAME_H
