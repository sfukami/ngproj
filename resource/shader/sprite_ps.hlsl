/*!
* @file		sprite_ps.hlsl
* @brief	簡易シェーダー スプライト ピクセルシェーダー
* @date		2019-09-30
* @author	s.fukami
*/

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
struct VSOutput
{
	float4 pos			: SV_POSITION;
	float2 uv			: TEXCOORD0;
};

// --------------------------------
// PixelShader
// --------------------------------
float4 PSMain(VSOutput In) : SV_TARGET
{
	return tex0.Sample(samp0, In.uv);
}