
//----------------------------------------------------------------------------------------------------
//                              �Q�[���S�̂��Ǘ�����N���X
// 
// �Q�[���S�̂��Ǘ�����N���X�B�Q�[���J�n����I���܂Ő�����������
// di�R���e�i�ł̓V���O���g���Ńo�C���h����Ă���̂ŁAcreate�֐��ŏ�ɓ����C���X�^���X���擾�ł���
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------
#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 
#include "DIContainer.h"
#include "SceneManager.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;


using namespace DirectX;

//===========================================================================================
//							�R���X�g���N�^
// 
// di�R���e�i���K�v�Ȋ֐��̃C���X�^���X���쐬���ă����o�ϐ��ŕۊǂ���
// currentscene�ɂ�TitleScene�N���X���ŏ��ɍ쐬����
//===========================================================================================
GameManager::GameManager(std::shared_ptr<DIContainer> con)
	: container_(con),
	gamestatus_(con->Create<GameStatus>()),
	inputmanager_(con->Create<IInputManager>()),
	resourcemanager_(con->Create<ResourceManager>())
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));		//�������w�j�ɗ������Z�b�g
	scenemanager_ = std::make_shared<SceneManager>(container_);
}

//===========================================================================================
//							������
//===========================================================================================
void GameManager::Initialize(Game* game, HWND window, HINSTANCE hInstance)
{
    //IDirectInput8�C���^�[�t�F�C�X�̍쐬
    HRESULT hr = DirectInput8Create(
        hInstance,                 //�A�v���P�[�V�����̃C���X�^���X�n���h��
        DIRECTINPUT_VERSION,    //directInput�̃o�[�W����(DIRECTINPUT_VERSION�ŌŒ�ł���)
        IID_IDirectInput8,
        (void**)&m_directInput,
        NULL);
    if (FAILED(hr))
    {
        // ���s
    }

    //IDirectInputDevice8�̍쐬
    hr = m_directInput->CreateDevice(
        GUID_SysKeyboard,       //�g�p����f�o�C�X�̎��(����̓L�[�{�[�h)
        &m_keyboardDevice,      //IDirectInputDevice8�C���^�[�t�F�[�X�󂯎��
        NULL                    //��{NULL
    );
    if (FAILED(hr))
    {
        // ���s
    }

    //�f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
    hr = m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    if (FAILED(hr))
    {
        //���s
    }

    // �������[�h�̐ݒ�
    if (FAILED(m_keyboardDevice->SetCooperativeLevel(
        window,
        DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
    ))

        // ����J�n
        hr = m_keyboardDevice->Acquire();

    if (FAILED(hr))
    {
        // ����J�n���s
    }
    {
        // ���s
    }

    SetUp();
}

//�Q�[���̏����ݒ���s��
void GameManager::SetUp()
{

    //�V�[���쐬
    scenemanager_->SwitchToScene<TitleScene>();
}


//===========================================================================================
//							����
// 
// InputReception�ɂĕ����L�[�Az,x,esc,enter�ȂǃQ�[�����Ɏg�p����S�ẴL�[�̓��͂��擾����
// ���N���X�͂����ł̓��͌��ʂ��󂯂ăA�N�V�������N�����B
//===========================================================================================
int GameManager::Input()
{
    ////�S�Ă̓��͂��󂯂���
    //inputmanager_->InputReception();

    ////ESC�L�[�̓��͂��������ꍇ
    //if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))		//esc�t���O���`�F�b�N
    //{
    //    return SceneID::APP_EXIT;			//�A�v���̏I����main�֐��ɓ`����	
    //}


    // GetDeviceState�֐��g�p��
// �L�[����i�[�p
    BYTE KeyState[256];
    HRESULT hr;

    // �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
    hr = m_keyboardDevice->GetDeviceState(256, KeyState);
    if (SUCCEEDED(hr))
    {

        // ��L�[
        if (KeyState[DIK_UP] & 0x80)
        {
            //m_pos.y += 4.f;
        }

        // ���L�[
        if (KeyState[DIK_DOWN] & 0x80)
        {
            //m_pos.y -= 4.f;
        }

        // ���L�[
        if (KeyState[DIK_LEFT] & 0x80)
        {
            //m_pos.x -= 4.f;
        }

        // �E�L�[
        if (KeyState[DIK_RIGHT] & 0x80)
        {
            //m_pos.x += 4.f;
        }

        // ���^�[���L�[
        if (KeyState[DIK_RETURN] & 0x80)
        {

        }

        // �g���K�[���擾

        // �f�o�C�X���X�g���͍ēx����J�n���Ă�
    }
    else if (hr == DIERR_INPUTLOST) {
        m_keyboardDevice->Acquire();
    }
}

//===========================================================================================
//							�V�[���̍X�V
// 
// �V�[���̍X�V�������s���B�V�[�����ׂ̍��ȏ�����Scene�N���X���s���B
// �����ł�scene�N���X��Update�̕Ԃ�l�ɂ���ăG���[���� �y�� �V�[���J�ڂ��s��
//===========================================================================================
int GameManager::Update()
{

    int ir = scenemanager_->Init();
    int ur = scenemanager_->Update();
    int dr = scenemanager_->Draw();

    if (ir + ur + dr >= SceneID::APP_EXIT) return SceneID::APP_EXIT;

    return 0;
}
void GameManager::Draw()
{
}
void GameManager::Relese()
{
    //DirectInput�̒�~
    //1.�f�o�C�X����̒�~
    m_keyboardDevice->Unacquire();
    // IDirectInputDevice8�̉��
    m_keyboardDevice->Release();
    //IDirectInput8�̉��
    m_directInput->Release();
}

