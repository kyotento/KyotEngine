#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_model = new SkinModel;// NewGO<SkinModel>(0, "a");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/unityChan.cmo");

	return true;
}

void Player::Update()
{
	//���[���h�s��̍X�V�B
	m_model->UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}
void Player::Draw()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}