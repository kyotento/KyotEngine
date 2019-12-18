#pragma once
#include "GameObject.h"

class FoodSheetGenerations : public GameObject
{
public:
	FoodSheetGenerations();
	~FoodSheetGenerations();

	bool Start();
	void Update();

	/// <summary>
	/// �����Ɏg�p����H�ו��������V�[�g�B
	/// </summary>
	/// <param name="FoodTypeNum">�����Ɏg���H�ו��̎��</param>
	void FoodSheetGeneration(int FoodTypeNum);

	/// <summary>
	/// �V�[�g�̍��W�X�V�B
	/// </summary>
	/// <param name="FoodTypeNum">�����Ɏg���H�ו��̎��</param>
	void SheetPos(int FoodTypeNum);

private:

	int m_foodNum = 0;
	int m_foodTypeLimit = 4;

	float m_y = 0.f;			//Y���W�B
	float m_scaleY = 1.f;		//�X�P�[����Y���W�B

	bool m_changeScaleFlag = false;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();

	SpriteRender* m_spriteRender[] = { nullptr };			//�X�v���C�g�B


};

