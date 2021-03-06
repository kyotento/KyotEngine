#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"


SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}

	//ライト用定数バッファの開放。
	if (m_lightConstantBuffer != nullptr)
	{
		m_lightConstantBuffer->Release();
	}

	//スキン無モデル用の定数バッファの開放。
	if (m_uvConstantBuffer != nullptr)
	{
		m_uvConstantBuffer->Release();
	}

}

void SkinModel::Init(const wchar_t* filePath,/* EnFbxUpAxis enFbxUpAxis,*/ const char* entryPS, const char* entryVS/*, bool ShadowReciever = true*/)
{
	m_psmain = entryPS;
	m_vsmain = entryVS;

	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	//ディレクションライトの初期化。
	InitDirectionLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	//影を生成するか否か。
	/*SetShadowReciever(ShadowReciever);*/

	//m_enFbxUpAxis = enFbxUpAxis;
}

void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	//※ここで落ちた人へ。ファイルパス間違ってない？。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}

void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更する。
	bufferDesc.ByteWidth = sizeof(DirectionLight);				//DirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightConstantBuffer);

	//スキン無しモデル用の定数バッファを作成。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_uvConstantBuffer);

}

void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void SkinModel::InitDirectionLight()
{
	//太陽光
	m_directionLight.direction[0] = { -1.0f,-1.0f,1.0f,0.0f };
	m_directionLight.direction[0].Normalize();
	m_directionLight.color[0] = { 0.4f,0.4f,0.4f,1.f };
	
	//地面の照り返し
	/*m_directionLight.direction[1] = { 1.0f,-1.0f,1.0f,0.0f };
	m_directionLight.direction[1].Normalize();
	m_directionLight.color[1] = { 0.1f,0.1f,0.1f,1.f };


	m_directionLight.direction[2] = { -1.0f,0.5f,0.0f,0.0f };
	m_directionLight.direction[2].Normalize();
	m_directionLight.color[2] = { 0.0f,0.0f,0.0f,1.f };

	m_directionLight.direction[3] = { 1.0f,0.5f,1.0f,0.0f };
	m_directionLight.direction[3].Normalize();
	m_directionLight.color[3] = { 0.0f,0.0f,0.0f,1.f };

	m_directionLight.direction[4] = { 0.f,0.f,1.0f,0.0f };
	m_directionLight.color[4] = { 0.3f,0.3f,0.3f,1.f };
	*/
	m_directionLight.specPos = 0.0f;
	m_directionLight.ambientLig = { 0.5f, 0.5f, 0.5f, 1.0f };
	/*for (int i = 0; i < directionLightNum; i++)
	{
		if (i == 0) {
			m_directionLight.direction[i] = { 0.f,0.f,-1.0f,0.0f };
			m_directionLight.color[i] = { 1.f,1.f,1.f,1.f };
		}

		if (i == 1) {
			m_directionLight.direction[i] = { 0.f,0.f,-1.0f,0.0f };
			m_directionLight.color[i] = { 1.f,1.f,1.f,1.f };
		}
	}*/
}

void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}

void SkinModel::Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	auto shadowMap = IGameObjectManager().GetShadowMap();		//シャドウマップを取得。
	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	//ライトのカメラビュー、プロジェクション行列を送る。
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();

	//シャドウマップを生成するかどうかを決める。
	if (m_isShadowReciever) {			//フラグがtrueのとき。
		vsCb.isShadowReciever = 1;		//影を生成する。
	}
	else {								//フラグがfalseのとき。
		vsCb.isShadowReciever = 0;		//影を生成しない。
	}

	//法線マップを使用するかどうかのフラグを送る。
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}	

	//スペキュラマップを使用するかどうかのフラグを送る。
	if (m_specMapSRV != nullptr) {
		vsCb.isHasSpecuraMap = true;
	}
	else {
		vsCb.isHasSpecuraMap = false;
	}

//	vsCb.ambientLight = g_graphicsEngine->GetAmbientLight();
	//メインメモリの内容をVRAMにコピー（VRAM：：　GPUがアクセスするメモリ）。
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//視点を設定。
	m_directionLight.eyePos = g_camera3D.GetPosition();
	//鏡面反射光の絞りを設定。//各クラスで指定するように変更。
	//m_directionLight.specPos = 2.f;

	//UV値を更新。
	m_uvScroll.uv = m_uv;
	
	//ライト用の定数バッファを更新。
	d3dDeviceContext->UpdateSubresource(m_lightConstantBuffer, 0, nullptr, &m_directionLight, 0, 0);
	//PS用の定数バッファを更新。
	d3dDeviceContext->UpdateSubresource(m_uvConstantBuffer, 0, nullptr, &m_uvScroll, 0, 0);
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightConstantBuffer);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_uvConstantBuffer);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();
	//シャドウマップをレジスタに転送。(あってる？)
	d3dDeviceContext->PSSetShaderResources(2, 1, &m_shadowMapSRV);
	//エフェクトにクエリをかける。
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});

	if (m_normalMapSRV != nullptr) {
		//法線マップが設定されていたらをレジスタt3に設定する。
		d3dDeviceContext->PSSetShaderResources(3, 1, &m_normalMapSRV);
	}
	if (m_specMapSRV != nullptr) {
		//スペキュラマップが設定されていたらレジスタt4に設定する。
		d3dDeviceContext->PSSetShaderResources(4, 1, &m_specMapSRV);
	}

	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}

void SkinModel::InitNormalMap(const wchar_t* filePath)
{
	//DirectX::CreateDDSTextureFromFileEx(
	//	g_graphicsEngine->GetD3DDevice(),
	//	filePath,	//ロードするテクスチャのパス。
	//	0,
	//	D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
	//	0,
	//	0,
	//	false,
	//	nullptr,
	//	&m_normalMapSRV						//作成されたSRVのアドレスの格納先。
	//);

	//モデルに法線マップを設定する。
	//m_unityChanModelDraw.SetNormalMap(m_normalMapSRV);
}