#include "stdafx.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(se);
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");			//Gameクラスを検索。
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//画像描画クラスを生成。
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//初期化。
	m_spriteRender->SetPosition(m_position);								//座標更新。
	
	//BGM。
	se = NewGO<Sound>(0, "sound");
	se->Init(L"Assets/sound/BGM/title_overcooked.wav",true);
	se->Play();

	return true;
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonB))			//1Pがボタンを押したとき。
	{
		m_game->SetTitleDeleteFlag(true);		//Deleteフラグを返す。

		//決定音。
		Sound* se2 = NewGO<Sound>(0, "sound");
		se2->Init(L"Assets/sound/soundEffect/decision3.wav", false);
		se2->Play();

		DeleteGO(this);							//クラスを消す。
	}
}