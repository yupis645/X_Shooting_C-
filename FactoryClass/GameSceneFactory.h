#ifndef GAMESCENEFACTORY_H
#define GAMESCENEFACTORY_H

#include <iostream>
#include <memory>

#include "DIContainer.h"
#include "di.hpp"
#include "GameScene.h"
#include "Player.h"
#include "MapManager.h"
#include "TestMapManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TestPlayer.h"
#include "SpriteRenderer.h"
#include "BulletsManager.h"
#include "IEnemysManager.h"
#include "EnemysManager.h"

// 必要に応じてDIContainer.hをインクルード
#include "DIContainer.h" // 前方宣言が適切に機能しない場合、これを追加

class GameSceneFactory {
public:
    GameSceneFactory(std::shared_ptr<DIContainer> con) : container_(con) {}

    std::shared_ptr<IPlayer> CreatePlayer() {
        auto instance = std::make_shared<Player>(
            container_->Create<ResourceManager>(),
            container_->Create<SpriteRenderer>(),
            container_->Create<IInputManager>()
        );
        player_ = instance;
        return instance;
    }

    std::shared_ptr<IPlayer> CreateTestPlayer() {
        auto instance =  std::make_shared<TestPlayer>(container_);
        player_ = instance;
        return instance;

    }

    std::shared_ptr<IMapManager> CreateMap() {
        auto instance = std::make_shared<MapManager>(container_->Create<ResourceManager>());
        map_ = instance;
        return instance;
    }

    std::shared_ptr<IMapManager> CreateTestMap() {
        auto instance = std::make_shared<TestMapManager>(container_->Create<ResourceManager>());
        map_ = instance;
        return instance;
    }

     std::shared_ptr<IBulletsManager> CreateBulletsManager() {
         auto instance = std::make_shared<BulletsManager>(container_->Create<ResourceManager>(),container_->Create<SpriteRenderer>());
         bullets_ = instance;
         return instance;
    }

      std::shared_ptr<IEnemysManager> CreateEnemysManager() {
          auto instance = std::make_shared<EnemysManager>(player_,bullets_, map_,container_->Create<ResourceManager>(),container_->Create<SpriteRenderer>());
         enemys_ = instance;
         return instance;
    }



private:
    std::shared_ptr<DIContainer> container_;
    std::weak_ptr<IPlayer> player_;
    std::weak_ptr<IBulletsManager> bullets_;
    std::weak_ptr<IMapManager> map_;
    std::weak_ptr<IEnemysManager> enemys_;
};

#endif //GAMESCENEFACTORY_H
