#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	int cuisinePriority = 5;		//�����摜�̃v���C�I���e�B�B

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
	m_foodSheetGenerations = NewGO<FoodSheetGenerations>(3, "foodSheet");
	m_cookingList = NewGO<CookingList>(0, "cookingList");

	return true;
}

//���������B
void OrderGenerations::Generations()
{
	if (m_generationNum < m_orderNumLimit && m_order == false) {		//�����̐�������l��菭�Ȃ��Ƃ��B���A���������Ă��Ȃ��Ƃ��B
		m_orderTimer += 1.f / 60.f;					//�^�C�}�[��i�߂�B
		if (m_orderTimer >= 5.f) {					//5�b�ȏ�o�߂����Ȃ�B
			m_order = true;							//�����t���O��Ԃ��B
			m_orderTimer = 0.f;						//�^�C�}�[�����Z�b�g����B
		}
	}

	if (m_order) {			//�����t���O��true�Ȃ�B
		m_orderSheet[m_orderNumber] = NewGO<OrderSheet>(0, "orderSheet");		//�z��m_order�Ԗڂɒ����V�[�g�𐶐��B
		m_position[m_orderNumber].x = 540.f;			//X���W���w��B
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
	for (int m_orderNumber = 0; m_orderNumber < m_orderNumLimit; m_orderNumber++) {		//�z��̐������[�v����B
		if (m_orderSheet[m_orderNumber] != nullptr) {			//�V�[�g����������Ă�����B
			if (m_position[m_orderNumber].x > m_moveLimit[m_orderNumber]) {		//���W������l�ɒB���Ă��Ȃ�������B
				m_position[m_orderNumber].x -= 20.f;			//X���W���X�V�B	
				m_position[m_orderNumber].y = m_sheet_y;		//Y���W���X�V�B
				m_position[m_orderNumber].z = m_sheet_z;		//Z���W���X�V�B
			}
			m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//�V�[�g�̍��W���X�V�B

			if (m_position[m_orderNumber].x <= m_moveLimit[m_orderNumber]) {	//���W������l�ɒB�������B

				FoodSheetGeneration(m_cookingList->GetFoodType(), m_orderNumber);		//�H�ו��V�[�g�𐶐�����B
				FoodSheetPosUpdate(m_orderNumber);						//�H�ו��V�[�g�̍��W�X�V�����B
			}
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
		m_foodSheetGenerations->FoodSheetGeneration(FoodTypeNum);		//�H�ו��V�[�g�𐶐��B
		m_foodSheetGenerations->SetPosition(m_position[genenum]);		//�������ꂽ�V�[�g�̍��W���w�肵�Ă��B
		m_foodPosY[genenum] = m_position[genenum].y;								//Y���W��ۑ����Ă����B

		m_timeLimitGauge[genenum] = NewGO<TimeLimitGauge>(0, "timelimitgauge");
		m_timeLimitGaugePosition[genenum] = m_position[genenum];
		m_timeLimitGaugePosition[genenum].x -= 55.f;
		m_timeLimitGaugePosition[genenum].y += 20.f;
		m_timeLimitGauge[genenum]->SetPosition(m_timeLimitGaugePosition[genenum]);

		m_foodSheetGenerationFlag[genenum] = true;			//���������̂Ńt���O��Ԃ��B
	}
}

//�H�ו��V�[�g�̍��W�X�V�����B
void OrderGenerations::FoodSheetPosUpdate(int genenum)
{
	if (m_foodPosY[genenum] >= m_foodPosYLimit) {		//���W������l�ɒB���Ă��Ȃ��Ȃ�B
		m_foodPosY[genenum] += -1.f;					//Y���W�𖈃t���[���X�V�B
	}

	else {		//����l�ɒB������B
		Order(genenum);		//���̑��摜���������B
	}

	if (m_foodSheetGenerationFlag) {					//��������Ă�����B
		m_foodSheetGenerations->SetPositionY(m_foodPosY[genenum]);		//���W���X�V����B
	}
}

//���̑��摜�̐��������B
void OrderGenerations::Order(int genenum)
{
	if (m_cuisineSheetFlag[genenum] == false) {			//�����̉摜����������Ă��Ȃ��Ƃ��B
		if (m_cookingList->GetCookingList() == CookingList::enTomatoSoup)		//�쐬������̂��g�}�g�X�[�v�̏ꍇ�B
		{
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
	}
}

void OrderGenerations::Update()
{
	//���������B
	Generations();
	//�ړ������B
	Move();
}

//todo �z�񂲂Ə����Ƃ��ɂ�邱��
/*
	�����t���O��Ԃ��B
	�z��̋󂢂��Ƃ�����l�߂�B
	m_foodPosY�����Z�b�g����B
*/