#include "stdafx.h"
#include "Result.h"
#include "Stage_1.h"
#include "PlayerGenerations.h"
#include "Title.h"

namespace {
	int score = 0;							//取得したスコアを格納する。
	int getStar = 0;						//獲得した星の数。
	float starScale = 2.f;					//星のスケールを変更する時に使う。

	float m_sheet_w = 360.f;				//シートの画像の幅。
	float m_sheet_h = 540.f;				//シートの画像の高さ。
	float m_star_w = 80.f;					//星の画像の幅。
	float m_star_h = 80.f;					//星の画像の高さ。
}

//todo マジックナンバーはすべて仮。

Result::Result()
{
}


Result::~Result()
{
	starScale = 2.f;
	if (m_spriteRenderSheet != nullptr) {				//シートが生成されているとき。
		DeleteGO(m_spriteRenderSheet);					//シートを消す。
	}
	for (int i = 0; i < m_starNum; i++) {				//星の配列分ループする。
		if (m_spriteRenderStar[i] != nullptr) {			//星が生成されていたら。
			DeleteGO(m_spriteRenderStar[i]);			//星を消す。
			m_spriteRenderStar[i] = nullptr;			//インスタンスを破棄。
		}
	}
}


bool Result::Start()
{
	m_score = FindGO<Score>("score");				//スコアのインスタンスを取得。

	m_spriteRenderSheet = NewGO<SpriteRender>(0, "sprite");										//スプライトクラスを生成。
	m_spriteRenderSheet->Init(L"Assets/sprite/result_sheet.dds", m_sheet_w, m_sheet_h);			//シートの初期化。
	m_spriteRenderSheet->SetPosition(m_positionSheet);											//座標を初期化。
	m_spriteRenderSheet->SetScale(m_scaleSheet);												//スケールを初期化。

	m_positionStar[0] = m_positionSheet;			//一つ目の星の座標にシートの座標を代入。
	m_positionStar[0].x -= 80.f;					//左に移動する。
	m_positionStar[0].y -= 90.f;					//下に移動する。

	for (int i = 0; i < m_starNum; i++) {			//生成する星の数分ループする。
		m_spriteRenderStar[i] = NewGO<SpriteRender>(1, "sprite");								//スプライトクラスを生成。
		m_spriteRenderStar[i]->Init(L"Assets/sprite/black_star.dds", m_star_w, m_star_h);		//星の初期化(はじめは黒い星)。
		m_spriteRenderStar[i]->SetPosition(m_positionStar[i]);									//座標を初期化。
		m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);										//スケールを初期化。

		if (i <= m_starNum - 1) {					//次の配列が存在したら。
			m_positionStar[i + 1] = m_positionStar[i];											//次の星の座標に前の星の座標を代入。
			m_positionStar[i + 1].x += 80.f;													//右に移動する。
		}
	}

	score = m_score->GetScore();				//スコアを取得。

	//BGM。
	Sound* sound = NewGO<Sound>(0, "sound");				//サウンドクラス。
	sound->Init(L"Assets/sound/bgm/result.wav", false);		//初期化。
	sound->Play();											//再生。

	return true;
}

//スコアに応じて星を変更する。
void Result::ChangeStar()
{
	if (score < m_score->GetStarOne()) {			//スコアが星１のボーダーよりも少ないとき。
		getStar = 0;								//星の数を０に。
	}

	if (score >= m_score->GetStarOne() && score < m_score->GetStarTwo()) {		//星１のとき。
		getStar = 1;								//星の数を１に。
	}

	if (score >= m_score->GetStarTwo() && score < m_score->GetStarThree()) {	//星２のとき。
		getStar = 2;								//星の数を２に。
	}

	if (score >= m_score->GetStarThree()) {			//星３のとき。
		getStar = 3;								//星の数を３に。
	}

	for (int i = 0; i < getStar; i++) {				//獲得した星の数分ループする。
		if (m_changeStarFlag[i] == false) {			//星画像を変更していなかったとき。
			m_spriteRenderStar[i]->Init(L"Assets/sprite/star.dds", m_star_w, m_star_h);			//星のモデル変更。
			m_scaleStar[i] = { starScale,starScale,starScale };
			m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);
			m_changeStarFlag[i] = true;				//星の画像を変更したのでフラグを返す。
		}
	}

	//todo 星変更のときにはじめ拡大している状態で描画しておき、縮小して元のサイズに戻すアニメーションを実装する。

	for (int i = 0; i < getStar; i++) {				//獲得した星の数分ループする。　
		if (starScale > 1.f) {											//スケールが１より大きいとき。
			starScale -= 0.03f;											//スケールを縮小する。
			m_scaleStar[i] = { starScale,starScale,starScale };			//スケールに代入。
			m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);			//スケールを更新。	
		}
	}
}

void Result::Update()
{
	if (m_deleteOKFlag){			//消すことができる状態になった時。
		if (g_pad[0].IsTrigger(enButtonB)) {			//Bボタンを押したとき。

			Sound* sound = NewGO<Sound>(0, "sound");								//サウンド。
			sound->Init(L"Assets/sound/soundEffect/decision3.wav", false);			//初期化。
			sound->Play();															//再生。

			Title* title = NewGO<Title>(0, "title");

			Stage_1* m_stage_1 = nullptr;				//ステージ１．
			m_stage_1 = FindGO<Stage_1>("stage_1");		//ステージ１のインスタンスを取得する。
			DeleteGO(m_stage_1);						//ステージ１を消す。	

			PlayerGenerations* playerGenerations = nullptr;							//プレイヤー生成クラス。
			playerGenerations = FindGO<PlayerGenerations>("playergenrations");		//プレイヤー生成クラスのインスタンスを取得。
			DeleteGO(playerGenerations);											//プレイヤー生成クラスを消す。

			DeleteGOs("dishdirty");			//汚れたお皿を消す。

			DeleteGO(m_score);				//スコアクラスを消す。
			DeleteGO(this);					//このクラスを消す。
		}
	}

}

//次の星までのスコア。
int Result::NexStarNum()
{
	if (score < m_score->GetStarOne()) {			//スコアが星１のボーダーよりも少ないとき。
		return m_score->GetStarOne() - score;		//星１のボーダーからスコアを減算したものを返す。
	}

	if (score >= m_score->GetStarOne() && score < m_score->GetStarTwo()) {			//スコアが星１のボーダーよりも少ないとき。
		return m_score->GetStarTwo() - score;									//星２のボーダーからスコアを減算したものを返す。
	}

	if (score >= m_score->GetStarTwo() && score < m_score->GetStarThree()) {	//星２のとき。
		return m_score->GetStarThree() - score;									//星３のボーダーからスコアを減算したものを返す。
	}

	if (score >= m_score->GetStarThree()) {			//星３のとき。
		return 0;									//0を返す。
	}
}

void Result::AfterFontRender()
{
	m_timer += gametime().GetFrameDeltaTime();			//タイマーを加算。

	//ステージ。
	m_font.Begin();			//描画開始。
	wchar_t text[64];														//テキストに使う配列。
	swprintf_s(text, L"1");													//テキストを設定。
	m_positionFont.x = m_positionSheet.x + 50.f;							//X座標を指定。						
	m_positionFont.y = m_positionSheet.y + 148.f;							//Y座標を指定。
	m_font.Draw(text, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
	m_font.End();			//描画終了。

	if (m_timer >= 0.5f) {
		//チップ加算前のスコア。
		m_font.Begin();			//描画開始。
		wchar_t text2[64];														//テキストに使う配列。
		swprintf_s(text2, L"%d", m_score->GetProfit());							//テキストを指定。
		m_positionFont.y -= 50.f;												//Y座標を指定。
		m_font.Draw(text2, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
		m_font.End();			//描画終了。
	}

	if (m_timer >= 1.f) {
		//チップ。
		m_font.Begin();			//描画開始。
		wchar_t text3[64];														//テキストに使う配列。
		swprintf_s(text3, L"%d", m_score->GetChip());							//テキストを指定。
		m_positionFont.y -= 25.f;												//Y座標を指定。
		m_font.Draw(text3, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
		m_font.End();			//描画終了。
	}

	if (m_timer >= 1.5f) {
		//ペナルティ。
		m_font.Begin();			//描画開始。
		wchar_t text4[64];														//テキストに使う配列。
		swprintf_s(text4, L"%d", m_score->GetPenalty());						//テキストを指定。
		m_positionFont.y -= 25.f;												//Y座標を指定。
		m_font.Draw(text4, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
		m_font.End();			//描画終了。
	}

	if (m_timer >= 2.f) {
		//累計スコア
		m_font.Begin();			//描画開始。
		wchar_t text5[64];														//テキストに使う配列。
		swprintf_s(text5, L"%d", m_score->GetScore());							//テキストを指定。
		m_positionFont.x -= 70.f;												//X座標を指定。
		m_positionFont.y -= 32.f;												//Y座標を指定。
		float scaleScore = 1.2f;												//フォントのスケールを指定。
		m_font.Draw(text5, m_positionFont, m_colorFont, 0.0f, scaleScore);		//更新処理。
		m_font.End();			//描画終了。
	}
	if (m_timer >= 2.5f) {
		ChangeStar();			//スコアに応じて星を変更する。
	}

	if (m_timer >= 3.f) {
		//次の星までのスコア。
		m_font.Begin();			//描画開始。
		wchar_t text6[64];														//テキストに使う配列。
		swprintf_s(text6, L"%d", NexStarNum());									//テキストを指定。
		m_positionFont.y -= 153.f;												//Y座標を指定。
		m_font.Draw(text6, m_positionFont, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
		m_font.End();			//描画終了。
	}

	//todo 間に合わせ程度の仮。
	if (m_timer >= 4.5f) {
		//タイトルへ。
		m_font.Begin();			//描画開始。
		wchar_t text7[64];														//テキストに使う配列。
		swprintf_s(text7, L"Bボタンでタイトルへ");				//テキストを指定。
		m_font.Draw(text7, { 0.f,-300.f }, m_colorFont, 0.0f, m_scaleFont);		//更新処理。
		m_font.End();			//描画終了。
		m_deleteOKFlag = true;				//ゲームを終了することができるように。
	}
}