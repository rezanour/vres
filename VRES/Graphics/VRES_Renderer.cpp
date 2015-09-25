#include "Precomp.h"
#include "VRES_Renderer.h"

namespace VRES
{
    Renderer::Renderer()
    {
        ZeroMemory(&Viewport, sizeof(Viewport));
    }

    Renderer::~Renderer()
    {
    }

    bool Renderer::Initialize(HWND hwnd)
    {
        ComPtr<IDXGIFactory> factory;
        HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
        if (FAILED(hr))
        {
            assert(false);
            return false;
        }

        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        uint32_t flags = 0;
#if (_DEBUG)
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
            flags, &featureLevel, 1, D3D11_SDK_VERSION, &Device, nullptr, &Context);
        if (FAILED(hr))
        {
            assert(false);
            return false;
        }

        DXGI_SWAP_CHAIN_DESC scd{};
        scd.BufferCount = 2;
        scd.BufferDesc.Width = 1280;
        scd.BufferDesc.Height = 720;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = hwnd;
        scd.SampleDesc.Count = 1;
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        scd.Windowed = TRUE;

        hr = factory->CreateSwapChain(Device.Get(), &scd, &SwapChain);
        if (FAILED(hr))
        {
            assert(false);
            return false;
        }

        hr = SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
        if (FAILED(hr))
        {
            assert(false);
            return false;
        }

        D3D11_RENDER_TARGET_VIEW_DESC rtvd{};
        rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        hr = Device->CreateRenderTargetView(BackBuffer.Get(), &rtvd, &BackBufferRTV);
        if (FAILED(hr))
        {
            assert(false);
            return false;
        }

        Viewport.Width = (float)scd.BufferDesc.Width;
        Viewport.Height = (float)scd.BufferDesc.Height;
        Viewport.MaxDepth = 1.f;

        return true;
    }

    void Renderer::Begin()
    {
        static const float clearColor[]{ 0, 0, 0, 1 };
        Context->ClearRenderTargetView(BackBufferRTV.Get(), clearColor);

        Context->OMSetRenderTargets(1, BackBufferRTV.GetAddressOf(), nullptr);
        Context->RSSetViewports(1, &Viewport);
    }

    bool Renderer::Present()
    {
        HRESULT hr = SwapChain->Present(1, 0);
        assert(SUCCEEDED(hr));
        return SUCCEEDED(hr);
    }

} // namespace VRES
