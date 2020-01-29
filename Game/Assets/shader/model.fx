/// <summary>
/// モデルシェーダー。
/// </summary>

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> g_albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウマップ。
Texture2D<float4> g_shadowMap : register(t2);	
//	法線マップ。
Texture2D<float4> g_normalMap : register(t3);		

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;		//法線マップを保持している？
};

static const int directionLightNum = 1;		//ディレクションライトの数。

struct DirectionLight {
	float4 direction[directionLightNum];	//ディレクションライトの向き。
	float4 color[directionLightNum];		//ディレクションライトの色。
};

//ライト用定数バッファ。
cbuffer LightConstantBuffer : register(b1)
{
	DirectionLight		directionLight;		//ディレクションライト。
	float3				eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトのパワー。
	float3				environmentpow;		//環境光の強さ。
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。

};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};

/// <summary>
/// シャドウマップ用のピクセルシェーダーへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position		:SV_POSITION;
};

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 pos = mul(mWorld, In.Position);
	float4 worldPos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	//psInput.Normal = normalize(mul(mWorld, In.Normal));
	//psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	if (isShadowReciever == 1) {
		//ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj,psInput.posInLVP);
	}

	//UV座標はそのままピクセルシェーダーに渡す。
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	////法線をそのままピクセルシェーダーに渡す。
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	////UV座標はそのままピクセルシェーダーに渡す。
	//psInput.TexCoord = In.TexCoord;
	////法線はそのままピクセルシェーダーに渡す。
	//psInput.Normal = In.Normal;


	//UV座標はそのままピクセルシェーダーに渡す。
	psInput.TexCoord = In.TexCoord;
	//法線をワールド行列で変換する。
	//法線がfloat3の3要素のベクトルなので、回転と拡大の変換だけが行われる。
	psInput.Normal = mul(mWorld, In.Normal);
	//拡大成分が入っているかもしれないので、正規化しとこ。
	psInput.Normal = normalize(psInput.Normal);
	//接ベクトルも回す。
	psInput.Tangent = mul(mWorld, In.Tangent);
	psInput.Tangent = normalize(psInput.Tangent);

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	if (isShadowReciever == 1) {
		//ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, pos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	//鏡面反射の計算のために、ワールド座標をピクセルシェーダーに渡す。
	psInput.worldPos = pos;
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 albedoColor = g_albedoTexture.Sample(g_sampler, In.TexCoord); //todo In.TexCodeがテクスチャのUV値。CBufferを使って送る。
	float3 lig = 0.0f;


	//法線を計算する。
	float3 normal = 0;

	if (isHasNormalMap == 1) {	//１なら法線マップが設定されている。
	//1 従法線の計算。
		float3 biNormal = cross(In.Normal, In.Tangent);
		//2 従法線を正規化。
		normalize(biNormal);

		normal = g_normalMap.Sample(g_sampler, In.TexCoord);

		//元は0～1。
		//-1.0～1.0の範囲に変換する。
		normal = (normal * 2.0f) - 1.0f;

		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}

	else {
	//ない。
	normal = In.Normal;
	}

	//鏡面反射光。
	//ディレクションライトの鏡面反射光を計算する。
	{
		for(int i = 0; i < directionLightNum; i++) {
			//ディレクションライトの拡散反射光を計算する。
			
			//lig += max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i];
			//反射ベクトルRを求める。
			float3 R = directionLight.direction[i] + 2 * dot(In.Normal, -directionLight.direction[i]) * In.Normal;

			//始点からライトを当てる物体に伸びるベクトルEを求める。
			float3 E = normalize(In.worldPos - eyePos);

			//求まったベクトルの内積を計算する。
			float specPower = max(0, dot(R, -E));

			//スペキュラ反射をライトに加算する。
			lig += directionLight.color[i].xyz * pow(specPower, 2) * specPow;
		}
	}
	//　環境光を当てる。
	lig += float3(environmentpow);

	float t = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[0]));

	if (t < 0.3f) {
		lig *= 0.9f;
	}
	else {
		lig *= 1.5f;
	}

	if (isShadowReciever == 1) {	//シャドウレシーバー。
	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.001f) {// + 0.001fしているのは、シャドウアクネを回避するため。
				//影が落ちているので、光を弱くする
				lig *= 0.7f;
			}
		}
	}


	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;

	//return albedoTexture.Sample(Sampler, In.TexCoord);
}


/// <summary>
/// シルエット描画用のピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}


/// <summary>
/// スキンなしモデル用の頂点シェーダー(シャドウマップ生成)
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
//todo スキン有りモデル用の頂点シェーダーを作る(シャドウマップ生成)

/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}