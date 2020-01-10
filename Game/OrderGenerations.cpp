#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	int cuisinePriority = 5;		//�����摜�̎��s�D��x�B

	float cuisineSize = 50.f;		//�����̉摜�̃T�C�Y�B
	float foodSize = 30.f;			//�H�ו��̉摜�̃T�C�Y�B
}

OrderGenerations::OrderGenerations()
{
}

OrderGenerations::~OrderGenerations()
{
}

bool OrderGenerations::Start()
{
//	m_foodSheetGenerations = NewGO<FoodSheetGenerations>(0, "foodSheet");
	m_cookingList = NewGO<CookingList>(0, "cookingList");

	return true;
}

//���������B
void OrderGenerations::Generations()
{
	if (m_generationNum < m_orderNumLimit && m_order == false) {		//�����̐�������l��菭�Ȃ��Ƃ��B���A���������Ă��Ȃ��Ƃ��B
		m_orderTimer += 1.f / 60.f;					//�^�C�}�[��i�߂�B
		if (m_orderTimer >= 10.f) {					//10�b�ȏ�o�߂����Ȃ�B
			m_order = true;							//�����t���O��Ԃ��B
			m_orderTimer = 0.f;						//�^�C�}�[�����Z�b�g����B
		}
	}

	if (m_order) {			//�����t���O��true�Ȃ�B
		m_orderSheet[m_orderNumber] = NewGO<OrderSheet>(0, "orderSheet");		//�z��m_order�Ԗڂɒ����V�[�g�𐶐��B
		m_position[m_orderNumber].x = m_sheet_x;		//X���W���w��B
		m_position[m_orderNumber].y = m_sheet_y;		//Y���W���w��B
		m_position[m_orderNumber].z = m_sheet_z;		//Z���W���w��B
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//���W���X�V�B

		m_generationNum += 1;		//�����������Z����B
		m_orderNumber += 1;			//�����ԍ���ύX����B
		m_order = false;			//�������ꂽ�̂Ńt���O��Ԃ��B
	}
}

//�ړ������B
void OrderGenerations::Move()
{
	for (int m_orderNum = 0; m_orderNum < m_orderNumLimit; m_orderNum++) {		//�z��̐������[�v����B
		if (m_orderSheet[m_orderNum] != nullptr) {				//�V�[�g����������Ă�����B
			if (m_cuisineSheetFlag[m_orderNum] == false) {		//�����V�[�g����������Ă��Ȃ��Ƃ�(��x�����W������l�ɒB���Ă��Ȃ��Ƃ�)�B
				if (m_position[m_orderNum].x > m_moveLimit[m_orderNum]) {		//���W������l�ɒB���Ă��Ȃ�������B
					m_position[m_orderNum].x -= 20.f;			//X���W���X�V�B	
					m_position[m_orderNum].y = m_sheet_y;		//Y���W���X�V�B
					m_position[m_orderNum].z = m_sheet_z;		//Z���W���X�V�B
				}
				m_orderSheet[m_orderNum]->SetPosition(m_position[m_orderNum]);		//�V�[�g�̍��W���X�V�B
			}

			if (m_position[m_orderNum].x <= m_moveLimit[m_orderNum]) {	//���W������l�ɒB�������B
				if (m_cuisineDecision[m_orderNum] == false) {			//���������肵�Ă��Ȃ��Ƃ��B
					m_dishName[m_orderNum] = m_cookingList->OrderSetting();			//�����������_���Ɍ��߂�B
					m_cookingList->CookingInformations();							//�����̏����i�[�B
					m_foodType[m_orderNum] = m_cookingList->GetFoodType();			//�����ɕK�v�ȐH�ו��̎�ނ��擾�B
					m_cuisineDecision[m_orderNum] = true;				//���������肵���̂Ńt���O��Ԃ��B
				}

				FoodSheetGeneration(m_foodType[m_orderNum], m_orderNum);		//�H�ו��V�[�g�𐶐�����B
				FoodSheetPosUpdate(m_orderNum);						//�H�ו��V�[�g�̍��W�X�V�����B
				m_timeLimitGauge[m_orderNum]->ChangeScale();			//�Q�[�W�̊g�又���B
			}
			
			/// <summary>
			/// ��ɌĂ΂�鏈���͂����ɏ����B
			/// </summary>
			DeleteOrder(m_orderNum);			//�V�[�g�����������B
			TimeLimitOrder(m_orderNum);			//���Ԑ����𒴂��Ă��܂��������̏����B
		//	ShakeOrder(m_orderNum);				//�����[��h�炷�����B
		//	PositionUpdate(m_orderNum);			//���W�X�V�B
		}
	}
}

//�����Ɏg�p����H�ו��������V�[�g�B
void OrderGenerations::FoodSheetGeneration(int FoodTypeNum, int genenum)
{
	//���W�X�V�����B
	m_foodSheetPosition[genenum].x = m_position[genenum].x;
	m_foodSheetPosition[genenum].y = m_foodPosY[genenum];
	m_foodSheetPosition[genenum].z = m_position[genenum].z;

	if (m_foodSheetGenerationFlag[genenum] == false) {		//�H�ו��V�[�g�𐶐����Ă��Ȃ�������B
		m_foodSheetGenerations[genenum] = NewGO<FoodSheetGenerations>(0, "foodsheetgenerations");
		m_foodSheetGenerations[genenum]->FoodSheetGeneration(FoodTypeNum);			//�H�ו��V�[�g�𐶐��B
		m_foodSheetGenerations[genenum]->SetPosition(m_position[genenum]);			//�������ꂽ�V�[�g�̍��W���w�肵�Ă��B
		m_foodPosY[genenum] = m_position[genenum].y;								//Y���W��ۑ����Ă����B

		m_timeLimitGauge[genenum] = NewGO<TimeLimitGauge>(0, "timelimitgauge");		//�Q�[�W�����B
		m_timeLimitGaugePosition[genenum] = m_position[genenum];					//�V�[�g�̍��W�����B
		m_timeLimitGaugePosition[genenum].x -= 55.f;								//�Q�[�W����povot���Ⴄ�̂ŏ������Ɉړ�����B
		m_timeLimitGaugePosition[genenum].y += 20.f;								//������ɁB
		m_timeLimitGauge[genenum]->SetPosition(m_timeLimitGaugePosition[genenum]);	//���W�X�V�����B

		m_foodSheetGenerationFlag[genenum] = true;			//���������̂Ńt���O��Ԃ��B
	}
}

//�H�ו��V�[�g�̍��W�X�V�����B
void OrderGenerations::FoodSheetPosUpdate(int genenum)
{
	if (m_foodPosY[genenum] >= m_foodPosYLimit) {		//���W������l�ɒB���Ă��Ȃ��Ȃ�B
		m_foodPosY[genenum] += -1.f;					//Y���W�𖈃t���[���X�V�B
	}

	if (m_foodPosY[genenum] < m_foodPosYLimit) {	//����l�ɒB������B
		Order(genenum);		//���̑��摜���������B
	}

	if (m_foodSheetGenerationFlag) {					//��������Ă�����B
		m_foodSheetGenerations[genenum]->SetPositionY(m_foodPosY[genenum]);		//���W���X�V����B
	}
}

//���̑��摜�̐��������B
void OrderGenerations::Order(int genenum)
{
	if (m_cuisineSheetFlag[genenum] == false) {			//�����̉摜����������Ă��Ȃ��Ƃ��B
		if (m_cookingList->GetCookingList() == CookingList::enTomatoSoup){		//�쐬������̂��g�}�g�X�[�v�̏ꍇ�B

			//�g�}�g�X�[�v�̉摜��`�悷��B
			m_spriteRenderCuisine[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");						//�����̉摜�����B
			m_spriteRenderCuisine[genenum]->Init(L"Assets/sprite/TomatoSoup.dds", cuisineSize, cuisineSize);		//�������B
			m_spriteRenderCuisine[genenum]->SetPosition(m_position[genenum]);										//���W�X�V�B

			m_spriteRenderFoods[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");							//�H�ނ̉摜�����B
			m_spriteRenderFoods[genenum]->Init(L"Assets/sprite/Tomato.dds", foodSize, foodSize);					//�������B
			m_spriteRenderFoods[genenum]->SetPosition(m_foodSheetPosition[genenum]);								//���W�X�V�B

			m_spriteRenderCuisineMethod[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");					//�������@�̉摜�����B
			m_spriteRenderCuisineMethod[genenum]->Init(L"Assets/sprite/pot.dds", foodSize, foodSize);				//�������B
			m_kitchenWarePosition[genenum] = m_foodSheetPosition[genenum];											//�V�[�g�̍��W�����B
			m_kitchenWarePosition[genenum].y -= 25.f;																//�������ɍ��W���ړ��B
			m_spriteRenderCuisineMethod[genenum]->SetPosition(m_kitchenWarePosition[genenum]);						//���W�X�V�B

			m_cuisineSheetFlag[genenum] = true;			//�����̉摜���������ꂽ�̂Ńt���O��Ԃ��B
		}

		if (m_cookingList->GetCookingList() == CookingList::enOnionSoup){		//�쐬������̂��ʂ˂��X�[�v�̂Ƃ��B

			//�ʂ˂��X�[�v�̉摜��`�悷��B
			m_spriteRenderCuisine[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");						//�����̉摜�����B
			m_spriteRenderCuisine[genenum]->Init(L"Assets/sprite/OnionSoup.dds", cuisineSize, cuisineSize);			//�������B
			m_spriteRenderCuisine[genenum]->SetPosition(m_position[genenum]);										//���W�X�V�B

			m_spriteRenderFoods[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");							//�H�ނ̉摜�����B
			m_spriteRenderFoods[genenum]->Init(L"Assets/sprite/Onion.dds", foodSize, foodSize);						//�������B
			m_spriteRenderFoods[genenum]->SetPosition(m_foodSheetPosition[genenum]);								//���W�X�V�B

			m_spriteRenderCuisineMethod[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");					//�������@�̉摜�����B
			m_spriteRenderCuisineMethod[genenum]->Init(L"Assets/sprite/pot.dds", foodSize, foodSize);				//�������B
			m_kitchenWarePosition[genenum] = m_foodSheetPosition[genenum];											//�V�[�g�̍��W�����B
			m_kitchenWarePosition[genenum].y -= 25.f;																//�������ɍ��W���ړ��B
			m_spriteRenderCuisineMethod[genenum]->SetPosition(m_kitchenWarePosition[genenum]);						//���W�X�V�B

			m_cuisineSheetFlag[genenum] = true;			//�����̉摜���������ꂽ�̂Ńt���O��Ԃ��B
		}
	}
}

//�����[�����������B
void OrderGenerations::DeleteOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {				//�Q�[�W����������Ă���Ƃ��B
		if (m_timeLimitGauge[genenum]->GetTimeLimitFlag() == true) {			//todo ���@���Ԑ������������B
			DeleteGO(m_timeLimitGauge[genenum]);				//�Q�[�W������
			m_timeLimitGauge[genenum] = nullptr;				//�Q�[�W�̃C���X�^���X��j���B
			DeleteGO(m_orderSheet[genenum]);					//�����V�[�g�������B
			m_orderSheet[genenum] = nullptr;					//�����V�[�g�̃C���X�^���X��j���B
			DeleteGO(m_foodSheetGenerations[genenum]);			//�H�ו��V�[�g�������B
			m_foodSheetGenerations[genenum] = nullptr;			//�H�ו��V�[�g�̃C���X�^���X��j���B
			DeleteGO(m_spriteRenderCuisine[genenum]);			//�����̉摜�������B
			m_spriteRenderCuisine[genenum] = nullptr;			//�����̉摜�̃C���X�^���X��j���B
			DeleteGO(m_spriteRenderFoods[genenum]);				//�H�ނ̉摜�������B
			m_spriteRenderFoods[genenum] = nullptr;				//�H�ނ̉摜�̃C���X�^���X��j��
			DeleteGO(m_spriteRenderCuisineMethod[genenum]);		//�������@�̉摜�������B
			m_spriteRenderCuisineMethod[genenum] = nullptr;		//�������@�̉摜�̃C���X�^���X��j���B
		}
	}
}

//�����񂹂�����������Ă��܂��������̏����B
void OrderGenerations::TimeLimitOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {				//�Q�[�W����������Ă���Ƃ��B
		if (m_timeLimitGauge[genenum]->GetTimeLimitFlag() == true) {			//���Ԑ������������B
			m_timeLimitGauge[genenum]->SetScale(1.f);				//�摜�̃X�P�[�����P�ɖ߂��B
		}
	}
}

//�����[��h�炷�����B
void OrderGenerations::ShakeOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {
		if (m_timeLimitGauge[genenum]->GetGaugeState() == TimeLimitGauge::en10Less) {		//�Q�[�W�̏�Ԃ��g�嗦�P�O�p�[�Z���g�ȉ��̂Ƃ��B
			//for (int i = 0; i <= 3; i++) {
			//	if (i == 0) {
			//		m_position[genenum].x += 5.f;
			//	}
			//	if (i == 1) {
			//		m_position[genenum].x -= 5.f;
			//	}
			//	if (i == 2) {
			//		m_position[genenum].x -= 5.f;
			//	}
			//	if (i == 3) {
			//		m_position[genenum].x += 5.f;
			//		i = 0;
			//	}
			//	m_orderSheet[genenum]->SetPosition(m_position[genenum]);			//�������ꂽ�V�[�g�̍��W���w�肵�Ă��B
			//}
		}
	}
}

void OrderGenerations::PositionUpdate(int genenum)
{
	m_foodSheetPosition[genenum].x = m_position[genenum].x;
	m_foodSheetPosition[genenum].y = m_foodPosY[genenum];
	m_foodSheetPosition[genenum].z = m_position[genenum].z;
}

void OrderGenerations::Update()
{
	//���������B
	Generations();
	//�ړ������B
	Move();

	m_delivery = FindGO<Delivery>("delivery");				//�󂯓n�����̃C���X�^���X����������B
	m_deliveryCuisine = m_delivery->GetDeliveryDishCuisine();		//�[�i���ꂽ�������������đ������B
}

//todo �z�񂲂Ə����Ƃ��ɂ�邱��
/*
	�����t���O��Ԃ��B
	�z��̋󂢂��Ƃ�����l�߂�B
	m_foodPosY�����Z�b�g����B
*/
