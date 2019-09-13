#include "stdafx.h"
#include "Desk.h"


Desk::Desk()
{
}


Desk::~Desk()
{
}

bool Desk::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Desk.cmo");

	return true;
}

void Desk::Update()
{

}
