struct VS_INPUT {
	float4 Position: POSITION;
	float2 TexCoord: TEXCOORD0;
};

struct VS_OUTPUT {
	float4 Position: POSITION;
	float2 TexCoord: TEXCOORD0;
};

float4x4 world: register(c0);
float4x4 view: register(c4);
float4x4 proj: register(c8);

VS_OUTPUT main(VS_INPUT input) {
	float4x4 worldView = mul(view, world);
	float4x4 worldViewProj = mul(proj, worldView);

	VS_OUTPUT output;
	output.Position = mul(worldViewProj, input.Position);
	output.TexCoord = input.TexCoord;
	return output;
}