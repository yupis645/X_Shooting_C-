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
    //初期化
    void Initialize(HWND window, HINSTANCE hInstance, int width, int height);

    // Basic game loop
    //ゲームループ
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    //テクスチャのセット
    Textures TextureSet(const wchar_t* texfilepas);

    //インターフェースのゲッター
    ComPtr<ID3D11Device1> GetDevice() const {return m_d3dDevice; }                               //デバイスの取得
    ComPtr<ID3D11DeviceContext1> GetDeviceContext() const { return m_d3dContext; }               //デバイスコンテキストの取得
    HWND GetWindow() const { return m_window; }                                                  // ウィンドウハンドルの取得
    ComPtr<IDXGISwapChain1> GetSwapChain() const { return m_swapChain; }                         // スワップチェインの取得
    ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const { return m_renderTargetView; }    // レンダーターゲットビューの取得
    ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const { return m_depthStencilView; }    // 深度/ステンシルビューの取得
    int GetOutputWidth() const { return m_outputWidth; }                                         // 出力の幅の取得
    int GetOutputHeight() const { return m_outputHeight; }                                       // 出力の高さの取得
    DirectX::SimpleMath::Vector2 GetPosition() const { return m_pos; }                           // 2D位置の取得

private:

    //更新
    void Update(DX::StepTimer const& timer);
    
    //描画
    void Render();

    //クリア
    void Clear();

    //バッファの入れ替え
    void Present();

    //デバイスの作成
    void CreateDevice();

    //リソースの作成
    void CreateResources();

    //各インターフェースのリセットとデバイス、リソースの再設定
    void OnDeviceLost();


//変数
    // Device resources.
    HWND                                            m_window;           //ウィンドウハンドルを格納する
    int                                             m_outputWidth;      //幅
    int                                             m_outputHeight;     //高さ

    D3D_FEATURE_LEVEL                               m_featureLevel;     //機能レベル
    ComPtr<ID3D11Device1>           m_d3dDevice;        //デバイス
    ComPtr<ID3D11DeviceContext1>    m_d3dContext;       //デバイスコンテキスト

    ComPtr<IDXGISwapChain1>         m_swapChain;        //スワップチェイン  
    ComPtr<ID3D11RenderTargetView>  m_renderTargetView; //レンダーターゲットビュー
    ComPtr<ID3D11DepthStencilView>  m_depthStencilView; //深度/ステンシルビュー
    DirectX::SimpleMath::Vector2 m_pos;                             //2次元ベクトルクラス


    Textures tex;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};
