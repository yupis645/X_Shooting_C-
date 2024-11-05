//
// Game.cpp
//

#include "pch.h"
#include "GameApplication.h"
#include "GameManager.h"

extern void ExitGame() noexcept;

using namespace DirectX;

std::shared_ptr<GameManager> gamemain;

//==================================================
//             -- �R���X�g���N�^ --
// �ϐ��̏����ݒ�
//==================================================
GameApplication::GameApplication() noexcept :
    m_window(nullptr),         
    m_outputWidth(800),     //��
    m_outputHeight(600),    //����
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

//==================================================
//                  -- �����ݒ� --
// �E�B���h�E�̏����ݒ���s��
//==================================================
// Initialize the Direct3D resources required to run.
void GameApplication::Initialize(HWND window, HINSTANCE hInstance, int width, int height)
{
    m_window = window;                      //�E�B���h�E�n���h����ϐ��ɑ������
    m_outputWidth = std::max(width, 1);     //�����Ŏ󂯎����width �𕝂Ƃ��Ď󂯎��Bstd::max�� width  �� 1 �傫������������
    m_outputHeight = std::max(height, 1);   //�����Ŏ󂯎����height�𕝂Ƃ��Ď󂯎��Bstd::max�� height �� 1 �傫������������

    CreateDevice();

    CreateResources();


    gamemain->Initialize(this,window,hInstance);

    
    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

//==================================================
//              -- ���[�v���� --
//�Q�[�����[�v���ł� 1�t���[���̏���
//==================================================
// Executes the basic game loop.
void GameApplication::Tick()
{
    m_timer.Tick([&]()
    {
        //�X�V����
        Update(m_timer);
    });

    //�`�揈��
    Render();
}

//==================================================
//              -- �X�V���� --
//�Q�[���̏�������������
//==================================================
// Updates the world.
void GameApplication::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());


  

    gamemain->Input();
    gamemain->Update();

    // TODO: ���̑��̃Q�[�����W�b�N�̒ǉ�
    elapsedTime;
}

//==================================================
//              -- �`�揈�� --
//�Q�[�����[�v���ł� 1�t���[���̏���
//==================================================
// Draws the scene.
void GameApplication::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
    //��ʂ̃N���A
    Clear();

    //����������������������������������������������������
     // TODO: Add your rendering code here.
    //��ʂ̏���
    tex.Sprite->Begin();
    tex.Sprite->Draw(tex.SRV.Get(), m_pos);
    tex.Sprite->End();
   /* gamemain.Draw();*/
   //������������������������������������������������������

    //�o�b�t�@�̐؂�ւ�
    Present();

  
}

//==================================================
//              -- ��ʂ̃N���A --
//�e�t���[���̕`��̑O�ɌĂяo���A �O�̃t���[���̓��e��
//�N���A���ĐV�����t���[���̕`��̏���������
//==================================================
// Helper method to clear the back buffers.
void GameApplication::Clear()
{
    //�����_�[�^�[�Q�b�g�Ɛ[�x/�X�e���V���r���[���N���A(������)����
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);                             //��ʂ�F�ŃN���A����
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);    //�[�x/�X�e���V���r���[�̏�����

    //���������������_�[�^�[�Q�b�g�Ɛ[�x/�X�e���V���r���[���ēx�ݒ肷��
    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    //�r���[�|�[�g���Đݒ肷��
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight), 0.f, 1.f };
    m_d3dContext->RSSetViewports(1, &viewport);
}

//==================================================
//              -- �o�b�t�@�̐؂�ւ� --
//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�����ւ���
//==================================================
// Presents the back buffer contents to the screen.
void GameApplication::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

//==================================================
//     -- �C�x���g�֐��Q --
//����̃C�x���g�����������Ƃ��ɌĂяo�����֐�
//==================================================

//�Q�[���E�B���h�E���A�N�e�B�u�ɂȂ������ɌĂ΂��
void GameApplication::OnActivated()
{
    // TODO: Game is becoming active window.
}

//�Q�[���E�B���h�E����A�N�e�B�u�ɂȂ�����(�o�b�N�O���E���h������ǂ��ɂȂ�����@)
void GameApplication::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

//�Q�[�������f�����(�d�����؂���B�ŏ���)���O�ɌĂяo�����
void GameApplication::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

//�Q�[���E�B���h�E�̃T�C�Y���ύX���ꂽ��
void GameApplication::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}
//==================================================
//              -- �o�b�t�@�̐؂�ւ� --
//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�����ւ���
//==================================================
void GameApplication::OnWindowSizeChanged(int width, int height)
{
    if (!m_window)
        return;

    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void GameApplication::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

//==================================================
//              -- �f�o�C�X���쐬 --
//�f�o�C�X���쐬���A�ϐ��ɑ������
//==================================================
// These are the resources that depend on the device.
void GameApplication::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    DX::ThrowIfFailed(D3D11CreateDevice(
        nullptr,                            // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        static_cast<UINT>(std::size(featureLevels)),
        D3D11_SDK_VERSION,
        device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
        &m_featureLevel,                    // returns feature level of device created
        context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(device.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = static_cast<UINT>(std::size(hide));
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    DX::ThrowIfFailed(device.As(&m_d3dDevice));
    DX::ThrowIfFailed(context.As(&m_d3dContext));

  
    // TODO: Initialize device dependent objects here (independent of window size).
    
    tex = TextureSet(L"png/���@.png");

    //m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());      //2d�X�v���N�g��`�ʂ���N���X�̃I�u�W�F�N�g�𐶐����A�f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
    //ComPtr<ID3D11Resource> resource;        //���\�[�X�𐶐�
    //DX::ThrowIfFailed(                      
    //    CreateWICTextureFromFile(m_d3dDevice.Get(), L"png/���@.png", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf())
    //);          //�t�@�C������e�N�X�`����ǂݍ��ށB
    ////������:�f�o�C�X���擾
    ////������:�ǂݍ��ރe�N�X�`���̃t�@�C���p�X
    //
    //ComPtr<ID3D11Texture2D> texture;            //�e�N�X�`�����쐬
    //DX::ThrowIfFailed(resource.As(&texture));   //�쐬�����e�N�X�`����2D�e�N�X�`���ɕϊ��������\�[�X��������
    //CD3D11_TEXTURE2D_DESC textureDesc;          //
    //texture->GetDesc(&textureDesc);             //�e�N�X�`���̏ڍ׏����i�[����
  
}

//==================================================
//              -- ���\�[�X���쐬���� --
//�O���t�B�b�N�X�A�V�F�[�_�[�A�e�N�X�`���A���f���A�V�F�[�_�[���\�[�X
// �Ȃǂ��i�[����
//==================================================
// Allocate all memory resources that change on a window SizeChanged event.
void GameApplication::CreateResources()
{
    // Clear the previous window size specific context.
    m_d3dContext->OMSetRenderTargets(0, nullptr, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    const UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    const UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory2> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        // Create a descriptor for the swap chain.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = backBufferFormat;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = backBufferCount;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
        fsSwapChainDesc.Windowed = TRUE;

        // Create a SwapChain from a Win32 window.
        DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
            m_d3dDevice.Get(),
            m_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr,
            m_swapChain.ReleaseAndGetAddressOf()
            ));

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), nullptr, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

//==================================================
//       -- �f�o�C�X�̃��Z�b�g & �ď����� --
//�f�o�C�X�����Z�b�g(���)���Ă�����x����������
//==================================================
void GameApplication::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    //�e�C���^�[�t�F�[�X�̃��Z�b�g
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();

    

    //�e�N�X�`���̏�����
    /*m_texture.Reset();
    m_spriteBatch.reset();*/

    tex.Sprite.reset();
    tex.SRV.Reset();
   // gamemain.Relese();

    //�f�o�C�X�ƃ��\�[�X�̏�����
    CreateDevice();

    CreateResources();
}

Textures GameApplication::TextureSet(const wchar_t* textureFilePath)
{
    Textures textures;
    textures.Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());      //2d�X�v���N�g��`�ʂ���N���X�̃I�u�W�F�N�g�𐶐����A�f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
    ComPtr<ID3D11Resource> resource;        //���\�[�X�𐶐�
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(m_d3dDevice.Get(), textureFilePath, resource.GetAddressOf(), textures.SRV.ReleaseAndGetAddressOf())
    );          //�t�@�C������e�N�X�`����ǂݍ��ށB
    //������:�f�o�C�X���擾
    //������:�ǂݍ��ރe�N�X�`���̃t�@�C���p�X

    ComPtr<ID3D11Texture2D> texture;            //�e�N�X�`�����쐬
    DX::ThrowIfFailed(resource.As(&texture));   //�쐬�����e�N�X�`����2D�e�N�X�`���ɕϊ��������\�[�X��������

    CD3D11_TEXTURE2D_DESC textureDesc;          //
    texture->GetDesc(&textureDesc);             //�e�N�X�`���̏ڍ׏����i�[����

    return textures;
}
