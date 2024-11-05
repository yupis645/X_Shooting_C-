#ifndef DICONTAINER_H
#define DICONTAINER_H

//----------------------------------------------------------------------------------------------------
//                              DIコンテナ
// 
// 依存性を解消するためのDIコンテナ
// 現在はIGameManager,IInputManager,IMapManager の3つのクラスをテストクラスに変更が可能
// MapManagerのみスコープが di::unique(範囲を限定) に設定。その他は di::singleton(全体を通して一つ) に設定
//----------------------------------------------------------------------------------------------------

class IGameManager;
class GameStatus;
class ResourceManager;
class SpriteRenderer;
class IInputManager;
class DebugManager;

#include "di.hpp"

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
        std::shared_ptr<IGameManager>,      //ゲームマネージャーのインターフェース型
        std::shared_ptr<GameStatus>,        //スコアや残機などのゲーム全体で参照するステータス
        std::shared_ptr<ResourceManager>,   //画像やcsvファイルのパスなどを管理するクラス
        std::shared_ptr<SpriteRenderer>,    //画像の描画などを担当するクラス
        std::shared_ptr<IInputManager>,     //入力を受付、キーの管理をするクラス

        std::shared_ptr<DebugManager>
        >
    > injector;  
};

#endif // DICONTAINER_H