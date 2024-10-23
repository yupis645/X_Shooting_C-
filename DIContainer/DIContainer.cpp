
//----------------------------------------------------------------------------------------------------
//                              DIコンテナ
// 
// 依存性を解消するためのDIコンテナ
// コンストラクタで登録とバインドを行う
//IGameManager,IInputManager,IMapManager の3つのクラスをテストクラスに変更が可能
// MapManagerのみスコープが di::unique(範囲を限定) に設定。その他は di::singleton(全体を通して一つ) に設定
//----------------------------------------------------------------------------------------------------

#include "DIContainer.h"
#include "di.hpp"

#include "GameManager.h"
#include "MapManager.h"
#include "InputManager.h"


// コンストラクタで DI コンテナを生成して保持
DIContainer::DIContainer() {
    injector = std::make_shared <di::injector<
        std::shared_ptr<IGameManager>,
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>,
        std::shared_ptr<IMapManager>,
        std::shared_ptr<SpriteRenderer>,
        std::shared_ptr<IInputManager>>>(
            di::make_injector(
                di::bind<IGameManager>().in(di::singleton).to<GameManager>(),
                di::bind<GameStatus>().in(di::singleton).to<GameStatus>(),
                di::bind<ResourceManager>().in(di::singleton).to<ResourceManager>(),
                di::bind<IMapManager>().in(di::unique).to<MapManager>(),
                di::bind<SpriteRenderer>().in(di::singleton).to<SpriteRenderer>(),
                di::bind<IInputManager>().in(di::singleton).to<InputManager>()
            )
        );
}