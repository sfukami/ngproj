/*!
* @file		simple.hlsl
* @brief	簡易シェーダー
* @date		2019-08-31
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
	float4 color		: COLOR;
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