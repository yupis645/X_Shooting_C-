#ifndef DICONTAINER_H
#define DICONTAINER_H

//----------------------------------------------------------------------------------------------------
//                              DI�R���e�i
// 
// �ˑ������������邽�߂�DI�R���e�i
// ���݂�IGameManager,IInputManager,IMapManager ��3�̃N���X���e�X�g�N���X�ɕύX���\
// MapManager�̂݃X�R�[�v�� di::unique(�͈͂�����) �ɐݒ�B���̑��� di::singleton(�S�̂�ʂ��Ĉ��) �ɐݒ�
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
        std::shared_ptr<IGameManager>,      //�Q�[���}�l�[�W���[�̃C���^�[�t�F�[�X�^
        std::shared_ptr<GameStatus>,        //�X�R�A��c�@�Ȃǂ̃Q�[���S�̂ŎQ�Ƃ���X�e�[�^�X
        std::shared_ptr<ResourceManager>,   //�摜��csv�t�@�C���̃p�X�Ȃǂ��Ǘ�����N���X
        std::shared_ptr<SpriteRenderer>,    //�摜�̕`��Ȃǂ�S������N���X
        std::shared_ptr<IInputManager>,     //���͂���t�A�L�[�̊Ǘ�������N���X

        std::shared_ptr<DebugManager>
        >
    > injector;  
};

#endif // DICONTAINER_H