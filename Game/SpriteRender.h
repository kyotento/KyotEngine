#pragma once
class SpriteRender
{
public:
	SpriteRender();
	~SpriteRender();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="textureFilePath">テクスチャファイルパス。</param>
	/// <param name="w">幅。</param>
	/// <param name="h">高さ。</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	
	/// <summary>
	/// 座標設定。
	/// </summary>
	/// <param name="pos">３Dベクトル。</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 座標を取得。
	/// </summary>
	/// <returns>座標。</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}

private:

	float m_w = 0;					//幅。
	float m_h = 0;					//高さ。

	CVector3 m_position;			//座標。

	Sprite m_sprite;//Sprite。
};

