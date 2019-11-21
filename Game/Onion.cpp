#include "stdafx.h"
#include "Onion.h"


Onion::Onion()
{
	//食べ物と識別される。
	m_identification = enFood;
}


Onion::~Onion()
{
	DeleteGO(m_skinModelRender);
}


bool Onion::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Food/Onion/onion.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);


	return true;
}

void Onion::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

	//todo 技　切られているモーションを付ける。
	if (m_foodState == enCutting)		//もし切られたら。
	{
		if (m_CuttingModel == false) {

			m_skinModelRender->Init(L"Assets/modelData/Food/Onion/CuttingOnion.cmo");	//切られたモデルに変更。
			m_CuttingModel = true;
		}
	}

}