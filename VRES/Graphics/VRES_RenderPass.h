#pragma once

namespace VRES
{
    class RenderPass
    {
    public:
        RenderPass(const ComPtr<ID3D11Device>& device);
        virtual ~RenderPass();

        uint32_t GetID() const;

        bool LoadVS(const uint8_t* byteCode, size_t byteCodeSize);
        bool LoadPS(const uint8_t* byteCode, size_t byteCodeSize);

        void Apply();

    private:
        ComPtr<ID3D11Device> Device;
        ComPtr<ID3D11VertexShader> VertexShader;
        ComPtr<ID3D11PixelShader> PixelShader;

        static uint32_t NextID;
        uint32_t ID;
    };
}
