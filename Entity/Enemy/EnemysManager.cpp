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
		if (airenemys[i].GetActive() == false) {  // activeがfalseの場合
			return i;  // 条件に合致するEnemyを返す
		}
	}
	return -1;
}

int EnemysManager::searchEmptyGroundEnemyIndex()
{
	for (int i = 0; i < groundenemys.size(); ++i) {
		if (groundenemys[i].GetActive() == false) {  // activeがfalseの場合
			return i;  // 条件に合致するEnemyを返す
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
	//MAP_DATE BackMap = _m->backmap[_m->split_num];		//現在のバックマップの情報(1ステージにつき5つに分割されているうちの一つ)

	auto wholemapdata = map->currentbackmap();
	auto backmap = wholemapdata.backmap[wholemapdata.currentparttition_num];

	if (wholemapdata.currentparttition_num > 0) {
		//マップの進行度がマップチップのサイズ分進んだ時	　&	スクロール速度に関わらず一回だけ通る &	 マップが更新された瞬間のy = 0の時は無視する
		if (backmap.y % CHIP_SIZE == 0 && _frame % SCROLL_SPEED == 0 && backmap.y > 0) {

			//マップの左上(0,0)から→(行)を見て行く
			for (int r = 0; r < MAP_W; r++)
			{
				//変数の作成
				int SeachY_Axis = (backmap.y / CHIP_SIZE * MAP_W) + r;	//y軸の進行度合い(何列目か + r行目)
				int enemyNum = backmap.data[SeachY_Axis];				//ヒットした敵の番号

				//ボスのチップがあったら///////////
				if (enemyNum == 60) {
						//ボスの初期設定
				}

				//地上敵(50で割り切れる)//
				else if ((enemyNum / 50) % 2 == 1) {
					int emptynum = searchEmptyGroundEnemyIndex();
					groundenemys[searchEmptyGroundEnemyIndex()];

					//地上敵の出現位置等の設定
					int back_coord = SeachY_Axis;									//裏マップにおける座標を記憶する
					int back_num = wholemapdata.currentparttition_num;								//裏マップ番号を記憶する
					float center_x = (float)((CHIP_SIZE * r) + (CHIP_SIZE / 2));	//敵の中心座標を設定[(0座標からの距離) + 敵の大きさの半分]

					//敵の生成
					G_Enemy_Create(_ge, enemyNum, back_coord, back_num, center_x);

				}



				//固定空中敵(必ず出現する)
				else if ((enemyNum / 50) % 2 == 0)		//番号が50以下
				{
					bool init = false;
					airenemys[searchEmptyGroundEnemyIndex()].Create(enemyNum,0);

				}
			}
		}
	}
}