#include "Precomp.h"
#include "VRES_RenderPass.h"

namespace VRES
{
    uint32_t RenderPass::NextID = 0;

    RenderPass::RenderPass(const ComPtr<ID3D11Device>& device)
        : Device(device)
        , ID(NextID++)
    {
    }

    RenderPass::~RenderPass()
    {
    }

    uint32_t RenderPass::GetID() const
    {
        return ID;
    }

    bool RenderPass::LoadVS(const uint8_t* byteCode, size_t byteCodeSize)
    {
        HRESULT hr = Device->CreateVertexShader(byteCode, byteCodeSize, nullptr, &VertexShader);
        assert(SUCCEEDED(hr));
        return SUCCEEDED(hr);
    }

    bool RenderPass::LoadPS(const uint8_t* byteCode, size_t byteCodeSize)
    {
        HRESULT hr = Device->CreatePixelShader(byteCode, byteCodeSize, nullptr, &PixelShader);
        assert(SUCCEEDED(hr));
        return SUCCEEDED(hr);
    }

    void RenderPass::Apply()
    {
        ComPtr<ID3D11DeviceContext> context;
        Device->GetImmediateContext(&context);
        context->VSSetShader(VertexShader.Get(), nullptr, 0);
        context->PSSetShader(PixelShader.Get(), nullptr, 0);
    }

} // namespace VRES
