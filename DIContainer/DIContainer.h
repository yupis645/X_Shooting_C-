#ifndef DICONTAINER_H
#define DICONTAINER_H

//----------------------------------------------------------------------------------------------------
//                              DI�R���e�i
// 
// �ˑ������������邽�߂�DI�R���e�i
// ���݂�IGameManager,IInputManager,IMapManager ��3�̃N���X���e�X�g�N���X�ɕύX���\
// MapManager�̂݃X�R�[�v�� di::unique(�͈͂�����) �ɐݒ�B���̑��� di::singleton(�S�̂�ʂ��Ĉ��) �ɐݒ�
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
    // �R���X�g���N�^�� DI �R���e�i�𐶐����ĕێ�
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
        std::shared_ptr<GameStatus>,
        std::shared_ptr<ResourceManager>,
        std::shared_ptr<IMapManager>,
        std::shared_ptr<RendererManager>,
        std::shared_ptr<IInputManager>
        >
    > injector;  
};

#endif // DICONTAINER_H