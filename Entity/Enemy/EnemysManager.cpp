#include "EnemysManager.h"

int EnemysManager::ALLEnemysInit()
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		groundenemys[i].Init(player_, bulletmanager_);
	}
	for (int i = 0; i < airenemys.size(); ++i) {
		airenemys[i].Init(player_,bulletmanager_);
	}
	return 0;
}

int EnemysManager::GroundEnemysUpdate(int framecount)
{
	for (int i = 0; i < groundenemys.size(); i++) {
		groundenemys[i].ActionUpdate(framecount);
	}
	return 0;
}

int EnemysManager::AirEnemysUpdate(int framecount)
{
	for (int i = 0; i < airenemys.size(); i++) {
		airenemys[i].ActionUpdate(framecount);
	}
	return 0;
}

int EnemysManager::GroundEnemysDraw()
{
	for (int i = 0; i < groundenemys.size(); i++) {
		groundenemys[i].Draw();
	}
	return 0;
}

int EnemysManager::AirEnemysDraw()
{
	for (int i = 0; i < airenemys.size(); i++) {
		airenemys[i].Draw();
	}
	return 0;
}

GroundEnemyBase& EnemysManager::GetGroundEnemysIndex(int index)
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		if (i == index) {
			return groundenemys[i];
		}
	}
}

AirEnemyBase& EnemysManager::GetAirEnemysIndex(int index)
{
	for (int i = 0; i < airenemys.size(); ++i) {
		if (i == index) {
			return airenemys[i];
		}
	}
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
		if (airenemys[i].GetActive() == false) {  // active��false�̏ꍇ
			return i;  // �����ɍ��v����Enemy��Ԃ�
		}
	}
	return -1;
}

int EnemysManager::searchEmptyGroundEnemyIndex()
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		if (groundenemys[i].GetActive() == false) {  // active��false�̏ꍇ
			return i;  // �����ɍ��v����Enemy��Ԃ�
		}
		return -1;
	}
}

inline std::array<GroundEnemyBase, MAX_ENEMY>& EnemysManager::GroundEnemysArray()
{
	return groundenemys;
}

inline std::array<AirEnemyBase, MAX_ENEMY>& EnemysManager::AirEnemysArray()
{
	return airenemys;
}

void EnemysManager::BackMap_Enemy_table(std::shared_ptr<IPlayer> player, std::shared_ptr<IMapManager> map, int _frame)
{
	//MAP_DATE BackMap = _m->backmap[_m->split_num];		//���݂̃o�b�N�}�b�v�̏��(1�X�e�[�W�ɂ�5�ɕ�������Ă��邤���̈��)

	auto wholemapdata = map->currentbackmap();
	auto backmap = wholemapdata.backmap[wholemapdata.currentparttition_num];

	if (wholemapdata.currentparttition_num > 0) {
		//�}�b�v�̐i�s�x���}�b�v�`�b�v�̃T�C�Y���i�񂾎�	�@&	�X�N���[�����x�Ɋւ�炸��񂾂��ʂ� &	 �}�b�v���X�V���ꂽ�u�Ԃ�y = 0�̎��͖�������
		if (backmap.y % CHIP_SIZE == 0 && _frame % SCROLL_SPEED == 0 && backmap.y > 0) {

			//�}�b�v�̍���(0,0)���灨(�s)�����čs��
			for (int r = 0; r < MAP_W; r++)
			{
				//�ϐ��̍쐬
				int SeachY_Axis = (backmap.y / CHIP_SIZE * MAP_W) + r;	//y���̐i�s�x����(����ڂ� + r�s��)
				int enemyNum = backmap.data[SeachY_Axis];				//�q�b�g�����G�̔ԍ�

				//�{�X�̃`�b�v����������///////////
				if (enemyNum == 60) {
						//�{�X�̏����ݒ�
				}

				//�n��G(50�Ŋ���؂��)//
				else if ((enemyNum / 50) % 2 == 1) {
					int emptynum = searchEmptyGroundEnemyIndex();
					groundenemys[searchEmptyGroundEnemyIndex()];

					//�n��G�̏o���ʒu���̐ݒ�
					int back_coord = SeachY_Axis;									//���}�b�v�ɂ�������W���L������
					int back_num = wholemapdata.currentparttition_num;								//���}�b�v�ԍ����L������
					float center_x = (float)((CHIP_SIZE * r) + (CHIP_SIZE / 2));	//�G�̒��S���W��ݒ�[(0���W����̋���) + �G�̑傫���̔���]

					//�G�̐���
					G_Enemy_Create(_ge, enemyNum, back_coord, back_num, center_x);

				}



				//�Œ�󒆓G(�K���o������)
				else if ((enemyNum / 50) % 2 == 0)		//�ԍ���50�ȉ�
				{
					bool init = false;
					airenemys[searchEmptyGroundEnemyIndex()].Create(enemyNum,0);

				}
			}
		}
	}
}