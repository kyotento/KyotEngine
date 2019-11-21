#include "stdafx.h"
#include "Onion.h"


Onion::Onion()
{
	//�H�ו��Ǝ��ʂ����B
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

	//todo �Z�@�؂��Ă��郂�[�V������t����B
	if (m_foodState == enCutting)		//�����؂�ꂽ��B
	{
		if (m_CuttingModel == false) {

			m_skinModelRender->Init(L"Assets/modelData/Food/Onion/CuttingOnion.cmo");	//�؂�ꂽ���f���ɕύX�B
			m_CuttingModel = true;
		}
	}

}