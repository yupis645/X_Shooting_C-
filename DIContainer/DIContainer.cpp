
//----------------------------------------------------------------------------------------------------
//                              DIコンテナ
// 
// 依存性を解消するためのDIコンテナ
// コンストラクタで登録とバインドを行うdi::singleton(全体を通して一つのインスタンス) に設定
//----------------------------------------------------------------------------------------------------

#include "DIContainer.h"
#include "di.hpp"
#include "GameManager.h"

#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include "DebugManager.h"
#include "TestInputManager.h"


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
                di::bind<IInputManager>().in(di::singleton).to<TestInputManager>(),
                di::bind<DebugManager>().in(di::singleton).to<DebugManager>()
            )
        );
}