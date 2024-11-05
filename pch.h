//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <winsdkver.h>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#include <sdkddkver.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unordered_map>

#include "GameApplication.h"
#include "common.h"
#include "Geometry.h"
#include "types.h"
#include "di.hpp"

#include <SpriteBatch.h>            //2Dスプライトのクラス
#include <SimpleMath.h>             //数学メソッド
#include <WICTextureLoader.h>       //テクスチャをロードする

#include <dinput.h>
using Microsoft::WRL::ComPtr;

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


namespace di = boost::di;       //boostの省略

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }
}
