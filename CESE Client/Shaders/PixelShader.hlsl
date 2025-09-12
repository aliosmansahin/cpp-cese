struct PS_INPUT {
    float2 TexCoord: TEXCOORD0;
};

sampler2D g_texture;

float4 main(PS_INPUT input) : COLOR{
    float4 texColor = tex2D(g_texture, input.TexCoord);
    return texColor;
}