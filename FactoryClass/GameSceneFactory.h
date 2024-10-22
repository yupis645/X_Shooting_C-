#pragma once

#include <iostream>
#include "GameScene.h"
#include "IPlayer.h"
#include "Player.h"
#include "IMapManager.h"
#include "MapManager.h"
#include "TestMapManager.h"
#include "ResourceManager.h"

class GameSceneFactory {
public:
    GameSceneFactory(std::shared_ptr<ResourceManager> rs) : resourcemanager_(rs) {}

    std::shared_ptr<IPlayer> CreatePlayer() {
        return std::make_shared<Player>();
    }

    std::shared_ptr<IPlayer> CreateTestPlayer() {
        return std::make_shared<Player>();
    }

    std::shared_ptr<IMapManager> CreateMap() {
        return std::make_shared<MapManager>(resourcemanager_);
    }

    std::shared_ptr<IMapManager> CreateTestMap() {
        return std::make_shared<TestMapManager>(resourcemanager_);
    }





private:
    std::shared_ptr<ResourceManager> resourcemanager_;
};
