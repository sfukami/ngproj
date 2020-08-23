/*!
* @file		texture_vs.hlsl
* @brief	簡易シェーダー スプライト 頂点シェーダー
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
// VS Input/Output
// --------------------------------
struct VSInput
{
	float4 pos			: POSITION;
	float4 color		: COLOR;
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