
//----------------------------------------------------------------------------------------------------
//                              DI�R���e�i
// 
// �ˑ������������邽�߂�DI�R���e�i
// �R���X�g���N�^�œo�^�ƃo�C���h���s��di::singleton(�S�̂�ʂ��Ĉ�̃C���X�^���X) �ɐݒ�
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


// �R���X�g���N�^�� DI �R���e�i�𐶐����ĕێ�
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