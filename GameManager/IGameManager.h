#pragma once

#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H


class IGameManager {
public:
    IGameManager() {};
    ~IGameManager() = default;

    virtual int Init() = 0;

    virtual int Input() = 0;

    // シーンの更新と描画
    virtual int Update() = 0;

    virtual int Draw() = 0;

    // シーンの終了処理
    virtual int End() = 0;

};

#endif // IGAMEMANAGER_H
