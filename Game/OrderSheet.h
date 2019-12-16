#pragma once
#include "GameObject.h"

class OrderSheet: public GameObject
{
public:
	OrderSheet();
	~OrderSheet();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SpriteRender* m_spriteRenderSheetNo1 = nullptr;			//�摜�����N���X�B��ԉ��̃V�[�g�B
	SpriteRender* m_spriteRenderSheetNo2 = nullptr;			//�摜�����N���X�B��O�̃V�[�g�B

};

