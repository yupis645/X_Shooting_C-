#include "TestGameScene.h"
#include "DebugManager.h"
#include "DIContainer.h"

#include "MapManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameSceneFactory.h"
#include "Player.h"

#include "TestBulletsManager.h"
#include "TestEnemysManager.h"
#include "TestPlayer.h"




TestGameScene::TestGameScene(std::shared_ptr<DIContainer> con)
    :GameScene(con),debug_(con->Create<DebugManager>()),
	createA_enemynumber(0),
	createG_enemynumber(0)
{

	testinput_ = std::dynamic_pointer_cast<TestInputManager>(con->Create<IInputManager>());
	testenemys_ = std::dynamic_pointer_cast<TestEnemysManager>(GameScene::GetEnemys());
	testbullets_ = std::dynamic_pointer_cast<TestBulletsManager>(GameScene::GetBullets());
	testplayer_ = std::dynamic_pointer_cast<TestPlayer>(GameScene::GetPlayer());

	if (testinput_   == nullptr) std::cout  << testinput_ <<   " のインスタンスではありません" << std::endl;
	if (testenemys_  == nullptr) std::cout  << testenemys_ <<  " のインスタンスではありません" << std::endl;
	if (testbullets_ == nullptr) std::cout  << testbullets_ << " のインスタンスではありません" << std::endl;
	if (testplayer_  == nullptr) std::cout  << testplayer_ <<  " のインスタンスではありません" << std::endl;
	
		

}

int TestGameScene::Init()
{
    GameScene::Init();
    return 0;
}

int TestGameScene::Update()
{
    int s = GameScene::Update();
	if (testinput_ != nullptr)
	{
		if (testinput_->DebugIsFlagSet(TestInputManager::DebugInputFlag::updateA_Enemynumber)) {
			createA_enemynumber++;
		}
		if (testinput_->DebugIsFlagSet(TestInputManager::DebugInputFlag::createA_Enemy)) {
			DebugCreateEnemy();
		}
	}

    return s;
}

int TestGameScene::Draw()
{
    GameScene::Draw();


    return 0;
}




void TestGameScene::DebugCreateEnemy()
{
	switch (createA_enemynumber) {
	case 0:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Toroid);
		break;
	case 1:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::toroid_type2);
		break;

	case 2:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Torkan);
		break;
	case 3:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Giddospario);
		break;
	case 4:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Zoshi);
		break;

	case 5:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::zoshi_type2);
		break;

	case 6:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::zoshi_type3);
		break;

	case 7:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Jara);
		break;

	case 8:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Jara_type2);
		break;
	case 9:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Kapi);
		break;
	case 10:
		GameScene::GetEnemys()->CreateAirEnemy(EnemyID::EnemyName::Terrazi);
		break;


	default:  // 上記のどのケースにも該当しない場合
		createA_enemynumber = 0;
		break;
	}

}