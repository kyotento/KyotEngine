#pragma once
#include "character/CharacterController.h"
#include "Desk.h"
#include "DishHold.h"
#include "GasStove.h"
#include "DustBox.h"
#include "CuttingDesk.h"
#include "Kitchen.h"
#include "Delivery.h"
#include "TomatoBox.h"
#include "OnionBox.h"
#include "Knife.h"
#include "Belongings.h"
#include "Tomato.h"
#include "ObjectAbove.h"
#include "Gauge.h"
#include "math/Vector.h"
#include "SoupBase.h"
/// <summary>
/// �v���C���[�̊��N���X�B
/// </summary>
class Desk;
class DishHold;
class GasStove;
class DustBox;
class CuttingDesk;
class Kitchen;
class Delivery;
class TomatoBox;
class OnionBox;
class Knife;
class Belongings;
class Tomato;
class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	/// <summary>
	/// �v���C���[�ړ��N���X�B
	/// </summary>
	/// <param name="a">�R���g���[���[�ԍ�</param>
	void Movement(int a);

	/// <summary>
	/// �v���C���[��]�N���X�B
	/// </summary>
	void Rotation();

	/// <summary>
	/// �v���C���[�̓��쏈���B
	/// </summary>
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	void ActionProcessing(int controllerNum);

	/// <summary>
	/// �v���C���[�̑O�������ɐ����΂������B
	/// ray�ƃI�u�W�F�N�g�̓����蔻��𒲂ׂ鏈���B
	/// </summary>
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	/// <remarks>
	/// �O�������ɃI�u�W�F�N�g�����邩�𒲂ׂ邽�߂̂��́B
	/// </remarks>
	void ForwardDirectionRay(int controllerNum);

	/// <summary>
	/// �����������B
	/// </summary>
	void HoldingKnife();

	/// <summary>
	/// �����Ă���H�ו��̍��W��ݒ肷��B
	/// </summary>
	void SetFoodPosition();

	/// <summary>
	/// �H�ו���u�������B
	/// </summary>
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	void PutObjects(int controllerNum);

	/// <summary>
	/// ��������Ă��Ȃ��Ƃ��ɐH�ו���u�������B
	/// </summary>
	void NoRidePutFoods();

	/// <summary>
	/// ��������Ă��Ȃ��Ƃ��ɒ�������u�������B
	/// </summary>
	void NoRidePutKichenWares();

	/// <summary>
	/// ��������Ă��Ȃ��Ƃ��ɂ��M��u�������B
	/// </summary>
	void NoRidePutDishs();

	/// <summary>
	///	��������Ă��Ȃ��Ƃ��ɉ��ꂽ���M��u�������B
	/// </summary>
	void NoRidePutDirtyDishs();

	/// <summary>
	/// �I�u�W�F�N�g���E���B
	/// </summary>
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	void PickUpObjects(int controllerNum);

	/// <summary>
	/// �I�u�W�F�N�g��؂鏈���B
	/// </summary>
	void CuttingObject();

	/// <summary>
	/// �A�j���[�V�����B
	/// </summary>
	enum EnAnimationClip
	{
		enanimationClip_Idle,			//�ҋ@�B
		enanimationClip_Run,			//�����������Ɉړ��B
		enanimationClip_Cut,			//����؂�B
		enanimationClip_Washing,		//�M��􂤁B
		enanimationClip_IdleHave,		//���������đҋ@�B
		enanimationClip_RunHave,		//���������Ĉړ��B
		enanimationClip_Num,			//�A�j���[�V�����̐��B
	};

	/// <summary>
	/// �v���C���[�̏�ԁB
	/// </summary>
	enum enPlayerState
	{
		enIdle,							//�ҋ@��ԁB
		enRun,							//�ړ��B
		enCutting,						//����؂�B
		enWashing,						//�M��􂤁B
		enIdleHave,						//���������đҋ@���Ă���B
		enRunHave,						//���������Ĉړ����Ă���B
	};

	AnimationClip m_animationClips[enanimationClip_Num];		//�A�j���[�V�����̐��B

	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �����Ƃ̂ł�����̂�������B
	/// </summary>
	/// <param name="belon">������</param>
	void SetBelongings(Belongings* belon)
	{
		m_belongings = belon;
	}

	/// <summary>
	///	�i�C�t�̃C���X�^���X���擾�B
	/// </summary>
	/// <returns>�i�C�t</returns>
	Knife *GetKnife()
	{
		return m_knife;
	}

	/// <summary>
	/// �v���C���[��ray���I�u�W�F�N�g�ɏՓ˂������̏����B
	/// </summary>
	/// <param name="rayRC"></param>
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	void CollideToObject(btCollisionWorld::ClosestRayResultCallback rayRC, int controllerNum);

protected:

	int userIndexNum = 0;									//�������Ă���C���f�b�N�X�����B
	int m_controllerNumber = 0;								//todo ���@�v���C���[�P�̃R���g���[���[�ԍ��B

	bool m_toHave = false;									//�����������Ă��邩�ǂ����B
	bool m_knifeflag = false;								//�i�C�t��New���ꂽ���ǂ����B

	float m_transitionTime = 0.1f;							//�A�j���[�V�������؂�ւ��Ƃ��̑J�ڎ��ԁB
	float m_moveSpeed = 7.5f;								//�ړ����x�B
	float m_fallSpeed = 9.8f;								//�������x�B
	float m_distance = 70.0f;								//Ray�̔�΂��鋗���B
	float m_noLongerZero = 0.00001f;						//����Ȃ��O�ɋ߂��l�B
	float m_putTimer = 0.5f;								//�������I�u�W�F�N�g��u����悤�ɂȂ�܂ł̎��ԁB

	CVector3 m_objPos = CVector3::Zero();					//���������̃m���W�B
	CVector3 m_position = CVector3::Zero();					//�v���C���[�̍��W�B
	CVector3 m_characonPos = CVector3::Zero();				//�L�����R���̍��W�B
	CVector3 m_scale = CVector3::One();						//�g�嗦�B
	CVector3 m_move = CVector3::Zero();						//�L�����R���Ƃ��v���C���[�̈ړ����x���v�Z�������́B(��������)�B
	CVector3 m_oldPosition = CVector3::Zero();				//�L�����N�^�[�̂P�t���[���O�̍��W�B
	CVector3 m_stickPower = CVector3::Zero();				//���X�e�B�b�N�̌X�����ێ����邽�߂̂��́B
	CVector3 m_YisDie = CVector3::Zero();					//XZ���W�݂̂�ێ��B�v���C���[�̌����̌v�Z�Ɏg���B
	CVector3 m_ray = CVector3::Zero();						//���C�̏I�_�B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	CharacterController m_characon;							//�L�����R���B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B

	enPlayerState m_playerState = enIdle;					//�v���C���[�̏�ԁB

	Desk* m_desk = nullptr;						//���B
	DishHold* m_dishHold = nullptr;				//���M�u���B
	GasStove* m_gasStove = nullptr;				//�K�X�R�����B
	DustBox* m_dustbox = nullptr;				//�S�~���B
	CuttingDesk* m_cuttingDesk = nullptr;		//�܂ȔB
	Kitchen* m_kitchen = nullptr;				//���􂢏�B
	Delivery* m_delivery = nullptr;				//�󂯓n�����B
	TomatoBox* m_tomatoBox = nullptr;			//�g�}�g�̔��B
	OnionBox* m_onionBox = nullptr;				//�ʂ˂��̔��B
	Knife* m_knife = nullptr;					//�i�C�t�B
	Skeleton* m_skelton = nullptr;				//�T���Y(�X�P���g��)�B
	Belongings* m_belongings = nullptr;			//�����Ƃ��ł�����́B
	Belongings* m_cacth = nullptr;				//����u�����Ƃ̂ł���I�u�W�F�N�g�ɏ���Ă���A�����Ƃ̂ł���I�u�W�F�N�g�������������̂��i�[���邽�߂̂��́B
	Belongings* m_putSoup = nullptr;
	Tomato* m_tomato = nullptr;					//�g�}�g�B
	ObjectAbove* m_objectAbove = nullptr;		//����u�����Ƃ��ł���I�u�W�F�N�g�B
	Gauge* m_gauge = nullptr;					//�Q�[�W�B
	SoupBase* m_soupBase = nullptr;				//�X�[�v�B


private:

};

