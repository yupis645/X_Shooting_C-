#ifndef GAMESCENEFACTORY_H
#define GAMESCENEFACTORY_H


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
    GameSceneFactory(std::shared_ptr<ResourceManager> resm, std::shared_ptr<SpriteRenderer> renm) : resurce_(resm), renderer_(renm){}

    std::shared_ptr<IPlayer> CreatePlayer() {
        return std::make_shared<Player>(resurce_, renderer_);
    }

    std::shared_ptr<IPlayer> CreateTestPlayer() {
        return std::make_shared<Player>(resurce_, renderer_);
    }

    std::shared_ptr<IMapManager> CreateMap() {
        return std::make_shared<MapManager>(resurce_);
    }

    std::shared_ptr<IMapManager> CreateTestMap() {
        return std::make_shared<TestMapManager>(resurce_);
    }





private:
    std::shared_ptr<ResourceManager> resurce_;
    std::shared_ptr<SpriteRenderer> renderer_;
};


#endif //GAMESCENEFACTORY_H