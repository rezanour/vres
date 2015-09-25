#include "Precomp.h"
#include "VRES_Mesh.h"
#include "VRES_RenderPass.h"

namespace VRES
{
    Mesh::Mesh(const ComPtr<ID3D11Device>& device)
        : Device(device)
        , PrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED)
        , BaseVertex(0)
        , VertexStride(0)
        , NumVertices(0)
        , BaseIndex(0)
        , NumIndices(0)
    {
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::SetRenderPass(const std::shared_ptr<RenderPass>& pass)
    {
        Pass = pass;
    }

    void Mesh::SetData(D3D11_PRIMITIVE_TOPOLOGY primitiveTopology, const ComPtr<ID3D11InputLayout>& inputLayout,
        const ComPtr<ID3D11Buffer>& vertexBuffer, uint32_t stride, uint32_t baseVertex, uint32_t numVertices,
        const ComPtr<ID3D11Buffer>& indexBuffer, uint32_t baseIndex, uint32_t numIndices)
    {
        PrimitiveTopology = primitiveTopology;
        InputLayout = inputLayout;
        VertexBuffer = vertexBuffer;
        VertexStride = stride;
        BaseVertex = baseVertex;
        NumVertices = numVertices;
        IndexBuffer = indexBuffer;
        BaseIndex = baseIndex;
        NumIndices = numIndices;
    }

    void Mesh::Render()
    {
        ComPtr<ID3D11DeviceContext> context;
        Device->GetImmediateContext(&context);

        Pass->Apply();

        // Setup input geometry
        context->IASetPrimitiveTopology(PrimitiveTopology);
        context->IASetInputLayout(InputLayout.Get());
        context->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &VertexStride, &BaseVertex);

        if (IndexBuffer)
        {
            context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            context->DrawIndexed(NumIndices, BaseIndex, BaseVertex);
        }
        else
        {
            context->Draw(NumVertices, BaseVertex);
        }
    }

} // namespace VRES
