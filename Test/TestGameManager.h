#ifndef TESTGAMEMANAGER_H
#define TESTGAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              �e�X�g�pGameManager
// 
// �Q�[���S�̂��Ǘ�����N���X�̃e�X�g�N���X
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------

#include "IGameManager.h"
#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "ResourceManager.h"
#include "RendererManager.h"
#include "SceneManager.h"


class TestGameManager : public IGameManager{
public:
    TestGameManager(std::shared_ptr<DIContainer> con);      //�R���X�g���N�^ 

    int Init()override;         //������
    int Input()override;        //����
    int GameLoop() override;      //�X�V

    int End()override;          //�I������

    ~TestGameManager() {}       //�f�X�g���N�^

private:
    std::shared_ptr<SceneManager> scenemanager_;           // ���݂̎g�p���̃V�[��
    std::shared_ptr<GameStatus> gamestatus_;            // �Q�[���̃X�R�A�ȂǃQ�[���S�̂ŊǗ�����f�[�^
    std::shared_ptr<ResourceManager> resoucemanager_;   // �`��Ɏg���摜��Csv�Ȃǂ�ۊǂ���H�炤s
    std::shared_ptr<IInputManager> inputmanager_;       // ���͂��Ǘ�����N���X
    std::shared_ptr<RendererManager> renderermanager_;       // ���͂��Ǘ�����N���X
    std::shared_ptr<DIContainer> container_;            // DIContainer �̃����o�ϐ�
};

#endif ///ESTGAMEMANAGER_H