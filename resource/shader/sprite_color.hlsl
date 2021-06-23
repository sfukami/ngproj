/*!
* @file		sprite_color.hlsl
* @brief	簡易シェーダー スプライト 色指定
* @date		2019-09-30
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
	float2 uv			: TEXCOORD0;
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