#include "DIContainer.h"

class GameManager;
class ResourceManager;
class MapManager;
class InputManager;

class TestGameManager;
class TestInputManager;

#include "di.hpp"

#include "GameManager.h"
#include "InputManager.h"
#include "MapManager.h"


// コンストラクタで DI コンテナを生成して保持
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

DIContainer::DIContainer() {
    injector = std::make_shared <di::injector<
        std::shared_ptr<IGameManager>,
        std::shared_ptr<Scenestatus>,
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>, 
        std::shared_ptr<IMapManager>, 
        std::shared_ptr<IInputManager>>>(
            di::make_injector(
                di::bind<IGameManager>().to<GameManager>().in(di::singleton),
                di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()).in(di::singleton),
                di::bind<GameStatus>().to(std::make_shared<GameStatus>()).in(di::singleton),
                di::bind<ResourceManager>().to(std::make_shared<ResourceManager>()).in(di::singleton),
                di::bind<IMapManager>().to<MapManager>().in(di::unique),
                di::bind<IInputManager>().to<InputManager>().in(di::singleton)
            )
        );


}
