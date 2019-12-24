#include "stdafx.h"
#include "FoodSheetGenerations.h"

namespace {
	float XU = 120.f;		//画像のXスケール。
	float YV = 80.f;		//画像のYスケール。
}

FoodSheetGenerations::FoodSheetGenerations()
{
}


FoodSheetGenerations::~FoodSheetGenerations()
{
	DeleteGO(m_spriteRender);
}


bool FoodSheetGenerations::Start()
{
	return true;
}

//食べ物シートの生成処理。
void FoodSheetGenerations::FoodSheetGeneration(int FoodTypeNum)
{
	for (int i = 0; i < FoodTypeNum; i++)
	{
		m_spriteRender = NewGO<SpriteRender>(0, "sprite");
		m_spriteRender->Init(L"Assets/sprite/Food_Sheet3.dds", XU, YV);
		//m_spriteRender->SetPosition(m_position);
		//m_spriteRender->SetScale(m_scale);
		//m_spriteRender->SetRotation(m_rotation);
		SheetPos(FoodTypeNum);
	}
}

void FoodSheetGenerations::SheetPos(int FoodTypeNum)
{
	if (FoodTypeNum == 1) {		//食べ物が一種類のとき。
		m_spriteRender->SetPosition(m_position);
		m_spriteRender->SetScale(m_scale);
		m_spriteRender->SetRotation(m_rotation);
	}
	//todo 高　材料が二種類以上のとき」のシートの生成処理ができていないので作成する。
	else {					//食べ物が二種類以上のとき。
		//一度だけ呼ぶ。
		if (m_changeScaleFlag == false) {			//スケールのY座標を変更していなければ。
			m_scale.x = m_scaleX / FoodTypeNum;		//スケールを計算。	
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
			}

			m_spriteRender->SetPosition(m_position);
			m_spriteRender->SetScale(m_scale);			//スケールを代入。
			m_spriteRender->SetRotation(m_rotation);		//回転を代入。
		}
	}
}

void FoodSheetGenerations::Update()
{
	if (m_spriteRender != nullptr) {
		m_spriteRender->SetPosition(m_position);		//座標更新。
	}
	m_position.y = m_y;
}