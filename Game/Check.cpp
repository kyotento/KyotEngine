#include "stdafx.h"
#include "Check.h"


Check::Check()
{
}


Check::~Check()
{
	DeleteGO(m_skinModelRender);			//�X�L�����f���������B
}

bool Check::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinModel");			
	m_skinModelRender->Init(L"Assets/modelData/2D/Check/check.cmo", nullptr, 0, "PSMain", "VSMain", true, false);		//�������B
	m_skinModelRender->SetPosition(m_position);			//���W���w��B
	m_skinModelRender->SetScale(m_scale);				//�g�嗦���w��B

	return true;
}

void Check::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W���X�V�B

}