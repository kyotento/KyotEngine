#include "stdafx.h"
#include "Tomato.h"


Tomato::Tomato()
{
	//食べ物と識別される。
	m_identification = enFood;
	//トマトだよ。
	m_foodTypeState = enTomato;
}


Tomato::~Tomato()
{
//	DeleteGO(m_skinModelRender);
}

bool Tomato::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Food/Tomato/Tomato.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}


void Tomato::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

	//todo 技　食べ物に切られているモーションを付ける。
	if (m_foodState == enCutting)		//もし切られたら。
	{
		if (m_CuttingModel == false) {

			m_skinModelRender->Init(L"Assets/modelData/Food/Tomato/TomatoCutting.cmo");	//切られたモデルに変更。
			m_CuttingModel = true;
		}
	}

	GaugePosUpdate();			//生成されたゲージの座標を更新。
}