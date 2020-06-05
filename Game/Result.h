/// <summary>
/// リザルト。
/// </summary>

#pragma once
#include "GameObject.h"
#include "Score.h"
class Result : public GameObject
{
public:
	Result();
	~Result();

	bool Start();
	void Update();

	/// <summary>
	/// フォントを生成する。
	/// </summary>
	void AfterFontRender();

	/// <summary>
	/// スコアに応じてほしを変更する。
	/// </summary>
	void ChangeStar();

	/// <summary>
	/// 次の星までのスコアを返す。
	/// </summary>
	/// <returns>次の星までのスコア</returns>
	int NexStarNum();

private:

	static const int m_starNum = 3;			//生成される星の数。

	float m_timer = 0.f;					//タイマー。

	bool m_changeStarFlag[m_starNum] = { false };			//星を変更したかどうか。
	bool m_deleteOKFlag = false;							//ゲームを終了することができる状態か。

	CVector3 m_positionSheet = CVector3::Zero();															//シートの座標。
	CVector3 m_positionStar[m_starNum] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//星の座標。
	CVector3 m_scaleSheet = CVector3::One();																//シートのスケール。
	CVector3 m_scaleStar[m_starNum] = { CVector3::One(),CVector3::One(),CVector3::One() };					//星のスケール。

	CVector2 m_positionFont = CVector2::Zero();				//フォントの座標。
	float m_scaleFont = 0.7f;								//フォントのスケール。
		
	CVector4 m_colorFont = CVector4::Black;					//フォントの色。

	SpriteRender* m_spriteRenderSheet = nullptr;					//シートを生成する画像生成クラス。
	SpriteRender* m_spriteRenderStar[m_starNum] = { nullptr };		//星を生成する画像生成クラス。		

	Score* m_score = nullptr;					//スコア。
	
	Font m_font;		//フォント。

};

