#include "stdafx.h"
#include "StageObject.h"
#include "Desk.h"
#include "DishHold.h"

StageObject::StageObject()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");

}


StageObject::~StageObject()
{
	if (m_skinModelRender != nullptr) {
		DeleteGO(m_skinModelRender);
	}
	if (m_skinModelRenderCollidion != nullptr) {
		DeleteGO(m_skinModelRenderCollidion);
	}
}


bool StageObject::Start()
{



	return true;
}


void StageObject::Update()
{


}