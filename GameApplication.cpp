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
//             -- コンストラクタ --
// 変数の初期設定
//==================================================
GameApplication::GameApplication() noexcept :
    m_window(nullptr),         
    m_outputWidth(800),     //幅
    m_outputHeight(600),    //高さ
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

//==================================================
//                  -- 初期設定 --
// ウィンドウの初期設定を行う
//==================================================
// Initialize the Direct3D resources required to run.
void GameApplication::Initialize(HWND window, HINSTANCE hInstance, int width, int height)
{
    m_window = window;                      //ウィンドウハンドルを変数に代入する
    m_outputWidth = std::max(width, 1);     //引数で受け取ったwidth を幅として受け取る。std::maxで width  か 1 大きい方を代入する
    m_outputHeight = std::max(height, 1);   //引数で受け取ったheightを幅として受け取る。std::maxで height か 1 大きい方を代入する

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
//              -- ループ処理 --
//ゲームループ内での 1フレームの処理
//==================================================
// Executes the basic game loop.
void GameApplication::Tick()
{
    m_timer.Tick([&]()
    {
        //更新処理
        Update(m_timer);
    });

    //描画処理
    Render();
}

//==================================================
//              -- 更新処理 --
//ゲームの情報を処理をする
//==================================================
// Updates the world.
void GameApplication::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());


  

    gamemain->Input();
    gamemain->Update();

    // TODO: その他のゲームロジックの追加
    elapsedTime;
}

//==================================================
//              -- 描画処理 --
//ゲームループ内での 1フレームの処理
//==================================================
// Draws the scene.
void GameApplication::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
    //画面のクリア
    Clear();

    //▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
     // TODO: Add your rendering code here.
    //画面の処理
    tex.Sprite->Begin();
    tex.Sprite->Draw(tex.SRV.Get(), m_pos);
    tex.Sprite->End();
   /* gamemain.Draw();*/
   //▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

    //バッファの切り替え
    Present();

  
}

//==================================================
//              -- 画面のクリア --
//各フレームの描画の前に呼び出し、 前のフレームの内容を
//クリアして新しいフレームの描画の準備をする
//==================================================
// Helper method to clear the back buffers.
void GameApplication::Clear()
{
    //レンダーターゲットと深度/ステンシルビューをクリア(初期化)する
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);                             //画面を色でクリアする
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);    //深度/ステンシルビューの初期化

    //初期化したレンダーターゲットと深度/ステンシルビューを再度設定する
    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    //ビューポートを再設定する
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight), 0.f, 1.f };
    m_d3dContext->RSSetViewports(1, &viewport);
}

//==================================================
//              -- バッファの切り替え --
//フロントバッファとバックバッファを入れ替える
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
//     -- イベント関数群 --
//特定のイベントが発生したときに呼び出される関数
//==================================================

//ゲームウィンドウがアクティブになった時に呼ばれる
void GameApplication::OnActivated()
{
    // TODO: Game is becoming active window.
}

//ゲームウィンドウが非アクティブになったら(バックグラウンドうぃんどうになったら　)
void GameApplication::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

//ゲームが中断される(電源が切られる。最少化)直前に呼び出される
void GameApplication::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

//ゲームウィンドウのサイズが変更されたら
void GameApplication::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}
//==================================================
//              -- バッファの切り替え --
//フロントバッファとバックバッファを入れ替える
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
//              -- デバイスを作成 --
//デバイスを作成し、変数に代入する
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
    
    tex = TextureSet(L"png/自機.png");

    //m_spriteBatch = std::make_unique<SpriteBatch>(m_d3dContext.Get());      //2dスプリクトを描写するクラスのオブジェクトを生成し、デバイスコンテキストのポインタを取得する
    //ComPtr<ID3D11Resource> resource;        //リソースを生成
    //DX::ThrowIfFailed(                      
    //    CreateWICTextureFromFile(m_d3dDevice.Get(), L"png/自機.png", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf())
    //);          //ファイルからテクスチャを読み込む。
    ////第一引数:デバイスを取得
    ////第二引数:読み込むテクスチャのファイルパス
    //
    //ComPtr<ID3D11Texture2D> texture;            //テクスチャを作成
    //DX::ThrowIfFailed(resource.As(&texture));   //作成したテクスチャを2Dテクスチャに変換したリソースを代入する
    //CD3D11_TEXTURE2D_DESC textureDesc;          //
    //texture->GetDesc(&textureDesc);             //テクスチャの詳細情報を格納する
  
}

//==================================================
//              -- リソースを作成する --
//グラフィックス、シェーダー、テクスチャ、モデル、シェーダーリソース
// などを格納する
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
//       -- デバイスのリセット & 再初期化 --
//デバイスをリセット(解放)してもう一度初期化する
//==================================================
void GameApplication::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    //各インターフェースのリセット
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();

    

    //テクスチャの初期化
    /*m_texture.Reset();
    m_spriteBatch.reset();*/

    tex.Sprite.reset();
    tex.SRV.Reset();
   // gamemain.Relese();

    //デバイスとリソースの初期化
    CreateDevice();

    CreateResources();
}

Textures GameApplication::TextureSet(const wchar_t* textureFilePath)
{
    Textures textures;
    textures.Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());      //2dスプリクトを描写するクラスのオブジェクトを生成し、デバイスコンテキストのポインタを取得する
    ComPtr<ID3D11Resource> resource;        //リソースを生成
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(m_d3dDevice.Get(), textureFilePath, resource.GetAddressOf(), textures.SRV.ReleaseAndGetAddressOf())
    );          //ファイルからテクスチャを読み込む。
    //第一引数:デバイスを取得
    //第二引数:読み込むテクスチャのファイルパス

    ComPtr<ID3D11Texture2D> texture;            //テクスチャを作成
    DX::ThrowIfFailed(resource.As(&texture));   //作成したテクスチャを2Dテクスチャに変換したリソースを代入する

    CD3D11_TEXTURE2D_DESC textureDesc;          //
    texture->GetDesc(&textureDesc);             //テクスチャの詳細情報を格納する

    return textures;
}
