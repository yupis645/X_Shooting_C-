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

// 必要に応じてDIContainer.hをインクルード
#include "DIContainer.h" // 前方宣言が適切に機能しない場合、これを追加

class GameSceneFactory {
public:
    GameSceneFactory(std::shared_ptr<DIContainer> con) : container_(con) {}

    std::shared_ptr<IPlayer> CreatePlayer() {
        return std::make_shared<Player>(
            container_->Create<ResourceManager>(),
            container_->Create<SpriteRenderer>(),
            container_->Create<IInputManager>()
        );
    }

    std::shared_ptr<IPlayer> CreateTestPlayer() {
        return std::make_shared<TestPlayer>(container_);
    }

    std::shared_ptr<IMapManager> CreateMap() {
        return std::make_shared<MapManager>(container_->Create<ResourceManager>());
    }

    std::shared_ptr<IMapManager> CreateTestMap() {
        return std::make_shared<TestMapManager>(container_->Create<ResourceManager>());
    }

private:
    std::shared_ptr<DIContainer> container_;
};

#endif //GAMESCENEFACTORY_H
