#include "EnemysManager.h"

#include <functional>

#include "Game.h"
#include "IEnemysManager.h"
#include "IMapManager.h"
#include "IPlayer.h"
#include "IBulletsManager.h"
#include "EnemyBase.h"
#include "GroundEnemyBase.h"
#include "AirEnemyBase.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

namespace EnemyUtils {

	// �ėp�I�ȃC���f�b�N�X�����֐�
	template<typename EnemyType, std::size_t N>
	int FindActiveIndex(const std::array<std::shared_ptr<EnemyType>, N>& enemies, bool isActive) {
		for (std::size_t i = 0; i < enemies.size(); ++i) {
			if (enemies[i] && enemies[i]->GetActive() == isActive) {
				return static_cast<int>(i);
			}
		}
		return -1;
	}


}

EnemysManager::EnemysManager(std::shared_ptr<IPlayer> pl,
	std::shared_ptr<IBulletsManager> bm,
	std::shared_ptr<IMapManager> mr,
	std::shared_ptr<ResourceManager> rm,
	std::shared_ptr<SpriteRenderer> sm) :
	player_(pl), bullets_(bm), mapdata_(mr),render_(sm)
{
	textures_ = rm->GetAllTexture();

	for (auto& ae : airenemys) {
		ae = std::make_shared<AirEnemyDummy>();
	}
	for (auto& ge : groundenemys) {
		ge = std::make_shared<GroundEnemyDummy>();
	}
}

int EnemysManager::ALLEnemysInit()
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		groundenemys[i]->Init();
	}
	for (int i = 0; i < airenemys.size(); ++i) {
		airenemys[i]->Init();
	}

	return 0;
}

void EnemysManager::CreateAirEnemy(AirEnemytype type)
{
}

void EnemysManager::CreateGroundEnemy(GroundEnemytype type)
{
	int index = EnemyUtils::FindActiveIndex(groundenemys, false);
	if (index == -1) return;

	for (int i = 0; i < groundenemys.size(); i++) {
		if (groundenemys[i]->GetActive()) {
			//�����ɏ���������
		}
	}
}

int EnemysManager::GroundEnemysUpdate(int framecount)
{
	for (int i = 0; i < groundenemys.size(); i++) {
		if (groundenemys[i]->GetActive()) {
			int Re = groundenemys[i]->Update(player_);
			if (Re == EnemyBase::UpdateReturnID::OnBulletShot)
			{
				bullets_->CreateEnemyShot(player_->GetPosition(), groundenemys[i]->GetPosition());
			}
		}
	}
	return 0;
}

int EnemysManager::AirEnemysUpdate(int framecount)
{
	for (int i = 0; i < airenemys.size(); i++) {
		if (airenemys[i]->GetActive()) {
			int Re = airenemys[i]->Update(player_);
			if (Re == EnemyBase::UpdateReturnID::OnBulletShot)
			{
				bullets_->CreateEnemyShot(player_->GetPosition(), airenemys[i]->GetPosition());
			}
		}
	}
	return 0;
}

int EnemysManager::GroundEnemysDraw()
{
	for (int i = 0; i < groundenemys.size(); i++) {
		if (groundenemys[i]->GetActive()) {
			//groundenemys[i].Draw();
		}
	}
	return 0;
}

int EnemysManager::AirEnemysDraw()
{
	for (int i = 0; i < airenemys.size(); i++) {
		if (airenemys[i]->GetActive()) {
			//airenemys[i].Draw();
		}
	}
	return 0;
}

std::shared_ptr<GroundEnemyBase>  EnemysManager::GetGroundEnemysIndex(int index)
{
	if (index > groundenemys.size()) return nullptr;
	else return groundenemys[index];
}

std::shared_ptr<AirEnemyBase>  EnemysManager::GetAirEnemysIndex(int index)
{
	if (index > airenemys.size()) return nullptr;
	else return airenemys[index];
}
int EnemysManager::GetAirEnemysSum()
{
	return airenemys.size();
}
int EnemysManager::GetGroundEnemysSum()
{
	return groundenemys.size();
}
int EnemysManager::searchEmptyAirEnemyIndex()
{
	for (int i = 0; i < airenemys.size(); ++i) {
		if (airenemys[i]->GetActive() == false) {  // active��false�̏ꍇ
			return i;  // �����ɍ��v����Enemy��Ԃ�
		}
	}
	return -1;
}

int EnemysManager::searchEmptyGroundEnemyIndex()
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		if (groundenemys[i]->GetActive() == false) {  // active��false�̏ꍇ
			return i;  // �����ɍ��v����Enemy��Ԃ�
		}
	}
	return -1;

}

std::array<std::shared_ptr<GroundEnemyBase>, GroundEnemyConfig::MAX_ENEMY>& EnemysManager::GroundEnemysArray()
{
	return groundenemys;
}

std::array<std::shared_ptr<AirEnemyBase>, AirEnemyConfig::MAX_ENEMY>& EnemysManager::AirEnemysArray()
{
	return airenemys;
}


//=============================================================================================
//                              �}�b�v�f�[�^�̍X�V
//=============================================================================================
void EnemysManager::SwapMapdata(std::vector<int> setmap) {

	/*enemyplacement = resource_->ConvertDrawMapCsv_Vector();*/
	enemyplacement = setmap;

}


void EnemysManager::BackMap_Enemy_table(std::shared_ptr<IPlayer> player, std::shared_ptr<IMapManager> map, int _frame)
{
	//MAP_DATE BackMap = _m->backmap[_m->split_num];		//���݂̃o�b�N�}�b�v�̏��(1�X�e�[�W�ɂ�5�ɕ�������Ă��邤���̈��)

	//auto wholemapdata = map->currentbackmap();
	//auto backmap = wholemapdata.backmap[wholemapdata.currentparttition_num];

	//if (wholemapdata.currentparttition_num > 0) {
	//	//�}�b�v�̐i�s�x���}�b�v�`�b�v�̃T�C�Y���i�񂾎�	�@&	�X�N���[�����x�Ɋւ�炸��񂾂��ʂ� &	 �}�b�v���X�V���ꂽ�u�Ԃ�y = 0�̎��͖�������
	//	if (backmap.y % CHIP_SIZE == 0 && _frame % SCROLL_SPEED == 0 && backmap.y > 0) {

	//		//�}�b�v�̍���(0,0)���灨(�s)�����čs��
	//		for (int r = 0; r < MAP_W; r++)
	//		{
	//			//�ϐ��̍쐬
	//			int SeachY_Axis = (backmap.y / CHIP_SIZE * MAP_W) + r;	//y���̐i�s�x����(����ڂ� + r�s��)
	//			int enemyNum = backmap.data[SeachY_Axis];				//�q�b�g�����G�̔ԍ�

	//			//�{�X�̃`�b�v����������///////////
	//			if (enemyNum == 60) {
	//					//�{�X�̏����ݒ�
	//			}

	//			//�n��G(50�Ŋ���؂��)//
	//			else if ((enemyNum / 50) % 2 == 1) {
	//				int emptynum = searchEmptyGroundEnemyIndex();
	//				groundenemys[searchEmptyGroundEnemyIndex()];

	//				//�n��G�̏o���ʒu���̐ݒ�
	//				int back_coord = SeachY_Axis;									//���}�b�v�ɂ�������W���L������
	//				int back_num = wholemapdata.currentparttition_num;								//���}�b�v�ԍ����L������
	//				float center_x = (float)((CHIP_SIZE * r) + (CHIP_SIZE / 2));	//�G�̒��S���W��ݒ�[(0���W����̋���) + �G�̑傫���̔���]

	//				//�G�̐���
	//				G_Enemy_Create(_ge, enemyNum, back_coord, back_num, center_x);

	//			}



	//			//�Œ�󒆓G(�K���o������)
	//			else if ((enemyNum / 50) % 2 == 0)		//�ԍ���50�ȉ�
	//			{
	//				bool init = false;
	//				airenemys[searchEmptyGroundEnemyIndex()].Create(enemyNum,0);

	//			}
	//		}
	//	}
	//}
}