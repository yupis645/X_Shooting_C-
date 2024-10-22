#ifndef DICONTAINER_H
#define DICONTAINER_H

//----------------------------------------------------------------------------------------------------
//                              DIコンテナ
// 
// 依存性を解消するためのDIコンテナ
// 現在はIGameManager,IInputManager,IMapManager の3つのクラスをテストクラスに変更が可能
// MapManagerのみスコープが di::unique(範囲を限定) に設定。その他は di::singleton(全体を通して一つ) に設定
//----------------------------------------------------------------------------------------------------

#include "di.hpp"

#include "IGameManager.h"
#include "ResourceManager.h"
#include "IInputManager.h"
#include "IMapManager.h"
#include "GameSceneFactory.h"
#include "RendererManager.h"

namespace di = boost::di;

class DIContainer {
public:
    // コンストラクタで DI コンテナを生成して保持
    DIContainer();

    // 任意の型の依存オブジェクトを生成
    template<typename T>
    std::shared_ptr<T> Create() {
        return injector->create<std::shared_ptr<T>>();
    }

private:
    std::shared_ptr<
        di::injector<
        std::shared_ptr<IGameManager>,
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>,
        std::shared_ptr<IMapManager>,
        std::shared_ptr<RendererManager>,
        std::shared_ptr<IInputManager>
        >
    > injector;  
};

#endif // DICONTAINER_H