
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

#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include "DebugManager.h"




// コンストラクタで DI コンテナを生成して保持
DIContainer::DIContainer() {
    injector = std::make_shared <di::injector<
        std::shared_ptr<IGameManager>,
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>,
        std::shared_ptr<SpriteRenderer>,
        std::shared_ptr<IInputManager>,
        std::shared_ptr<DebugManager>>>(
            di::make_injector(
                di::bind<IGameManager>().in(di::singleton).to<GameManager>(),
                di::bind<GameStatus>().in(di::singleton).to<GameStatus>(),
                di::bind<ResourceManager>().in(di::singleton).to<ResourceManager>(),
                di::bind<SpriteRenderer>().in(di::singleton).to<SpriteRenderer>(),
                di::bind<IInputManager>().in(di::singleton).to<InputManager>(),
                di::bind<DebugManager>().in(di::singleton).to<DebugManager>()
            )
        );
}