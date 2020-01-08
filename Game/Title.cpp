#include "stdafx.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");			//Gameクラスを検索。
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//画像描画クラスを生成。
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//初期化。
	m_spriteRender->SetPosition(m_position);								//座標更新。
	
	return true;
}

void Title::Update()
{
	if (g_pad[0].IsPress(enButtonB))			//1Pがボタンを押したとき。
	{
		m_game->SetTitleDeleteFlag(true);		//Deleteフラグを返す。
		DeleteGO(this);							//クラスを消す。
	}
}