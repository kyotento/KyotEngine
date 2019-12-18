#include "stdafx.h"
#include "FoodSheetGenerations.h"

namespace {
	float XU = 140.f;
}

FoodSheetGenerations::FoodSheetGenerations()
{
}


FoodSheetGenerations::~FoodSheetGenerations()
{
}


bool FoodSheetGenerations::Start()
{
	return true;
}

//食べ物シートの生成処理。
void FoodSheetGenerations::FoodSheetGeneration(int FoodTypeNum)
{
	for (int i = 0; i <= FoodTypeNum; i++)
	{
		m_spriteRender[i] = NewGO<SpriteRender>(0, "sprite");
		m_spriteRender[i]->Init(L"Assets/sprite/Food_Sheet3.dds", XU, 80.f);
		m_spriteRender[i]->SetPosition(m_position);
		m_spriteRender[i]->SetScale(m_position);
		m_spriteRender[i]->SetRotation(m_rotation);
	}
}

void FoodSheetGenerations::SheetPos(int FoodTypeNum)
{
	if (FoodTypeNum == 1) {		//食べ物が一種類のとき。
		m_spriteRender[0]->SetPosition(m_position);
		m_spriteRender[0]->SetScale(m_scale);
		m_spriteRender[0]->SetRotation(m_rotation);
	}

	else {					//食べ物が二種類以上のとき。
		//一度だけ呼ぶ。
		if (m_changeScaleFlag == false) {			//スケールのY座標を変更していなければ。
			m_scale.y = m_scaleY / FoodTypeNum;		//スケールを計算。	
			m_changeScaleFlag = true;				//変更したのでフラグを返す。
		}

		for (int i = 0; i <= FoodTypeNum; i++) {			//食べ物の種類だけループする。
			float x;
			if (FoodTypeNum == 1) {
				x = XU / FoodTypeNum / 2;
				if (i == 0) {
					m_position.x -= x;
				}
				if (i == 1) {
					m_position.x += x * 2;
				}
					m_spriteRender[i]->SetPosition(m_position);
			}

			m_spriteRender[i]->SetScale(m_scale);			//スケールを代入。
			m_spriteRender[i]->SetRotation(m_rotation);		//回転を代入。
		}
	}
}

void FoodSheetGenerations::Update()
{

}