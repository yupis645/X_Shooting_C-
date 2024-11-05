//
// Game.h
//

#pragma once

#include "StepTimer.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class GameApplication {
public:

    GameApplication() noexcept;
    ~GameApplication() = default;

    GameApplication(GameApplication&&) = default;
    GameApplication& operator= (GameApplication&&) = default;

    GameApplication(GameApplication const&) = delete;
    GameApplication& operator= (GameApplication const&) = delete;

    // Initialization and management
    //������
    void Initialize(HWND window, HINSTANCE hInstance, int width, int height);

    // Basic game loop
    //�Q�[�����[�v
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    //�e�N�X�`���̃Z�b�g
    Textures TextureSet(const wchar_t* texfilepas);

    //�C���^�[�t�F�[�X�̃Q�b�^�[
    ComPtr<ID3D11Device1> GetDevice() const {return m_d3dDevice; }                               //�f�o�C�X�̎擾
    ComPtr<ID3D11DeviceContext1> GetDeviceContext() const { return m_d3dContext; }               //�f�o�C�X�R���e�L�X�g�̎擾
    HWND GetWindow() const { return m_window; }                                                  // �E�B���h�E�n���h���̎擾
    ComPtr<IDXGISwapChain1> GetSwapChain() const { return m_swapChain; }                         // �X���b�v�`�F�C���̎擾
    ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const { return m_renderTargetView; }    // �����_�[�^�[�Q�b�g�r���[�̎擾
    ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return m_depthStencilView; }    // �[�x/�X�e���V���r���[�̎擾
    int GetOutputWidth() const { return m_outputWidth; }                                         // �o�͂̕��̎擾
    int GetOutputHeight() const { return m_outputHeight; }                                       // �o�͂̍����̎擾
    DirectX::SimpleMath::Vector2 GetPosition() const { return m_pos; }                           // 2D�ʒu�̎擾

private:

    //�X�V
    void Update(DX::StepTimer const& timer);
    
    //�`��
    void Render();

    //�N���A
    void Clear();

    //�o�b�t�@�̓���ւ�
    void Present();

    //�f�o�C�X�̍쐬
    void CreateDevice();

    //���\�[�X�̍쐬
    void CreateResources();

    //�e�C���^�[�t�F�[�X�̃��Z�b�g�ƃf�o�C�X�A���\�[�X�̍Đݒ�
    void OnDeviceLost();


//�ϐ�
    // Device resources.
    HWND                                            m_window;           //�E�B���h�E�n���h�����i�[����
    int                                             m_outputWidth;      //��
    int                                             m_outputHeight;     //����

    D3D_FEATURE_LEVEL                               m_featureLevel;     //�@�\���x��
    ComPtr<ID3D11Device1>           m_d3dDevice;        //�f�o�C�X
    ComPtr<ID3D11DeviceContext1>    m_d3dContext;       //�f�o�C�X�R���e�L�X�g

    ComPtr<IDXGISwapChain1>         m_swapChain;        //�X���b�v�`�F�C��  
    ComPtr<ID3D11RenderTargetView>  m_renderTargetView; //�����_�[�^�[�Q�b�g�r���[
    ComPtr<ID3D11DepthStencilView>  m_depthStencilView; //�[�x/�X�e���V���r���[
    DirectX::SimpleMath::Vector2 m_pos;                             //2�����x�N�g���N���X


    Textures tex;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};
