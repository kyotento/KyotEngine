#include "stdafx.h"
#include "Tomato.h"


Tomato::Tomato()
{
	//�H�ו��Ǝ��ʂ����B
	m_identification = enFood;
	//�g�}�g����B
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

	//todo �Z�@�H�ו��ɐ؂��Ă��郂�[�V������t����B
	if (m_foodState == enCutting)		//�����؂�ꂽ��B
	{
		if (m_CuttingModel == false) {

			m_skinModelRender->Init(L"Assets/modelData/Food/Tomato/TomatoCutting.cmo");	//�؂�ꂽ���f���ɕύX�B
			m_CuttingModel = true;
		}
	}

	GaugePosUpdate();			//�������ꂽ�Q�[�W�̍��W���X�V�B
}