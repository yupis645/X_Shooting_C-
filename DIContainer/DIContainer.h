#ifndef DICONTAINER_H
#define DICONTAINER_H

#include "di.hpp"

#include "IGameManager.h"
#include "ResourceManager.h"
#include "IInputManager.h"
#include "IMapManager.h"


namespace di = boost::di;

class DIContainer {
public:
    // �R���X�g���N�^�� DI �R���e�i�𐶐����ĕێ�
    /*DIContainer() {
        injector = std::make_shared < di::injector < std::shared_ptr<Scenestatus>, std::shared_ptr<GameStatus>,
            std::shared_ptr<IPlayer>, std::shared_ptr<IEnemysManager>, std::shared_ptr<IBulletManager>, std::shared_ptr<IMapManager>,
            std::shared_ptr<IInputManager>>>(
                di::make_injector(
                    di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()),
                    di::bind<GameStatus>().to(std::make_shared<GameStatus>()),
                    di::bind<IPlayer>().to<Player>(),
                    di::bind<IEnemysManager>().to<EnemysManager>(),
                    di::bind<IBulletManager>().to<BulletsManager>(),
                    di::bind<IMapManager>().to<MapManager>(),
                    di::bind<IInputManager>().to<InputManager>()
                )
            );
    }*/
    DIContainer();

    // �C�ӂ̌^�̈ˑ��I�u�W�F�N�g�𐶐�
    template<typename T>
    std::shared_ptr<T> Create() {
        return injector->create<std::shared_ptr<T>>();
    }

private:
    std::shared_ptr<
        di::injector<
        std::shared_ptr<IGameManager>,
        std::shared_ptr<Scenestatus>,
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>,
        std::shared_ptr<IMapManager>,
        std::shared_ptr<IInputManager>
        >
    > injector;  // injector ���X�}�[�g�|�C���^�ŕێ�
};

#endif // DICONTAINER_H