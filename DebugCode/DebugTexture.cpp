#include "DebugTexture.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Geometry.h"
#include "GameTexture.h"
#include "common.h"
#include <iostream>

namespace util {
	constexpr int Y_POS = 40;		//�\��������W�̊�_
	constexpr int X_POS = 100;		//�\��������W�̊�_
}

//====================================================================================================
//				DebugManager�Ɏg�킹��֐��B�����ŕ\������e�N�X�`�����w�肷��
//====================================================================================================
void DebugTexture::DebugScreenDrawTexture(DebugSelectDraw draw)
{

	switch (draw) {
	case DebugSelectDraw::Unique:			//���ɕ��ނ̂Ȃ��摜����
		UniqueTextureDraw();
		break;
	case DebugSelectDraw::Airenemy:			//�󒆓G
		GroundEnemyTextureDraw();
		break;
	
	case DebugSelectDraw::GroundEnemy:		//�n��G
		AirEnemyTextureDraw();
		break;
	
	case DebugSelectDraw::Boss:				//�{�X�֘A
		BossTextureDraw();
		break;
	
	case DebugSelectDraw::MapChip:			//�}�b�v�`�b�v
		MapChipTextureDraw();
		break;
	}
}


//====================================================================================================
//					�^�C�g����v���C���[�Ȃǂǂ��ɂ������Ȃ��̉摜����ʂɕ`��
//====================================================================================================
void DebugTexture::UniqueTextureDraw()
{
	render->DrawFromTopLeftPos(resource->GetTexture(TextureType::Title), 0, Vector2(70, 100));

	DebugDrawRupe(TextureType::Player,             Vector2(util::X_POS, util::Y_POS * 1));
	DebugDrawRupe(TextureType::Targetsight,        Vector2(util::X_POS, util::Y_POS * 2));
	DebugDrawRupe(TextureType::Bullet,             Vector2(util::X_POS, util::Y_POS * 3));
	DebugDrawRupe(TextureType::Bom,                Vector2(util::X_POS, util::Y_POS * 4));
	DebugDrawRupe(TextureType::PlayerBomber,       Vector2(util::X_POS, util::Y_POS * 5));
	DebugDrawRupe(TextureType::BomBomber,          Vector2(util::X_POS, util::Y_POS * 6));
	DebugDrawRupe(TextureType::Air_EnemyBomber,    Vector2(util::X_POS, util::Y_POS * 7));
	DebugDrawRupe(TextureType::Ground_EnemyBomber, Vector2(util::X_POS, util::Y_POS * 8));
}


//====================================================================================================
//					�󒆓G�̉摜����ʂɕ`��
//====================================================================================================
void DebugTexture::AirEnemyTextureDraw()
{
	DebugDrawRupe(TextureType::Toroid,      Vector2(util::X_POS, util::Y_POS * 1));
	DebugDrawRupe(TextureType::Torkan,      Vector2(util::X_POS, util::Y_POS * 2));
	DebugDrawRupe(TextureType::Giddospario, Vector2(util::X_POS, util::Y_POS * 3));
	DebugDrawRupe(TextureType::Zoshi,       Vector2(util::X_POS, util::Y_POS * 4));
	DebugDrawRupe(TextureType::Jara,        Vector2(util::X_POS, util::Y_POS * 5));
	DebugDrawRupe(TextureType::Kapi,        Vector2(util::X_POS, util::Y_POS * 6));
	DebugDrawRupe(TextureType::Terrazi,     Vector2(util::X_POS, util::Y_POS * 7));
	DebugDrawRupe(TextureType::Zakato,      Vector2(util::X_POS, util::Y_POS * 8));
	DebugDrawRupe(TextureType::Bragzakato,  Vector2(util::X_POS, util::Y_POS * 9));
	DebugDrawRupe(TextureType::Garuzakato,  Vector2(util::X_POS, util::Y_POS * 10));
	DebugDrawRupe(TextureType::Bacura,      Vector2(util::X_POS, util::Y_POS * 11));
}


//====================================================================================================
//					�n��G�̉摜����ʂɕ`��
//====================================================================================================
void DebugTexture::GroundEnemyTextureDraw()
{
	DebugDrawRupe(TextureType::Barra,      Vector2(util::X_POS, util::Y_POS * 1));
	DebugDrawRupe(TextureType::Zolbak,     Vector2(util::X_POS, util::Y_POS * 2));
	DebugDrawRupe(TextureType::Logram,     Vector2(util::X_POS, util::Y_POS * 3));
	DebugDrawRupe(TextureType::Domogram,   Vector2(util::X_POS, util::Y_POS * 4));
	DebugDrawRupe(TextureType::Derota,     Vector2(util::X_POS, util::Y_POS * 5));
	DebugDrawRupe(TextureType::Grobda,     Vector2(util::X_POS, util::Y_POS * 6));
	DebugDrawRupe(TextureType::Bozalogram, Vector2(util::X_POS, util::Y_POS * 7));
	DebugDrawRupe(TextureType::Sol,        Vector2(util::X_POS, util::Y_POS * 8));
	DebugDrawRupe(TextureType::Garubarra,  Vector2(util::X_POS, util::Y_POS * 9));
	DebugDrawRupe(TextureType::Garuderota, Vector2(util::X_POS, util::Y_POS * 10));
	DebugDrawRupe(TextureType::Spflag,     Vector2(util::X_POS, util::Y_POS * 11));
}


//====================================================================================================
//					�{�X,�A���S(�C��),�R�A�̉摜����ʂɕ`��
//====================================================================================================
void DebugTexture::BossTextureDraw()
{
	auto config          = resource->GetTexture(TextureType::Boss)->GetConfig();

	Vector2 pos          = Vector2(ScreenConfig::CENTER_X, ScreenConfig::CENTER_Y);

	int algo_lefttop     = (config.indexcount / 2) - (config.rows + 1);
	int algo_righttop    = (config.indexcount / 2) - (config.rows - 1);
	
	int algo_leftbottom  = (config.indexcount / 2) + (config.rows + 1);
	int algo_rightbottom = (config.indexcount / 2) + (config.rows - 1);

	int algo_num = 0;
	for (int r = 0; r < config.rows; r++) {
		for (int r2 = 0; r2 < config.columns; r2++) {
			int pic_num  = r * config.columns + r2;
			int x_offset = -((config.width * config.rows) / 2) + (r2 * config.width);
			int y_offset = -((config.height* config.columns) / 2) + (r * config.height);
			
			render->DrawFromCenterPos(resource->GetTexture(TextureType::Boss), pic_num, (pos.x + x_offset), (pos.y + y_offset), config.width);

			if (pic_num == (config.indexcount / 2))
			{
				render->DrawFromCenterPos(resource->GetTexture(TextureType::Ad_core), 0, (pos.x + x_offset), (pos.y + y_offset), config.width);

			}
			if (pic_num == algo_lefttop ||pic_num == algo_righttop ||pic_num == algo_leftbottom ||pic_num == algo_rightbottom )
			{
				render->DrawFromCenterPos(resource->GetTexture(TextureType::Algo), algo_num, (pos.x + x_offset), (pos.y + y_offset), config.width);
				algo_num++;

			}
		}
	}


}


//====================================================================================================
//					�}�b�v�`�b�v�̉摜����ʂɕ`��
//====================================================================================================
void DebugTexture::MapChipTextureDraw()
{
	auto config = resource->GetTexture(TextureType::Map)->GetConfig();

	Vector2 pos = Vector2(0,0);

	for (int r = 0; r < config.columns; r++) {
		for (int r2 = 0; r2 < config.rows; r2++) {
			int pic_num = r * config.rows + r2;
			int x       = (r2 * config.width);
			int y       = (r * config.height);
			render->DrawFromTopLeftPos(resource->GetTexture(TextureType::Map), pic_num, x,y);
		}
	}

}


//====================================================================================================
//					�\���̃��[�v(�⏕�֐�)
//====================================================================================================
void DebugTexture::DebugDrawRupe(TextureType type, Vector2 pos) {

	auto config = resource->GetTexture(type)->GetConfig();

	for (int i = 0; i < config.indexcount; i++) {
		render->DrawFromCenterPos(resource->GetTexture(type),i, pos.x + (i * util::Y_POS), pos.y,  config.width);

	}
}
