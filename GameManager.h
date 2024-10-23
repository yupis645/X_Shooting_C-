#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//----------------------------------------------------------------------------------------------------
//                              �Q�[���S�̂��Ǘ�����N���X
// 
// �Q�[���S�̂��Ǘ�����N���X�B�Q�[���J�n����I���܂Ő�����������
// di�R���e�i�ł̓V���O���g���Ńo�C���h����Ă���̂ŁAcreate�֐��ŏ�ɓ����C���X�^���X���擾�ł���
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------

class DIContainer;
class SceneManager;            
class GameStatus;          
class IInputManager;       
class ResourceManager;
class SceneBase;

#include <iostream>
#include "IGameManager.h"


class GameManager :public IGameManager {
public:
    GameManager(std::shared_ptr<DIContainer> con);      //�R���X�g���N�^

    int Init()override;         //������
    int Input()override;        //����
    int GameLoop()override;    //�X�V
    int End()override;    // �I������
    
    ~GameManager() {}   //�f�X�g���N�^


    // �e���v���[�g�֐��ŃV�[���𐶐����Đ؂�ւ���
    template <typename SceneType>
    void SwitchToScene() {
        currentscene_ = std::make_shared<SceneType>(container_);
    }
private:
    std::shared_ptr<DIContainer> container_;            // Di�R���e�i
    std::shared_ptr<SceneManager> scenemanager_;            // Di�R���e�i
    std::shared_ptr<GameStatus> gamestatus_;            // �Q�[���֘A�̃X�e�[�^�X
    std::shared_ptr<IInputManager> inputmanager_;       // ���̓N���X
    std::shared_ptr<ResourceManager> resourcemanager_;  // �摜��CSV�t�@�C���Ȃǂ��Ǘ�����N���X
    std::shared_ptr<SceneBase> currentscene_;           // ���݂̃V�[��


};

#endif // GAMEMANAGER_H
