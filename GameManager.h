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

#include "StepTimer.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.


class GameManager  {
public:
    GameManager(std::shared_ptr<DIContainer> con);      //�R���X�g���N�^
    ~GameManager() = default;

    // Initialization and management
 //������

    //������
    void Initialize(Game* game, HWND window, HINSTANCE hInstance);

    //�X�V
    int Update();

    //����
    int Input();

    //�`��
    void Draw();

    //���
    void Relese();

private:
    void SetUp();


private:

    std::shared_ptr<DIContainer> container_;            // Di�R���e�i
    std::shared_ptr<SceneManager> scenemanager_;            // Di�R���e�i
    std::shared_ptr<GameStatus> gamestatus_;            // �Q�[���֘A�̃X�e�[�^�X
    std::shared_ptr<IInputManager> inputmanager_;       // ���̓N���X
    std::shared_ptr<ResourceManager> resourcemanager_;  // �摜��CSV�t�@�C���Ȃǂ��Ǘ�����N���X
    std::shared_ptr<SceneBase> currentscene_;           // ���݂̃V�[��


    IDirectInput8* m_directInput;               //DirectInputDevice8���쐬���邽�߂̊֐���DirectX���g�p����PC���ǂ��܂ŋ@�\���g�����Ȃ��邩���`�F�b�N����֐�
    IDirectInputDevice8* m_keyboardDevice;      //IDirectInputDevice8�̓f�o�C�X���͂��Ǘ�����C���^�[�t�F�[�X

};




#endif // GAMEMANAGER_H
