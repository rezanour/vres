struct Vertex
{
    float3 Position : POSITION;
    float3 Normal   : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VSOutput
{
    float4 Position : SV_POSITION;
    float3 Normal   : NORMAL;
    float2 TexCoord : TEXCOORD;
};

VSOutput main(in Vertex input)
{
    VSOutput output;
    output.Position = float4(input.Position, 1);
    output.Normal = input.Normal;
    output.TexCoord = input.TexCoord;
    return output;
}