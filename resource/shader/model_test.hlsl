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
	float4 color;
};

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
};

// --------------------------------
// VertexShader
// --------------------------------
VSOutput VSMain(VSInput In)
{
	VSOutput result = (VSOutput)0;

	result.pos = mul(In.pos, wvp);

	return result;
}

// --------------------------------
// PixelShader
// --------------------------------
float4 PSMain(VSOutput In) : SV_TARGET
{
	return color;
}