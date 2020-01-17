#include "stdafx.h"
#include "StartCountdown.h"

namespace {
	float m_ready_w = 720.f;		//Ready画像の幅。
	float m_ready_h = 180.f;		//Ready画像の高さ。
	float m_start_w = 360.f;		//Start画像の幅。
	float m_start_h = 180.f;		//Start画像の高さ。
}

StartCountdown::StartCountdown()
{
}


StartCountdown::~StartCountdown()
{
	if (m_spriteRenderReady != nullptr) {		//生成されていたら。
		DeleteGO(m_spriteRenderReady);			//消す。
	}
	if (m_spriteRenderStart != nullptr) {		//生成されていたら。
		DeleteGO(m_spriteRenderStart);			//消す。
	}
}

bool StartCountdown::Start()
{

	return true;
}

//スケールの更新処理。
void StartCountdown::ScaleUpdate()
{
	if (m_scale < 1.f) {			//スケールが１以下のとき。
		m_scale += 0.05f;			//スケールを加算。
	}

	//todo 分けた意味ない説。
	m_scaleReady = { m_scale,m_scale,m_scale };			//Readyのスケールを変更。
	m_scaleStart = { m_scale,m_scale,m_scale };			//Startのスケールを変更。

}

void StartCountdown::Update()
{
	if (m_newReady == false) {			//Renadyが一度も生成されていないとき。
		m_spriteRenderReady = NewGO<SpriteRender>(0, "sprite");								//スプライトクラスを生成。
		m_spriteRenderReady->Init(L"Assets/sprite/ready.dds", m_ready_w, m_ready_h);		//初期化。
		m_spriteRenderReady->SetPosition(m_position);										//座標更新。
		m_spriteRenderReady->SetScale(m_scaleReady);										//スケールを更新。
		m_newReady = true;				//生成されたのフグを返す。
	}

	//スケールの更新処理。
	ScaleUpdate();

	if (m_spriteRenderReady != nullptr) {							//Readyの画像が生成されていたら。
		m_spriteRenderReady->SetScale(m_scaleReady);				//スケールを更新。

		if (m_scale >= 1.f) {										//スケールが１以上のとき。
			m_deleteTimer += gametime().GetFrameDeltaTime();		//タイマーを更新。
			if (m_deleteTimer >= 1.f) {								//1秒以上経過した時。
				DeleteGO(m_spriteRenderReady);						//Readyの画像を消す。
				m_spriteRenderReady = nullptr;						//インスタンスを破棄。
				m_scale = 0.f;										//スケールを初期化する。
				m_deleteTimer = 0.f;								//タイマーを初期化。
			}
		}
	}

	if (m_spriteRenderReady == nullptr && m_newReady) {				//Readyの画像のインスタンスがnull且つ、一度生成されていた時。
		if (m_newStart == false) {			//Startが一度も生成されていないとき。
			m_spriteRenderStart = NewGO<SpriteRender>(0, "sprite");								//スプライトクラスを生成。
			m_spriteRenderStart->Init(L"Assets/sprite/start.dds", m_start_w, m_start_h);		//初期化。
			m_spriteRenderStart->SetPosition(m_position);										//座標を指定。
			m_spriteRenderStart->SetScale(m_scaleStart);										//スケールを更新。
			m_newStart = true;																	//一度生成されたのでフラグを返す。
		}	

		if (m_newStart) {			//一度生成されてたら。
			if (m_spriteRenderStart != nullptr) {							//Startの画像を生成していたら。
				m_spriteRenderStart->SetScale(m_scaleStart);				//スケールを更新。
				if (m_scale >= 1.f) {			//スケールが１以上のとき。
					m_deleteTimer += gametime().GetFrameDeltaTime();		//タイマーを更新。
					if (m_deleteTimer >= 1.f) {								//タイマーが1以上のとき。
						DeleteGO(m_spriteRenderStart);						//Startの画像を消す。
						m_spriteRenderStart = nullptr;						//インスタンスを破棄。
						m_gameStartFlag = true;								//ゲーむの更新処理を開始。
					}
				}
			}
		}
	}
}