#include "EnemysManager.h"


#include "IEnemysManager.h"
#include "IMapManager.h"
#include "IPlayer.h"
#include "IBulletsManager.h"
#include "EnemyBase.h"
#include "GroundEnemyBase.h"
#include "AirEnemyBase.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Player.h"

using enemyID = EnemyID::EnemyName;

namespace EnemyUtils {

	// 汎用的なインデックス検索関数
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

EnemysManager::EnemysManager(std::weak_ptr<IPlayer> pl,
	std::weak_ptr<IBulletsManager> bm,
	std::weak_ptr<IMapManager> mr,
	std::shared_ptr<ResourceManager> rm,
	std::shared_ptr<SpriteRenderer> sm) :
	player_(pl), bullets_(bm), mapdata_(mr),render_(sm)
{
	SetEnemyTexture(rm);

	for (auto& ae : airenemys) {
		ae = std::make_shared<AirEnemyDummy>();
	}
	for (auto& ge : groundenemys) {
		ge = std::make_shared<GroundEnemyDummy>();
	}
}


void EnemysManager::SetEnemyTexture(std::shared_ptr<ResourceManager> rm)
{

	int type_Strat= static_cast<int>(TextureType::Toroid);
	int type_End= static_cast<int>(TextureType::AirEnemyEnd);

	for (int i = enemyID::Toroid; i < enemyID::AirEnemyEnd; ++i) {
		enemyID id = static_cast<enemyID>(i);

		TextureType textureType = static_cast<TextureType>(type_Strat + i);

		// テクスチャを設定
		textures_[id] = rm->GetTexture(textureType);
	}

	type_Strat= static_cast<int>(TextureType::Barra);
	type_End= static_cast<int>(TextureType::GroundEnemyEnd);


	for (int i = enemyID::Barra; i < enemyID::GroundEnemyEnd; ++i) {
		enemyID id = static_cast<enemyID>(i);
		TextureType textureType = static_cast<TextureType>(type_Strat + i);

		// テクスチャを設定
		textures_[id]  = rm->GetTexture(textureType);
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

void EnemysManager::CreateAirEnemy(EnemyID::EnemyName name)
{
	int index = EnemyUtils::FindActiveIndex(airenemys, false);
	if (index == -1) return;

	int type_in_number = static_cast<int>(name);

	switch (name)
	{
	case EnemyID::EnemyName::Toroid:
	case EnemyID::EnemyName::toroid_type2:
		airenemys[index] = std::make_shared<TOROID>(player_, type_in_number);
		break;
	case EnemyID::EnemyName::Torkan:
		airenemys[index] = std::make_shared<TORKAN>(player_, type_in_number);
		break;
	case EnemyID::EnemyName::Giddospario:
		airenemys[index] = std::make_shared<GIDDOSPARIO>(player_, type_in_number);

		break;
	case EnemyID::EnemyName::Zoshi:
	case EnemyID::EnemyName::zoshi_type2:
	case EnemyID::EnemyName::zoshi_type3:
		airenemys[index] = std::make_shared<ZOSHI>(player_, type_in_number);
		break;
	case EnemyID::EnemyName::Jara:
	case EnemyID::EnemyName::Jara_type2:
		airenemys[index] = std::make_shared<JARA>(player_, type_in_number);
		break;
	case EnemyID::EnemyName::Kapi:
		airenemys[index] = std::make_shared<KAPI>(player_, type_in_number);

		break;
	case EnemyID::EnemyName::Terrazi:
		airenemys[index] = std::make_shared<TERRAZI>(player_, type_in_number);
		break;
	case EnemyID::EnemyName::Zakato:
		break;
	case EnemyID::EnemyName::Bragzakato:
		break;
	case EnemyID::EnemyName::Garuzakato:
		break;
	case EnemyID::EnemyName::Bacura:
		break;
	default:
		break;
	}
	
}

void EnemysManager::CreateGroundEnemy(EnemyID::EnemyName name)
{
	int index = EnemyUtils::FindActiveIndex(groundenemys, false);
	if (index == -1) return;

	switch (name)
	{
	case EnemyID::EnemyName::Barra:
		//groundenemys[index] = std::make_shared<BARA>();
		break;
	case EnemyID::EnemyName::Zolbak:
		break;
	case EnemyID::EnemyName::Logram:
	case EnemyID::EnemyName::Logram_type2:
	case EnemyID::EnemyName::Logram_type3:
	case EnemyID::EnemyName::Logram_type4:
		break;
	case EnemyID::EnemyName::Domogram:
		break;
	case EnemyID::EnemyName::Derota:
		break;
	case EnemyID::EnemyName::Grobda:
		break;
	case EnemyID::EnemyName::Bozalogram:
		break;
	case EnemyID::EnemyName::Sol:
		break;
	case EnemyID::EnemyName::Garubarra:
		break;
	case EnemyID::EnemyName::Garuderota:
	case EnemyID::EnemyName::Garubarra_type2:
	case EnemyID::EnemyName::Garubarra_type3:
	case EnemyID::EnemyName::Garubarra_type4:
	case EnemyID::EnemyName::Garubarra_type5:
	case EnemyID::EnemyName::Garubarra_type6:
	case EnemyID::EnemyName::Garubarra_type7:
	case EnemyID::EnemyName::Garubarra_type8:
	case EnemyID::EnemyName::Garubarra_type9:
		break;
	case EnemyID::EnemyName::Algo:
		break;
	case EnemyID::EnemyName::Ad_core:
		break;
	case EnemyID::EnemyName::Spflag:
		break;
	default:
		break;
	}
}

int EnemysManager::GroundEnemysUpdate(int framecount)
{
	auto usebullet = bullets_.lock();
	auto useplayer= player_.lock();

	for (int i = 0; i < groundenemys.size(); i++) {
		if (groundenemys[i]->GetActive()) {
			int Re = groundenemys[i]->Update(player_);
			if (Re == EnemyBase::UpdateReturnID::OnBulletShot)
			{
				usebullet->CreateEnemyShot(groundenemys[i]->GetPosition(), useplayer->GetPosition());
			}
		}
	}
	return 0;
}

int EnemysManager::AirEnemysUpdate(int framecount)
{
	auto usebullet = bullets_.lock();
	auto useplayer = player_.lock();
	for (int i = 0; i < airenemys.size(); i++) {
		if (airenemys[i]->GetActive()) {
			int Re = airenemys[i]->Update(useplayer);
			if (Re == EnemyBase::UpdateReturnID::OnBulletShot)
			{
				usebullet->CreateEnemyShot(airenemys[i]->GetPosition(), useplayer->GetPosition());
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
			EnemyID::EnemyName enemyname = static_cast<EnemyID::EnemyName>(airenemys[i]->GetNumber());
			if (!airenemys[i]->Getshootdown()) {
				render_->DrawFromCenterPos(textures_.at(enemyname), airenemys[i]->GetAnimNum(), airenemys[i]->GetPosition(), airenemys[i]->GetPicSize());
			}
			else {
				render_->DrawBomberFromCenterPos(SpriteRenderer::BomberType::airenemybomber, airenemys[i]->GetAnimNum(), airenemys[i]->GetPosition());

			}
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
	return static_cast<int>(airenemys.size());
}
int EnemysManager::GetGroundEnemysSum()
{
	return static_cast<int>(groundenemys.size());
}
int EnemysManager::searchEmptyAirEnemyIndex()
{
	return EnemyUtils::FindActiveIndex(airenemys, false);
}

int EnemysManager::searchEmptyGroundEnemyIndex()
{
	return EnemyUtils::FindActiveIndex(groundenemys, false);


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
//                              マップデータの更新
//=============================================================================================
void EnemysManager::SwapMapdata(std::vector<int> setmap) {

	/*enemyplacement = resource_->ConvertDrawMapCsv_Vector();*/
	enemyplacement = setmap;

}


void EnemysManager::BackMap_Enemy_table(std::shared_ptr<IPlayer> player, std::shared_ptr<IMapManager> map, int _frame)
{
	//MAP_DATE BackMap = _m->backmap[_m->split_num];		//現在のバックマップの情報(1ステージにつき5つに分割されているうちの一つ)

	//auto wholemapdata = map->currentbackmap();
	//auto backmap = wholemapdata.backmap[wholemapdata.currentparttition_num];

	//if (wholemapdata.currentparttition_num > 0) {
	//	//マップの進行度がマップチップのサイズ分進んだ時	　&	スクロール速度に関わらず一回だけ通る &	 マップが更新された瞬間のy = 0の時は無視する
	//	if (backmap.y % CHIP_SIZE == 0 && _frame % SCROLL_SPEED == 0 && backmap.y > 0) {

	//		//マップの左上(0,0)から→(行)を見て行く
	//		for (int r = 0; r < MAP_W; r++)
	//		{
	//			//変数の作成
	//			int SeachY_Axis = (backmap.y / CHIP_SIZE * MAP_W) + r;	//y軸の進行度合い(何列目か + r行目)
	//			int enemyNum = backmap.data[SeachY_Axis];				//ヒットした敵の番号

	//			//ボスのチップがあったら///////////
	//			if (enemyNum == 60) {
	//					//ボスの初期設定
	//			}

	//			//地上敵(50で割り切れる)//
	//			else if ((enemyNum / 50) % 2 == 1) {
	//				int emptynum = searchEmptyGroundEnemyIndex();
	//				groundenemys[searchEmptyGroundEnemyIndex()];

	//				//地上敵の出現位置等の設定
	//				int back_coord = SeachY_Axis;									//裏マップにおける座標を記憶する
	//				int back_num = wholemapdata.currentparttition_num;								//裏マップ番号を記憶する
	//				float center_x = (float)((CHIP_SIZE * r) + (CHIP_SIZE / 2));	//敵の中心座標を設定[(0座標からの距離) + 敵の大きさの半分]

	//				//敵の生成
	//				G_Enemy_Create(_ge, enemyNum, back_coord, back_num, center_x);

	//			}



	//			//固定空中敵(必ず出現する)
	//			else if ((enemyNum / 50) % 2 == 0)		//番号が50以下
	//			{
	//				bool init = false;
	//				airenemys[searchEmptyGroundEnemyIndex()].Create(enemyNum,0);

	//			}
	//		}
	//	}
	//}
}

