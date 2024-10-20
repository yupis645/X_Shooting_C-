#pragma once

#ifndef IGAMEMANAGER_H
#define IGAMEMANAGER_H


class IGameManager {
public:
    IGameManager() {};
    ~IGameManager() = default;

    virtual int Init() = 0;

    virtual int Input() = 0;

    // �V�[���̍X�V�ƕ`��
    virtual int Update() = 0;

    virtual int Draw() = 0;

    // �V�[���̏I������
    virtual int End() = 0;

};

#endif // IGAMEMANAGER_H
