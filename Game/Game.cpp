#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start()
{

	m_title = NewGO<Title>(0, "title");

	return true;
}


void Game::Update()
{


}