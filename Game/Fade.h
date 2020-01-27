#pragma once
#include "GameObject.h"

class Fade : public GameObject
{
public:
	Fade();
	~Fade();

	bool Start();
	void Update();

	/// <summary>
	/// 画像を生成する関数。
	/// </summary>
	/// <param name="scale">画像の拡大率</param>
	void ImageGeneration(float scale);

	/// <summary>
	/// フェードインする。
	/// </summary>
	/// <remarks>
	/// 基本的にはFadeOutされた後に呼ぶ。
	/// </remarks>
	void FadeIn();

	/// <summary>
	/// フェードアウトする。
	/// </summary>
	void FadeOut();

	/// <summary>
	/// フェードアウト後フェードインする。
	/// </summary>
	/// <param name="FadeInterval">フェードアウトからフェードインまでの間隔</param>
	void PlayFade(/*float FadeInterval*/);

private:

	enum  FadeState
	{
		enFadeIn,			//フェードイン。
		enFadeOut,			//フェードアウト。
		enFadeNum			//フェードの数。
	};

	bool m_newPunching = false;								//拡大縮小する画像が生成されているか。
	bool m_newCover = false;								//カバー画像が生成されているか。

	CVector3 m_position = CVector3::Zero();					//画像の座標。
	CVector3 m_scalePunching = CVector3::One();				//拡大縮小処理をする画像の拡大率。
	CVector3 m_scaleCover = CVector3::One();				//カバー画像の拡大率。

	CQuaternion m_rotation = CQuaternion::Identity();		//画像の回転。

	FadeState m_fadeState = enFadeNum;						//フェードの状態。

	SpriteRender* m_spriteRenderPunching = nullptr;			//拡大縮小処理をする画像。
	SpriteRender* m_spriteRenderCover = nullptr;			//Punchingの拡大率が１以下になる場合に描画する。

};

