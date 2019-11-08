#include "stdafx.h"
#include "Player.h"

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
	m_characon.Init(45.f, 50.f, m_characonPos);
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{


	return true;
}

void Player::Update()
{

}

void Player::Movement(int a)
{
	
	stickPower.x = g_pad[a].GetLStickXF();
	stickPower.y = 0.f;
	stickPower.z = g_pad[a].GetLStickYF();

	if (stickPower.Length() > m_noLongerZero)
	{
		m_oldPosition = m_position;

		m_move = stickPower * m_moveSpeed;
		m_move.y -= m_fallSpeed;
		m_position = m_characon.Execute(1.0, m_move);

		if (m_toHave == false) {
			m_state = enRun;	//�ړ���ԁB
		}
	}

	else {
		if (m_toHave == false) {
			m_state = enIdle;	//�ҋ@��ԁB
		}
	}


		
	m_skinModelRender->SetPosition(m_position);

}

void Player::Rotation()
{
	//�ړ����Ă��Ȃ��Ȃ�B
	//if (m_position.x == m_oldPosition.x && m_position.z == m_oldPosition.z)
	//{
	//	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
	//	m_skinModelRender->SetRotation(m_rotation);
	//}


	YisDie = m_move;
	YisDie.y = 0.0f;

	//�ړ����Ă���Ȃ�B
	if (YisDie.Length() > m_noLongerZero){
		
		YisDie.Normalize();
		m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
		m_skinModelRender->SetRotation(m_rotation);

	}

}

void Player::ForwardDirectionRay(int a)
{
	m_objectAbove = nullptr;		//����u����Null�ɂȂ�B

	CVector3 m_movesecond;							//ray�̒����B
	m_movesecond = m_move * m_distance;				//ray�̒�����ݒ�B
	btVector3 start(m_position.x, m_position.y + 10, m_position.z);		//btVector3�^�ɕϊ��B
	m_ray = { m_position.x + m_movesecond.x , m_position.y + m_movesecond.y, m_position.z + m_movesecond.z };		//ray�̏I�_���w��B
	btVector3 end(m_ray.x, m_ray.y + 10, m_ray.z);						//btVector3�^�ɕϊ��B

	if (m_movesecond.Length() > m_noLongerZero) {			//ray�̒������O�ȏ�̂Ƃ��B
		btCollisionWorld::ClosestRayResultCallback rayRC(start, end);	//rayRC�ɏ�񂪓����Ă���B
		g_physics.GetDynamicWorld()->rayTest(start, end, rayRC);			//�Փ˔���B

		if (rayRC.hasHit())			//�Փ˂��Ă���Ȃ�B
		{
			////Desk�B
			//if (rayRC.m_collisionObject->getUserIndex() == 1) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			//
			////Delivery�B
			//if (rayRC.m_collisionObject->getUserIndex() == 2) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////DishHold�B
			//if (rayRC.m_collisionObject->getUserIndex() == 3) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////DustBox�B
			//if (rayRC.m_collisionObject->getUserIndex() == 4) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////GasStove�B
			//if (rayRC.m_collisionObject->getUserIndex() == 5) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////Kitchen�B
			//if (rayRC.m_collisionObject->getUserIndex() == 6){
			//	rayRC.m_collisionObject->getUserPointer(); 
			//}
			////OnionBox�B
			//if (rayRC.m_collisionObject->getUserIndex() == 7) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////TomatoBox�B
			//if (rayRC.m_collisionObject->getUserIndex() == 8) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}

			for (int i = 1; i <= m_objectNum; i++)
			{
				int n = rayRC.m_collisionObject->getUserIndex();	//n�ɓ������Ă���I�u�W�F�N�g��Index�����B
				if (rayRC.m_collisionObject->getUserIndex() == i) {	//�Փ˂����I�u�W�F�N�g��i�Ԗڂ��������B
					rayRC.m_collisionObject->getUserPointer();		//�Փ˂��Ă�����̂̃|�C���^��Ԃ��B
					m_objNum = i;									//�I�u�W�F�N�g�i���o�[�i�[�ɂ�i�����B
					m_objectAbove = (ObjectAbove*)rayRC.m_collisionObject->getUserPointer();

					if (i == 1) {		//���̂Ƃ��B

						m_desk = (Desk*)rayRC.m_collisionObject->getUserPointer();	//(Desk*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

					}

					if (i == 2) {		//�J�E���^�[�̂Ƃ��B

						m_delivery = (Delivery*)rayRC.m_collisionObject->getUserPointer();	

					}

					if (i == 3) {		//���M�u���̂Ƃ��B

						m_dishHold = (DishHold*)rayRC.m_collisionObject->getUserPointer();

					}

					if (i == 4) {		//�S�~���̂Ƃ��B

						m_dustbox = (DustBox*)rayRC.m_collisionObject->getUserPointer();

					}

					if (i == 5) {		//�K�X�R�����̂Ƃ��B

						m_gasStove = (GasStove*)rayRC.m_collisionObject->getUserPointer();	//(GasStove*)�ɓ��������I�u�W�F�N�g�̃|�C���^������B

					}

					if (i == 6) {		//�L�b�`���̂Ƃ��B

						m_kitchen = (Kitchen*)rayRC.m_collisionObject->getUserPointer();

						//todo ��@�� ���ۂ͉��ꂽ���M������Ƃ��B
						if (g_pad[0].IsPress(enButtonB))
						{
							m_state = enWashing;
						}
					}

					if (i == 7) {		//�ʂ˂��{�b�N�X�̂Ƃ��B

						m_onionBox = (OnionBox*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {
							if (g_pad[a].IsTrigger(enButtonA) && m_objectAbove->GetState() == 0)
							{
								m_belongings = m_onionBox->NewFood(a);		//�ʂ˂��𐶐�����B�����������̂̏���m_belongings�ɑ���B

								m_state = enIdleHave;
							}
						}
					}

					if (i == 8) {		//�g�}�g�{�b�N�X�̂Ƃ��B

						m_tomatoBox = (TomatoBox*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
							if (g_pad[a].IsTrigger(enButtonA) && m_objectAbove->GetState() == 0)
							{
								m_belongings = m_tomatoBox->NewFood(a);	//�g�}�g�𐶐�����B�����������̂̏���m_belongings�ɑ���B

								m_state = enIdleHave;
							}
						}
					}

					if (i == 9) {		//�܂Ȕ̂Ƃ��B

						m_cuttingDesk = (CuttingDesk*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {		//���������Ă��Ȃ��Ƃ��B
							if (g_pad[a].IsPress(enButtonX) && m_objectAbove->GetState() == 1)		//X���������Ƃ��A��������Ă���Ƃ��B
							{
								m_state = enCutting;
							}
						}
					}
				}
			}
		}
	}
}

void Player::ActionProcessing(int a)
{

	switch (m_state)
	{
	case enIdle:		//�ҋ@��Ԃ̂Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Idle, m_transitionTime);
		m_animationClips[enanimationClip_Idle].SetLoopFlag(true);

		m_toHave = false;

		PickUpObjects(a);		//�I�u�W�F�N�g���������B

		break;

	case enRun:			//�ړ����Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Run, m_transitionTime);
		m_animationClips[enanimationClip_Run].SetLoopFlag(true);

		m_toHave = false;

		PickUpObjects(a);		//�I�u�W�F�N�g���������B

		break;

	case enCutting:		//����؂��Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Cut, m_transitionTime);
		m_animationClips[enanimationClip_Cut].SetLoopFlag(true);

		HoldingKnife();

		CuttingObject();		//����؂�B

		m_toHave = false;

		break;

	case enWashing:		//�M�����Ă���Ƃ��B

		m_skinModelRender->PlayAnimation(enanimationClip_Washing, m_transitionTime);
		m_animationClips[enanimationClip_Washing].SetLoopFlag(true);

		m_toHave = false;

		break;

	case enIdleHave:		//���������đҋ@���Ă���B

		m_skinModelRender->PlayAnimation(enanimationClip_IdleHave, m_transitionTime);
		m_animationClips[enanimationClip_IdleHave].SetLoopFlag(true);

		m_toHave = true;

		if (stickPower.Length() > m_noLongerZero){			//�ړ��������B
			m_state = enRunHave;
		}

		SetFoodPosition();
		PutObjects(a);

		break;

	case enRunHave:		//���������đ����Ă���B

		m_skinModelRender->PlayAnimation(enanimationClip_RunHave, m_transitionTime);
		m_animationClips[enanimationClip_RunHave].SetLoopFlag(true);

		m_toHave = true;

		if (stickPower.Length() > m_noLongerZero == false) {		//�ړ����ĂȂ������Ƃ��B
			m_state = enIdleHave;
		}

		SetFoodPosition();
		PutObjects(a);

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

void Player::PutObjects(int a)
{
	//todo ���H�B���������̂�������悤�ɂȂ�܂ł̃^�C�}�[�B
	m_putTimer -= 0.1f;

	if (g_pad[a].IsTrigger(enButtonA) && m_putTimer <= 0.f)		//A�{�^�����������Ƃ����A���������Ă����莞�Ԃ��o�߂������B
	{
		if (m_objectAbove != nullptr) {					//����u����I�u�W�F�N�g���ڂ̑O�ɂ���Ƃ��B

			//�I�u�W�F�N�g�ɉ�������Ă��Ȃ��Ƃ��B
			if (m_objectAbove->GetState() == 0) {		

				//�����Ă�����̂��H�ו��̂Ƃ��B
				if (m_belongings->GetIndentValue() == 0) {		
					if (m_objNum == 1 || m_objNum == 4 || m_objNum == 7 || m_objNum == 8 || m_objNum == 9) {		//�H�ו����u����I�u�W�F�N�g���ǂ����B
						m_objectAbove->PutThings(m_belongings);		//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
						m_objectAbove->SetState(1);					//����u�����I�u�W�F�N�g�̃X�e�[�g��ύX����B
						m_state = enIdle;							//�v���C���[�̃X�e�[�g��ҋ@��ԂɁB
					}
				}

				//�����Ă�����̂��������̏ꍇ�B
				if (m_belongings->GetIndentValue() == 1) {		
					if (m_objNum == 1 || m_objNum == 5 || m_objNum == 7 || m_objNum == 8) {		//�������u����I�u�W�F�N�g���ǂ����B
						m_objectAbove->PutThings(m_belongings);		//�ݒu���̍��W�ɃI�u�W�F�N�g�̍��W�����B
						m_objectAbove->SetState(1);					//����u�����I�u�W�F�N�g�̃X�e�[�g��ύX����B
						m_state = enIdle;							//�v���C���[�̃X�e�[�g��ҋ@��ԂɁB
					}
				}
			}

			//�I�u�W�F�N�g�ɉ�������Ă���Ƃ��B
			if (m_objectAbove->GetState() == 1){

				if (m_belongings->GetIndentValue() == 0) {			//�����Ă�����̂��H�ו��̂Ƃ��B
					if (m_belongings->GetState() == 2) {			//�����Ă���I�u�W�F�N�g���؂��Ă���Ƃ��B
					//	m_objectAbove->TakeThings(m_belongings);	//����Ă���I�u�W�F�N�g����������B
						//todo ��@����Ă�����̂������������ꍇ�A�؂��Ă�����̂�u���B
						if (m_belongings->GetIndentValue() == 1) {
							//todo ��@����Ă��钲������Kari�֐����ĂԁB�����Ď����Ă�����̂�����(�����t��)�B
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

void Player::PickUpObjects(int a)
{
	if (g_pad[a].IsTrigger(enButtonA))						//A�{�^�����������Ƃ��B
	{
		if (m_objectAbove != nullptr) {						//�ڂ̑O�ɃI�u�W�F�N�g������Ƃ��B
			if (m_objectAbove->GetState() == 1) {			//�I�u�W�F�N�g�ɉ�������Ă���Ƃ��B
				m_objectAbove->TakeThings(m_belongings);	//����Ă���I�u�W�F�N�g�������B
				SetFoodPosition();							//�����Ă�����̂̍��W���w��B
				m_objectAbove->SetState(0);					//�����Ƃ����I�u�W�F�N�g�̃X�e�[�g��ύX����B
				m_toHave = true;							//�������t���O�B
				m_state = enIdleHave;						//�X�e�[�g�ύX�B
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
//	m_objectAbove->TakeThings(m_belongings);
//	m_gauge->Expansion();
//	if (m_gauge->GetScale()) {		//2D�g�嗦�P�Ȃ�B
		m_belongings->SetState(2);	//���Ă���̂�؂��Ă����Ԃɂ���B
//	}
	
}

//todo �Z�@����v���C���[�Ɏ�������B
void Player::HoldingKnife()
{
	int a;
	m_skelton = &m_skinModelRender->GetSkinModel().GetSkeleton();
	a = m_skelton->FindBoneID(L"Bone008");		//�������Bone�̖��O�B
	Bone* m_bone;

	//���W�����������B
	CVector3 pos;

	m_bone = m_skelton->GetBone(a);

	CMatrix pp;
	pp = m_bone->GetMatrix();
	pos.x = pp.m[3][0];
	pos.y = pp.m[3][1];
	pos.z = pp.m[3][2];

	CQuaternion rote;			//���̉�]������������B
	rote.SetRotation(pp);		//�{�[���̍s�񂩂��]�s��𒊏o�B
	
	if (m_knifeflag == false) {
		m_knife = NewGO<Knife>(0, "knife");
		m_knifeflag = true;
	}

	m_knife->SetPosition(pos);			//��ɍ��̍��W�����B
	m_knife->SetRotation(rote);			//��ɍ��̉�]�����B
}