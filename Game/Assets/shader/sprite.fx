/// <summary>
/// スプライト用のシェーダー。
/// </summary>

cbuffer cb : register(b0){
	float4x4 mvp;		//ワールドビュープロジェクション行列。
	float4 mulCol;
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos =  mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain( PSInput In ) : SV_Target0
{
	float4 col = colorTexture.Sample(Sampler, In.uv) * mulCol;
	return col;
}

float4 PSMainn(PSInput In) : SV_Target0
{
	return colorTexture.Sample(Sampler, In.uv);
} 