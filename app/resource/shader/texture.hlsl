/*!
* @file		texture.hlsl
* @brief	簡易シェーダー テクスチャ
* @date		2019-09-30
* @author	s.fukami
*/

// --------------------------------
// ConstantBuffer
// --------------------------------
cbuffer ShaderParameter : register(b0)
{
	float4x4 wvp;
};

// --------------------------------
// Texure
// --------------------------------
Texture2D<float4>	tex0	: register(t0);

// --------------------------------
// Sampler
// --------------------------------
SamplerState		samp0	: register(s0);

// --------------------------------
// VS Input/Output
// --------------------------------
struct VSInput
{
	float4 pos			: POSITION;
	float4 normal		: NORMAL;
	float2 uv			: TEXCOORD0;
};
struct VSOutput
{
	float4 pos			: SV_POSITION;
	float2 uv			: TEXCOORD0;
};

// --------------------------------
// VertexShader
// --------------------------------
VSOutput VSMain(VSInput In)
{
	VSOutput result = (VSOutput)0;

	result.pos = mul(In.pos, wvp);
	result.uv = In.uv;

	return result;
}

// --------------------------------
// PixelShader
// --------------------------------
float4 PSMain(VSOutput In) : SV_TARGET
{
	return tex0.Sample(samp0, In.uv);
}