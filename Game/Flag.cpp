#include "stdafx.h"
#include "Flag.h"


Flag::Flag()
{
}


Flag::~Flag()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_skinModelRenderB);
}

bool Flag::Start()
{
	//���f���̐������X�B
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/Flag/Flag.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	return true;
}

//B�{�^���𐶐�����B
void Flag::NewButton()
{
	if (m_skinModelRenderB != nullptr) {
		return;
	}

	m_skinModelRenderB = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRenderB->Init(L"Assets/modelData/2D/Button/B.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_position2D = m_position;
	m_position2D.y += 200.f;
	m_position2D.z -= 50.f;
	m_skinModelRenderB->SetPosition(m_position2D);
	m_skinModelRenderB->SetScale(m_scale2D);
}

//B�{�^�������������B
void Flag::DeleteButton()
{
	if (m_skinModelRenderB != nullptr) {
		DeleteGO(m_skinModelRenderB);
		m_skinModelRenderB = nullptr;
	}
}

void Flag::Update()
{

}