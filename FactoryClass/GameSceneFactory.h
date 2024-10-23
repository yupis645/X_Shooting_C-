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

// �K�v�ɉ�����DIContainer.h���C���N���[�h
#include "DIContainer.h" // �O���錾���K�؂ɋ@�\���Ȃ��ꍇ�A�����ǉ�

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
