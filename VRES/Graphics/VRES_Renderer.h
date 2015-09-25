#pragma once

namespace VRES
{
    class Renderer
    {
    public:
        Renderer();
        virtual ~Renderer();

        bool Initialize(HWND hwnd);

        void Begin();
        bool Present();

    private:
        ComPtr<ID3D11Device> Device;
        ComPtr<ID3D11DeviceContext> Context;
        ComPtr<IDXGISwapChain> SwapChain;
        ComPtr<ID3D11Texture2D> BackBuffer;
        ComPtr<ID3D11RenderTargetView> BackBufferRTV;
        D3D11_VIEWPORT Viewport;
    };

} // namespace VRES
