#pragma once
#include "Sprite.h"
#include "graphics/Camera.h"
class SpriteRender : public GameObject
{
public:
	SpriteRender();
	~SpriteRender();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="textureFilePath">テクスチャファイルパス。</param>
	/// <param name="w">幅。</param>
	/// <param name="h">たかさ。</param>
	/// <param name="isDraw3D">3D空間上に描画するか。</param>
	void Init(const wchar_t* textureFilePath, float w, float h, bool isDraw3D = false);
	
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

	/// <summary>
	/// 回転設定。
	/// </summary>
	/// <param name="rot">回転。</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// 回転情報を取得。
	/// </summary>
	/// <returns>回転。</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	/// <summary>
	/// Pivotの設定。
	/// </summary>
	/// <param name="pivot">Pivot。</param>
	void SetPivot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}

	/// <summary>
	/// 更新処理。
	/// </summary>
	void Render()override;

private:
	Camera::EnUpdateProjMatrixFunc m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Ortho;

	bool m_Draw3D = false;		//3D空間上に描画するか。

	float m_w = 0;								//幅。
	float m_h = 0;								//高さ。

	CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//Pivot。
	CVector3 m_position;						//座標。
	CVector3 m_scale = { 1.f,1.f,1.f };			//スケール。
	CQuaternion m_rotation;						//回転。

	Sprite m_sprite;					//Sprite。
	//Camera m_camera;
};

