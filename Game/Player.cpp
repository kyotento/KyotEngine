#include "stdafx.h"
#include "Player.h"

//#define SPRITE_TEST		//3D��Sprite�̃e�X�g������Ƃ��ɒ�`����B
//todo �����Ă�����̂̉�]���v���C���[�ˑ��ɂ���B
//todo �v���C���[�𕡐��o���d�g�݂����B
//todo�@���`�悵�Ȃ��悤�ɁB
//todo�@�����Ƃ������AObjectAbove��m_belongings��null�ɂ���B
namespace {
	const float playerCollidedRadius = 45.f;			//�J�v�Z���R���C�_�[�̔��a�B
	const float playerCollidedHeight = 50.f;			//�J�v�Z���R���C�_�[�̍����B
}

Player::Player()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_animationClips[enanimationClip_Idle].Load(L"Assets/animData/chef_idle.tka");				//�ҋ@���[�V�����B
	m_animationClips[enanimationClip_Run].Load(L"Assets/animData/chef_run.tka");				//�ړ��B
	m_animationClips[enanimationClip_Cut].Load(L"Assets/animData/chef_cutting.tka");			//����؂�B
	m_animationClips[enanimationClip_Washing].Load(L"Assets/animData/chef_washing.tka");		//�M�􂢁B
	m_animationClips[enanimationClip_IdleHave].Load(L"Assets/animData/chef_idleHave.tka");		//������������Ԃőҋ@�B
	m_animationClips[enanimationClip_RunHave].Load(L"Assets/animData/chef_runHave.tka");		//������������Ԃňړ��B

	//�L�����R���̏������B
	m_characon.Init(playerCollidedRadius, playerCollidedHeight, m_characonPos);
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

#ifdef SPRITE_TEST
SkinModelRender* m_skinModelRender2;
#endif

bool Player::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Chef/chef_1.cmo", m_animationClips, enanimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->PlayAnimation(enanimationClip_Idle);

	//todo�@���@2D�̃e�X�g�B
	
#ifdef SPRITE_TEST
	m_skinModelRender2 = NewGO<SkinModelRender>(0, "karikkari");
	m_skinModelRender2->Init(L"Assets/modelData/karikkari.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
#endif

	m_knife = NewGO<Knife>(0, "knife");

	return true;
}

void Player::Update()
{
	Movement(m_controllerNumber);					//�v���C���[�̈ړ������B
	Rotation();										//�v���C���[�̉�]�����B
	ForwardDirectionRay(m_controllerNumber);		//�v���C���[�̑O��������ray���΂������B
	ActionProcessing(m_controllerNumber);			//�v���e�\�̏�Ԃɂ�铮�쏈���B

	if (m_playerState != enanimationClip_Cut) {		//�����؂��Ă����Ԃ���Ȃ��Ƃ��B
		m_knife->SetPosition(m_position);			//�i�C�t�̍��W���w��B
	}

#ifdef SPRITE_TEST

//	m_x += 0.1f;
	m_testScale.x = m_x;

	m_skinModelRender2->SetScale(m_testScale);
	//m_skinModelRender2->SetPosition(m_position);

#endif


}

//�v���C���[�̈ړ������B
void Player::Movement(int a)
{
	
	m_stickPower.x = g_pad[a].GetLStickXF();		//���X�e�B�b�N��X���̌X���B
	m_stickPower.y = 0.f;							//���X�e�B�b�N��Y���B
	m_stickPower.z = g_pad[a].GetLStickYF();		//���X�e�B�b�N��Z���̌X���B

	if (m_stickPower.Length() > m_noLongerZero)		//�X�e�B�b�N���X���Ă���Ƃ��B
	{
		m_oldPosition = m_position;			//�v���C���[�̍��W���o�b�N�A�b�v�B

		m_move = m_stickPower * m_moveSpeed;			//�ړ����x�̌v�Z�B
		m_move.y -= m_fallSpeed;					//�������x�̌v�Z�B
		m_position = m_characon.Execute(1.0, m_move);		//�L�����R���Ɉړ����x�����B

		if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
			m_playerState = enRun;	//�ړ���ԁB
		}
	}

	else {
		if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
			m_playerState = enIdle;	//�ҋ@��ԁB
		}
	}

	m_skinModelRender->SetPosition(m_position);			//���f���̍��W���X�V�B

}

//�v���C���[�̉�]�����B
void Player::Rotation()
{
	//�ړ����Ă��Ȃ��Ȃ�B
	//if (m_position.x == m_oldPosition.x && m_position.z == m_oldPosition.z)
	//{
	//	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
	//	m_skinModelRender->SetRotation(m_rotation);
	//}

	m_YisDie = m_move;
	m_YisDie.y = 0.0f;

	//�ړ����Ă���Ȃ�B
	if (m_YisDie.Length() > m_noLongerZero){
		
		m_YisDie.Normalize();
		m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(m_YisDie.x, m_YisDie.z));
		m_skinModelRender->SetRotation(m_rotation);

	}

}

//�v���C���[��ray���I�u�W�F�N�g�ɏՓ˂������̏����B
void Player::CollideToObject(btCollisionWorld::ClosestRayResultCallback rayRC, int controllerNum)
{
	//�I�u�W�F�N�g�̐������[�v����B
	for (int i = 0; i <= ObjectAbove::enNumberOfObjectAbove; i++)
	{
		userIndexNum = rayRC.m_collisionObject->getUserIndex();	//n�ɓ������Ă���I�u�W�F�N�g��Index�����B
		if (rayRC.m_collisionObject->getUserIndex() == i) {	//�Փ˂����I�u�W�F�N�g��i�Ԗڂ��������B
			rayRC.m_collisionObject->getUserPointer();		//�Փ˂��Ă�����̂̃|�C���^��Ԃ��B
			m_objectAbove = (ObjectAbove*)rayRC.m_collisionObject->getUserPointer();			//m_objectAbove�ɕ����u����I�u�W�F�N�g�����B

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDesk) {			//���̂Ƃ��B

				m_desk = (Desk*)rayRC.m_collisionObject->getUserPointer();		//(Desk*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDelivery) {		//�J�E���^�[�̂Ƃ��B

				m_delivery = (Delivery*)rayRC.m_collisionObject->getUserPointer();		//(Delivery*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDishHold) {		//���M�u���̂Ƃ��B

				m_dishHold = (DishHold*)rayRC.m_collisionObject->getUserPointer();		//(DishHold*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDustBox) {		//�S�~���̂Ƃ��B

				m_dustbox = (DustBox*)rayRC.m_collisionObject->getUserPointer();		//(DustBox*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enGasStove) {		//�K�X�R�����̂Ƃ��B
					
				m_gasStove = (GasStove*)rayRC.m_collisionObject->getUserPointer();		//(GasStove*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enKitchen) {		//�L�b�`���̂Ƃ��B

				m_kitchen = (Kitchen*)rayRC.m_collisionObject->getUserPointer();

				if (g_pad[0].IsPress(enButtonX))
				{
					if (m_toHave == false) {			//�v���C���[�����������Ă��Ȃ��Ƃ��B
						m_playerState = enWashing;			//�v���C���[�̏�Ԃ����Ă����ԂɁB
						m_objectAbove->TakeThingsDirtyDish(m_cacth);			//����Ă��鉘�ꂽ�I�u�W�F�N�g����������m_cactc�ɁB
						m_kitchen->SetDishDirtyInstance((DishDirty*)m_cacth);			//���ꂽ���M�̃C���X�^���X��ݒ�B
						m_kitchen->DishWashing();			//���M��􂤊֐����Ăяo���B
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enOnionBox) {		//�ʂ˂��{�b�N�X�̂Ƃ��B

				m_onionBox = (OnionBox*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
					if (g_pad[controllerNum].IsTrigger(enButtonA) && m_objectAbove->GetState() == ObjectAbove::en_default)
					{
						m_belongings = m_onionBox->NewFood(controllerNum);		//�ʂ˂��𐶐�����B�����������̂̏���m_belongings�ɑ���B

						m_playerState = enIdleHave;			//�v���C���[�̏�Ԃ𕨂������đҋ@���Ă����ԂɁB
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enTomatoBox) {		//�g�}�g�{�b�N�X�̂Ƃ��B

				m_tomatoBox = (TomatoBox*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
					if (g_pad[controllerNum].IsTrigger(enButtonA) && m_objectAbove->GetState() == ObjectAbove::en_default)
					{
						m_belongings = m_tomatoBox->NewFood(controllerNum);	//�g�}�g�𐶐�����B�����������̂̏���m_belongings�ɑ���B

						m_playerState = enIdleHave;			//�v���C���[�̏�Ԃ𕨂������đҋ@���Ă����ԂɁB
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enCuttingDesk) {		//�܂Ȕ̂Ƃ��B

				m_cuttingDesk = (CuttingDesk*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
					if (g_pad[controllerNum].IsPress(enButtonX) && m_objectAbove->GetState() == ObjectAbove::en_onObject)		//X���������Ƃ��A��������Ă���Ƃ��B
					{
						m_playerState = enCutting;			//�v���C���[�̏�Ԃ𕨂�؂��Ă����ԂɁB
					}
				}
			}
		}
	}
}

//�v���C���[�̑O�������ɐ����΂������Bray�ƃI�u�W�F�N�g�̓����蔻��𒲂ׂ鏈���B
void Player::ForwardDirectionRay(int controllerNum)
{
	m_objectAbove = nullptr;		//����u����Null�ɂȂ�B

	CVector3 m_movesecond;							//ray�̒����B
	m_move.Normalize();								//���K�����A�����������擾����B
	m_movesecond = m_move * m_distance;				//ray�̒�����ݒ�B
	btVector3 start(m_position.x, m_position.y + 10, m_position.z);		//ray�̎n�_��btVector3�^�ɕϊ��B
	m_ray = { m_position.x + m_movesecond.x , m_position.y + m_movesecond.y, m_position.z + m_movesecond.z };		//ray�̏I�_���w��B
	btVector3 end(m_ray.x, m_ray.y + 10, m_ray.z);						//ray�̏I�_��btVector3�^�ɕϊ��B

	if (m_movesecond.Length() > m_noLongerZero) {						//ray�̒������O�ȏ�̂Ƃ��B
		btCollisionWorld::ClosestRayResultCallback rayRC(start, end);	//rayRC�ɏ�񂪓����Ă���B
		g_physics.GetDynamicWorld()->rayTest(start, end, rayRC);		//�Փ˔���B

		if (rayRC.hasHit()){			//�Փ˂��Ă���Ȃ�B
			CollideToObject(rayRC,controllerNum);		//�v���C���[�̑O�������ɃI�u�W�F�N�g�����������̏����B
		}
	}
}

//�v���C���[�̏�Ԃɂ�铮�쏈���B
void Player::ActionProcessing(int controllerNum)
{
	switch (m_playerState)
	{
	case enIdle:		//�ҋ@��Ԃ̂Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Idle, m_transitionTime);
		m_animationClips[enanimationClip_Idle].SetLoopFlag(true);

		m_toHave = false;			//���������Ă��Ȃ��B

		PickUpObjects(controllerNum);		//�I�u�W�F�N�g���������B

		break;

	case enRun:			//�ړ����Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Run, m_transitionTime);
		m_animationClips[enanimationClip_Run].SetLoopFlag(true);

		m_toHave = false;			//���������Ă��Ȃ��B

		PickUpObjects(controllerNum);		//�I�u�W�F�N�g���������B

		break;

	case enCutting:		//����؂��Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Cut, m_transitionTime);
		m_animationClips[enanimationClip_Cut].SetLoopFlag(true);

		HoldingKnife();				//����v���C���[�Ɏ������鏈���B

		CuttingObject();			//����؂�B

		m_toHave = false;			//���������Ă��Ȃ��B

		break;

	case enWashing:		//�M�����Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Washing, m_transitionTime);
		m_animationClips[enanimationClip_Washing].SetLoopFlag(true);

		m_toHave = false;			//���������Ă��Ȃ��B

		break;

	case enIdleHave:		//���������đҋ@���Ă���B

		m_skinModelRender->PlayAnimation(enanimationClip_IdleHave, m_transitionTime);
		m_animationClips[enanimationClip_IdleHave].SetLoopFlag(true);

		m_toHave = true;			//���������Ă��Ȃ��B

		if (m_stickPower.Length() > m_noLongerZero){			//�ړ��������B
			m_playerState = enRunHave;			//��Ԃ�ω�������B
		}

		SetFoodPosition();				//�H�ו��̍��W���v���C���[�̑O�������ɁB
		PutObjects(controllerNum);		//����u�������B

		break;

	case enRunHave:		//���������đ����Ă���B

		m_skinModelRender->PlayAnimation(enanimationClip_RunHave, m_transitionTime);
		m_animationClips[enanimationClip_RunHave].SetLoopFlag(true);

		m_toHave = true;			//���������Ă��Ȃ��B

		if (m_stickPower.Length() > m_noLongerZero == false) {		//�ړ����ĂȂ������Ƃ��B
			m_playerState = enIdleHave;			//��Ԃ�ω�������B
		}

		SetFoodPosition();				//�H�ו��̍��W���v���C���[�̑O�������ɁB
		PutObjects(controllerNum);		//����u�������B

		break;

	}
}

void Player::SetFoodPosition()
{
	//todo ��@�]�T������ΉE��ƍ����Bone�̍��W�̒��Ԓn�_�ɃI�u�W�F�N�g��u�������ɂ���B(�A�j���[�V�����ɃI�u�W�F�N�g�����Ă��邩��)�B
	m_objPos = m_ray;						//�����Ă�����̂̍��W�Ƀv���C���[�̃��C���W�����B
	m_objPos.y += 60.f;						//�C������ɍ��W���グ��B
	m_belongings->SetPosition(m_objPos);	//�����Ă���I�u�W�F�N�g�̍��W��ݒ�B

}

//��������Ă��Ȃ��Ƃ��ɐH�ו���u�������B
void Player::NoRidePutFoods()
{
	if (userIndexNum == ObjectAbove::enDesk || userIndexNum == ObjectAbove::enOnionBox ||
		userIndexNum == ObjectAbove::enTomatoBox || userIndexNum == ObjectAbove::enCuttingDesk) {		//�H�ו����u����I�u�W�F�N�g���ǂ����B
		m_objectAbove->PutThings(m_belongings);		//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
		m_objectAbove->SetState(ObjectAbove::en_onObject);					//����u�����I�u�W�F�N�g�̃X�e�[�g��ύX����B
		m_playerState = enIdle;							//�v���C���[�̃X�e�[�g��ҋ@��ԂɁB
	}
}

//��������Ă��Ȃ��Ƃ��ɒ�������u�������B
void Player::NoRidePutKichenWares()
{
	if (userIndexNum == ObjectAbove::enDesk || userIndexNum == ObjectAbove::enGasStove ||
		userIndexNum == ObjectAbove::enOnionBox || userIndexNum == ObjectAbove::enTomatoBox) {		//�������u����I�u�W�F�N�g���ǂ����B
		m_objectAbove->PutThings(m_belongings);							//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
		m_objectAbove->SetState(ObjectAbove::en_onObject);				//����u�����I�u�W�F�N�g�̃X�e�[�g��ύX����B
		m_playerState = enIdle;											//�v���C���[�̃X�e�[�g��ҋ@��ԂɁB
	}
}

//��������Ă��Ȃ��Ƃ��ɂ��M��u�������B
void Player::NoRidePutDishs()
{
	if (userIndexNum == ObjectAbove::enDesk || userIndexNum == ObjectAbove::enOnionBox ||
		userIndexNum == ObjectAbove::enTomatoBox) {					//���M���u����I�u�W�F�N�g���ǂ����B
		m_objectAbove->PutThings(m_belongings);						//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//����u�����I�u�W�F�N�g�̃X�e�[�g��ύX����B
		m_playerState = enIdle;										//�v���C���[�̏�Ԃ�ҋ@��ԂɁB
	}

	if (userIndexNum == ObjectAbove::enDelivery) {					//�󂯓n�����̂Ƃ��B
		m_objectAbove->PutThings(m_belongings);						//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
		DeleteGO(m_belongings);										//���M�������B
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//�󂯓n�����̏�Ԃ�ύX����B
		m_playerState = enIdle;										//�v���C���[�̏�Ԃ�ҋ@��ԂɁB
	}
}

//��������Ă��Ȃ��Ƃ��ɉ��ꂽ���M��u�������B
void Player::NoRidePutDirtyDishs()
{
	if (userIndexNum == ObjectAbove::enKitchen) {					//���M�􂢏�̂Ƃ��B
		m_objectAbove->SetDirtyDishPos(m_belongings);				//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//���M�􂢏�̏�Ԃ�ύX����B
		m_playerState = enIdle;										//�v���C���[��Ԃ�ҋ@��ԂɁB
	}
}

//����u�������B
void Player::PutObjects(int controllerNum)
{
	//todo ���H�B���������̂�������悤�ɂȂ�܂ł̃^�C�}�[�B
	m_putTimer -= 0.1f;

	if (g_pad[controllerNum].IsTrigger(enButtonA) && m_putTimer <= 0.f)		//A�{�^�����������Ƃ����A���������Ă����莞�Ԃ��o�߂������B
	{
		if (m_objectAbove != nullptr) {					//����u����I�u�W�F�N�g���ڂ̑O�ɂ���Ƃ��B

			//�I�u�W�F�N�g�ɉ�������Ă��Ȃ��Ƃ��B
			if (m_objectAbove->GetState() == ObjectAbove::en_default) {		

				//�����Ă�����̂��H�ו��̂Ƃ��B
				if (m_belongings->GetIndentValue() == Belongings::enFood) {	

					NoRidePutFoods();
				}

				//�����Ă�����̂��������̏ꍇ�B
				if (m_belongings->GetIndentValue() == Belongings::enKitchenWare) {		

					NoRidePutKichenWares();
				}

				//�����Ă�����̂����M�̏ꍇ�B
				if (m_belongings->GetIndentValue() == Belongings::enDish) {

					NoRidePutDishs();
				}

				//�����Ă�����̂����ꂽ���M�̂Ƃ��B
				if (m_belongings->GetIndentValue() == Belongings::enDirtyDish) {

					NoRidePutDirtyDishs();
				}
			}

			//�I�u�W�F�N�g�ɉ�������Ă���Ƃ��B
			if (m_objectAbove->GetState() == ObjectAbove::en_onObject){

				//�����Ă�����̂��H�ו��̂Ƃ��B
				if (m_belongings->GetIndentValue() == Belongings::enFood) {			
					if (m_belongings->GetFoodState() == Belongings::enCutting) {			//�����Ă���I�u�W�F�N�g���؂��Ă���Ƃ��B
						m_objectAbove->TakeThings(m_cacth);			//����Ă���I�u�W�F�N�g����������B
						if (m_cacth->GetIndentValue() == Belongings::enKitchenWare) {			//����Ă�����̂������������ꍇ�B
							if ( m_cacth->GetPotState() == Belongings::enZero) {			//����ɉ��������ĂȂ��Ƃ��B
								m_cacth->SetPotFoodType(m_cacth, m_belongings->GetFoodTypeState());			//����ɓ����H�ו���ݒ肷��B
								m_cacth->SetSoupBase(m_cacth);				//��ɃX�[�v������(������ۂ��I�u�W�F�N�g�̐���)�����B
								m_cacth->SetFoodTypeState(m_belongings->GetFoodTypeState());
								DeleteGO(m_belongings);						//�����Ă�����̂������B
								m_playerState = enIdle;						//��Ԃ�ҋ@��ԂɕύX�B
							}

							else {			//����ɉ��������Ă���Ƃ��B
								if (m_cacth->GetPotFoosType(m_cacth) == m_belongings->GetFoodTypeState()) {			//����̒��g�Ǝ����Ă���H�ו��̎�ނ������Ƃ��B
									if (m_cacth->GetPotState() == Belongings::enOne || m_cacth->GetPotState() == Belongings::enTwo) {		//����ɂ܂��H�ו��������Ԃ̂Ƃ��B
										m_cacth->SetSoupBase(m_cacth);				//��ɃX�[�v������(������ۂ��I�u�W�F�N�g�̐���)�����B
										DeleteGO(m_belongings);						//�����Ă�����̂������B
										m_playerState = enIdle;						//��Ԃ�ҋ@��ԂɕύX�B
									}
								}
							}
						}
					}
				}

				//�����Ă�����̂����M�̂Ƃ��B
				if (m_belongings->GetIndentValue() == Belongings::enDish) {			
					m_objectAbove->TakeThings(m_cacth);				//����Ă���I�u�W�F�N�g����������B
					if (m_cacth->GetIndentValue() == Belongings::enKitchenWare) {			//����Ă�����̂������������ꍇ�B
						if (m_cacth->GetPotState() == Belongings::enComplete) {				//����Ă�����̂̏�Ԃ�������Ԃ��������B
							//todo ��@��u�X�[�v�̒��g���������W�ɍs���̂𒼂��B
							m_cacth->DeleteSoup(m_cacth);
							m_belongings->PutDishs(m_belongings, m_cacth->GetFoodTypeState());
						}
					}
				}
			}
		}
		//todo �����@�����̃R�����g���O���Ƃǂ��ɂł��H�ו���u�����Ƃ��ł���B
	//	else(m_state = enIdle);							//�O�������ɃI�u�W�F�N�g���Ȃ��Ƃ��B

		m_putTimer = 0.5f;		//�^�C�}�[���������B
	}
}

//�I�u�W�F�N�g���E�������B
void Player::PickUpObjects(int controllerNum)
{
	if (g_pad[controllerNum].IsTrigger(enButtonA))						//A�{�^�����������Ƃ��B
	{
		if(m_toHave == false){			//���������Ă��Ȃ��Ƃ�
			if (m_objectAbove != nullptr) {						//�ڂ̑O�ɃI�u�W�F�N�g������Ƃ��B

				//���M�􂢏�ȊO�̂Ƃ��B
				if (userIndexNum != ObjectAbove::enKitchen) {
					if (m_objectAbove->GetState() == ObjectAbove::en_onObject) {			//�I�u�W�F�N�g�ɉ�������Ă���Ƃ��B
						m_objectAbove->TakeThings(m_belongings);	//����Ă���I�u�W�F�N�g�������B
						m_objectAbove->SetState(ObjectAbove::en_default);					//�����Ƃ����I�u�W�F�N�g�̃X�e�[�g��ύX����B
						m_objectAbove->SetBelongings(nullptr);				//����Ă�����̂�null�ɁB
						m_toHave = true;							//�������t���O�B
						m_playerState = enIdleHave;					//�X�e�[�g�ύX�B
					}
				}

				//���M�􂢏�̂Ƃ��B
				if (userIndexNum == ObjectAbove::enKitchen) {
					m_objectAbove->TakeThings(m_belongings);

					if (m_belongings != nullptr) {				//�����Ƃ̂ł���I�u�W�F�N�g������Ƃ��B(���ꂽ���M�ȊO)�B

						//����Ă�����̂����M�̂Ƃ��B
						if (m_belongings->GetIndentValue() == Belongings::enDish) {
							m_objectAbove->TakeThings(m_belongings);		//����Ă���I�u�W�F�N�g�������B
							m_cacth = m_belongings;							//��xm_cacth�ɔ��B
							m_belongings->PutDishFromKitchen(m_cacth, (Kitchen*)m_objectAbove);		//���M����Ƃ�B
							m_belongings = NewGO<Dish>(0, "dish");			//�V�������M�𐶐�����B
							m_toHave = true;								//�������t���O�B
							m_playerState = enIdleHave;						//�X�e�[�g�ύX�B
						}
					}
				}
			}
		}
	}
}

void Player::CuttingObject()
{
	//todo �Q�[�W��`�悵�Ċg�嗦�𑀍삷��B�@
//	m_gauge = NewGO<Gauge>(0, "gauge");
////	m_objectAbove->SetGaugePosition(m_gauge);
//	//todo ��@���|�I���B
//	CVector3 hoge = m_position;
//	hoge.y -= 150.f;
//	m_gauge->SetPosition(hoge);
//
	m_objectAbove->TakeThings(m_belongings);		//�u���Ă���I�u�W�F�N�g�������B

//	m_gauge->Expansion();
//	if (m_gauge->GetScale()) {		//2D�g�嗦�P�Ȃ�B
		m_belongings->SetState(Belongings::enCutting);	//���Ă���̂�؂��Ă����Ԃɂ���B
//	}
	
}

//����v���C���[�Ɏ������鏈���B
void Player::HoldingKnife()
{
	int boneNum;			//���̔z��̔ԍ���ێ����邽�߂̂��́B
	m_skelton = &m_skinModelRender->GetSkinModel().GetSkeleton();		//�ق˂̃C���X�^���X���擾�B
	boneNum = m_skelton->FindBoneID(L"Bone008");		//�������Bone�̖��O�B
	Bone* m_bone;			//�������W���[�L�[�B

	//���W�����������B
	CVector3 Bonepos;		//���̍��W�B

	m_bone = m_skelton->GetBone(boneNum);			//���̏���n���B

	CMatrix boneRot;						//�{�[���̍s���ێ������B
	boneRot = m_bone->GetMatrix();			//�{�[���̍s������B
	Bonepos.x = boneRot.m[3][0];				//X���B
	Bonepos.y = boneRot.m[3][1];				//Y���B
	Bonepos.z = boneRot.m[3][2];				//Z���B

	CQuaternion Bonerote;			//���̉�]������������B
	Bonerote.SetRotation(boneRot);		//�{�[���̍s�񂩂��]�s��𒊏o�B

	m_knife->SetPosition(Bonepos);			//��ɍ��̍��W�����B
	m_knife->SetRotation(Bonerote);			//��ɍ��̉�]�����B
}