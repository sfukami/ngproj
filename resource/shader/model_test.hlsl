/*!
* @file		model_test.hlsl
* @brief	モデル表示テスト用シェーダー
* @date		2021-06-13
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
	float4 uv			: TEXCOORD;
};
struct VSOutput
{
	float4 pos			: SV_POSITION;
	float4 uv			: TEXCOORD;
};

// --------------------------------
// VertexShader
// --------------------------------
VSOutput VSMain(VSInput In)
{
	VSOutput Out = (VSOutput)0;

	Out.pos = mul(In.pos, wvp);
	Out.uv = In.uv;

	return Out;
}

// --------------------------------
// PixelShader
// --------------------------------
float4 PSMain(VSOutput In) : SV_TARGET
{
	return tex0.Sample(samp0, In.uv);
}