#include "stdafx.h"
#include "CuttingBoard.h"


CuttingBoard::CuttingBoard()
{
}


CuttingBoard::~CuttingBoard()
{
}

bool CuttingBoard::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/cutting_board/cutting_board.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}


void CuttingBoard::Update()
{


}