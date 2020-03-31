#pragma once

class StageSelectDetailed : public GameObject
{
public:
	StageSelectDetailed();
	~StageSelectDetailed();

	bool Start();
	void Update();

	/// <summary>
	/// ステージの詳細画像を生成する処理。
	/// </summary>
	/// <param name="stageNum">ステージ画像</param>
	void NewDetailedImage(int stageNum);

	/// <summary>
	/// 詳細画像を消す処理。
	/// </summary>
	void DeleteDetailedImage();

	/// <summary>
	/// 座標を指定する、
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// スケールを指定する。
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

private:

	bool m_newImage = false;						//画像が生成されているか。

	CVector3 m_position = CVector3::Zero();			//座標。
	CVector3 m_scale = CVector3::One();				//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SpriteRender* m_spriteRender = nullptr;			//画像生成用。

};

