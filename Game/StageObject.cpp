#include "stdafx.h"
#include "StageObject.h"
#include "Desk.h"

StageObject::StageObject()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");

}


StageObject::~StageObject()
{
	if (m_skinModelRender != nullptr) {
		DeleteGO(m_skinModelRender);
	}
}


bool StageObject::Start()
{



	return true;
}


void StageObject::Update()
{


}