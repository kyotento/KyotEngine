/// <summary>
/// �����V�[�g�̐��������B
/// </summary>
#pragma once
#include "GameObject.h"
#include "OrderSheet.h"

class OrderGenerations : public GameObject
{
public:
	OrderGenerations();
	~OrderGenerations();

	bool Start();
	void Update();

	/// <summary>
	/// ���������B
	/// </summary>
	void Generations();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();

	/// <summary>
	/// �����Ɏg�p����H�ו��������V�[�g�B
	/// </summary>
	/// <param name="FoodTypeNum">�����Ɏg�p����H�ו��̎��</param>
	void FoodSheetGenerations(int FoodTypeNum);

private://todo ��@����������B

	static const int m_orderNumLimit = 5;				//�����̏���l�B
	int m_orderNumber = 0;								//�������ꂽ�����̔ԍ��B
	int m_generationNum = 0;							//�������ꂽ�����̐��B
	float m_sheet_x = 700.f;							//�V�[�g��X���W�B
	float m_sheet_y = 320.f;							//�V�[�g��Y���W�B
	float m_sheet_z = 0.f;								//�V�[�g��Z���W�B
	float m_moveLimit[m_orderNumLimit] = { -540.f ,-400.f  ,-260.f  ,-120.f  ,20.f };	//�ړ�����l�B

	float m_orderTimer = 0.f;							//todo ���@����������^�C�}�[�B

	bool m_order = false;								//���������������ۂ��B
	
	CVector3 m_position[m_orderNumLimit] = { CVector3::Zero() };					//���W�B
	CVector3 m_scale[m_orderNumLimit] = { CVector3::One() };						//�X�P�[���B
	CQuaternion m_rotation[m_orderNumLimit] = { CQuaternion::Identity() };	    	//��]�B

	OrderSheet* m_orderSheet[m_orderNumLimit] = {nullptr};			//�I�[�_�[�V�[�g�B

};

