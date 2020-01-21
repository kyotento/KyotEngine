#include "stdafx.h"
#include "Title.h"

namespace {
	CVector2 fontPos = { 100.f,-200.f};				//フォントの座標。
	CVector2 fontPos2 = { 100.f,-300.f};			//フォントの座標。
}

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(se);
	DeleteGO(m_fontRender);
	DeleteGO(m_fontRender2);
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");			//Gameクラスを検索。
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//画像描画クラスを生成。
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//初期化。
	m_spriteRender->SetPosition(m_position);								//座標更新。

	//フォントを生成。
	m_fontRender = NewGO<FontRender>(0, "fontrender");			//フォントクラス。
	m_fontRender->SetText(L"Bぼたんをおしてね");				//テキストの指定。
	m_fontRender->SetPosition(fontPos);							//座標を指定。
		
	m_fontRender2 = NewGO<FontRender>(0, "fontrender");			//フォントクラス。
	m_fontRender2->SetText(L"BGM::MusMus");						//テキストの指定。
	m_fontRender2->SetPosition(fontPos2);						//座標の指定。
	
	//BGM。
	se = NewGO<Sound>(0, "sound");								//サウンドクラス。
	se->Init(L"Assets/sound/BGM/title_overcooked.wav",true);	//初期化。
	se->Play();													//再生。

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