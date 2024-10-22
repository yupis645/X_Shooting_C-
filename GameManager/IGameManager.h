
#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                         ゲーム全体を管理するクラス(インターフェース)
// 
// ゲーム全体を管理するクラスのインターフェース。
// 基本的なライフサイクルを定義している
//----------------------------------------------------------------------------------------------------

class IGameManager {
public:
    IGameManager() {};
    ~IGameManager() = default;

    virtual int Init() = 0;     //初期化

    virtual int Input() = 0;    //入力
    virtual int GameLoop() = 0;   //更新

    virtual int End() = 0;      //終了処理

};

#endif // IGAMEMANAGER_H
