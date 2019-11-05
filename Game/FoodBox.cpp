#include "stdafx.h"
#include "FoodBox.h"


FoodBox::FoodBox()
{
	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "coll");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBox.cmo");


}


FoodBox::~FoodBox()
{
}


bool FoodBox::Start()
{

	return true;
}


void FoodBox::Update()
{

}
