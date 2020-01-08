/// <summary>
/// �����V�[�g�̐��������B
/// </summary>
#pragma once
#include "GameObject.h"
#include "OrderSheet.h"
#include "FoodSheetGenerations.h"
#include "CookingList.h"
#include "TimeLimitGauge.h"

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
	/// <param name="geneunm">�������Ă���z��̔ԍ�</param>
	void FoodSheetGeneration(int FoodTypeNum,int genenum);

	/// <summary>
	/// ���������H�ו��V�[�g�̍��W�X�V�����B
	/// </summary>
	/// <param name="genenum">�������Ă���z��̔ԍ�</param>
	void FoodSheetPosUpdate(int genenum);

	/// <summary>
	/// ���̑��H�ו��ƒ������@�̉摜�`�揈���B
	/// </summary>
	/// <param name="genenum">�������Ă���z��̔ԍ�</param>
	void Order(int genenum);

	/// <summary>
	/// �����[�����������B
	/// </summary>
	/// <param name="genenum">�������Ă���z��̔ԍ�</param>
	void DeleteOrder(int genenum);

private://todo ��@����������B

	static const int m_orderNumLimit = 5;				//�����̏���l�B

	int m_orderNumber = 0;								//�������ꂽ�����̔ԍ��B
	int m_generationNum = 0;							//�������ꂽ�����̐��B
	int m_dishName[m_orderNumLimit] = { 0,0,0,0,0 };	//�����̖��O�B

	float m_sheet_x = 700.f;							//�V�[�g��X���W�B
	float m_sheet_y = 330.f;							//�V�[�g��Y���W�B
	float m_sheet_z = 0.f;								//�V�[�g��Z���W�B
	float m_moveLimit[m_orderNumLimit] = { -540.f ,-400.f  ,-260.f  ,-120.f  ,20.f };	//�ړ�����l�B
	float m_foodPosY[m_orderNumLimit] = { 340.f,340.f,340.f,340.f,340.f};
	float m_foodPosYLimit = 290.f;

	float m_orderTimer = 10.f;							//todo ���@����������^�C�}�[�B

	bool m_order = false;								//���������������ۂ��B
	bool m_foodSheetGenerationFlag[m_orderNumLimit] = { false };				//�H�ו��V�[�g�𐶐��������ۂ��B
	bool m_cuisineSheetFlag[m_orderNumLimit] = { false };			//�����̉摜�𐶐��������ۂ��B
	
	CVector3 m_position[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };					//���W�B
	CVector3 m_scale[m_orderNumLimit] = { CVector3::One(),CVector3::One(),CVector3::One(),CVector3::One(),CVector3::One() };							//�X�P�[���B
	CVector3 m_foodSheetPosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//�H�ו��V�[�g�̍��W�B
	CVector3 m_kitchenWarePosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() };		//�������̉摜���W�B
	CVector3 m_timeLimitGaugePosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() };	//�^�C�����~�b�g�Q�[�W�̍��W�B

	CQuaternion m_rotation[m_orderNumLimit] = { CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity() };	    	//��]�B

	OrderSheet* m_orderSheet[m_orderNumLimit] = {nullptr};			//�I�[�_�[�V�[�g�B
	FoodSheetGenerations* m_foodSheetGenerations = nullptr;			//�H�ו��̃V�[�g�B
	CookingList* m_cookingList = nullptr;							//�������X�g�B
	TimeLimitGauge* m_timeLimitGauge[m_orderNumLimit] = { nullptr };//���Ԑ����Q�[�W�B

	SpriteRender* m_spriteRenderCuisine[m_orderNumLimit] = { nullptr };					//�����̉摜�����p�X�v���C�g�B	
	SpriteRender* m_spriteRenderFoods[m_orderNumLimit] = { nullptr };					//�H�ו��̉摜�����p�X�v���C�g�B
	SpriteRender* m_spriteRenderCuisineMethod[m_orderNumLimit] = { nullptr };			//�����̉摜�����p�X�v���C�g�B


};

