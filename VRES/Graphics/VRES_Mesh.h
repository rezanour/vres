#pragma once

namespace VRES
{
    class RenderPass;

    class Mesh
    {
    public:
        Mesh(const ComPtr<ID3D11Device>& device);
        virtual ~Mesh();

        // Set the render pass to use for drawing this mesh
        void SetRenderPass(const std::shared_ptr<RenderPass>& pass);

        // Set the raw geometry
        void SetData(D3D11_PRIMITIVE_TOPOLOGY primitiveTopology, const ComPtr<ID3D11InputLayout>& inputLayout,
            const ComPtr<ID3D11Buffer>& vertexBuffer, uint32_t stride, uint32_t baseVertex, uint32_t numVertices,
            const ComPtr<ID3D11Buffer>& indexBuffer, uint32_t baseIndex, uint32_t numIndices);

        // TODO: take in the view dependent parameters
        void Render();

    private:
        ComPtr<ID3D11Device> Device;
        ComPtr<ID3D11InputLayout> InputLayout;
        ComPtr<ID3D11Buffer> VertexBuffer;
        ComPtr<ID3D11Buffer> IndexBuffer;
        std::shared_ptr<RenderPass> Pass;
        D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
        uint32_t VertexStride;
        uint32_t BaseVertex;
        uint32_t NumVertices;
        uint32_t BaseIndex;
        uint32_t NumIndices;
    };

} // namespace VRES
