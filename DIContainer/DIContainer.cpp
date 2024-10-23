
//----------------------------------------------------------------------------------------------------
//                              DI�R���e�i
// 
// �ˑ������������邽�߂�DI�R���e�i
// �R���X�g���N�^�œo�^�ƃo�C���h���s��
//IGameManager,IInputManager,IMapManager ��3�̃N���X���e�X�g�N���X�ɕύX���\
// MapManager�̂݃X�R�[�v�� di::unique(�͈͂�����) �ɐݒ�B���̑��� di::singleton(�S�̂�ʂ��Ĉ��) �ɐݒ�
//----------------------------------------------------------------------------------------------------

#include "DIContainer.h"
#include "di.hpp"

#include "GameManager.h"
#include "MapManager.h"
#include "InputManager.h"


// �R���X�g���N�^�� DI �R���e�i�𐶐����ĕێ�
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