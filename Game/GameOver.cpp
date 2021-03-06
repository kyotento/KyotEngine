#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Timer.h"
#include "OrderGenerations.h"
#include "StartCountDown.h"
#include "Pot.h"

namespace {
	float m_size_w = 900.f;
	float m_size_h = 180.f;
}

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}

bool GameOver::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");							//画像生成クラスを生成。
	m_spriteRender->Init(L"Assets/sprite/TimeUp.dds", m_size_w, m_size_h);		//初期化。
	m_spriteRender->SetPosition(m_position);									//画像を生成。
	m_spriteRender->SetScale(m_scale);											//スケールを更新。

	//かんかんかんかん！。
	Sound* sound = NewGO<Sound>(0, "sound");									//サウンドクラス。
	sound->Init(L"Assets/sound/soundEffect/end.wav", false);					//初期化。
	sound->Play();																//再生。

	return true;
}

//スケールの更新処理。
void GameOver::ScaleUpdate()
{
	if (m_scalefloat <= 1.f) {				//スケールが１以下のとき。
		m_scalefloat += 0.02f;				//スケールを拡大。

		m_scale = { m_scalefloat,m_scalefloat,m_scalefloat };		//スケールを代入。
	}
}

//フィールドのものをすべて消す処理。
void GameOver::DeleteField()
{
	//生成されたPlayerを消す処理。
	Player* m_player = nullptr;
	m_player = FindGO<Player>("player");
	if (m_player != nullptr) {
		DeleteGOs("player");
	}

	//タイマーを消す。
	Timer* m_timer = nullptr;
	m_timer = FindGO<Timer>("timer");
	if (m_timer != nullptr) {
		DeleteGO(m_timer);
	}

	//注文シート生成クラスを消す。
	OrderGenerations* m_orderGenerations = nullptr;
	m_orderGenerations = FindGO<OrderGenerations>("ordergenerations");
	if (m_orderGenerations != nullptr) {
		DeleteGO(m_orderGenerations);
	}

	//カウントダウンクラスを消す。
	StartCountdown* m_startCountDown = FindGO<StartCountdown>("startcountdown");
	if (m_startCountDown != nullptr) {
		DeleteGO(m_startCountDown);
	}

	//ポットを消す。
	DeleteGOs("pot");

}

void GameOver::Update()
{
	ScaleUpdate();			//スケールを更新。

	if (m_spriteRender != nullptr) {				//画像が生成されているとき。
		m_spriteRender->SetScale(m_scale);			//スケールを更新。
		m_timer += gametime().GetFrameDeltaTime();		//タイマーを更新。
	}

	if (m_timer >= 5.f) {			//タイマーが３以上のとき。

		//todoここにFadeを入れる、
		DeleteField();				//フィールドを消す。		

		m_result = NewGO<Result>(0, "result");			//リザルトを表示。

		DeleteGO(this);				//クラスを消す。
	}
}
