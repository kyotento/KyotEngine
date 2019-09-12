#pragma once
#include "character/CharacterController.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	/// <summary>
	/// プレイヤー移動クラス。
	/// </summary>
	void Movement();

	/// <summary>
	/// プレイヤー回転クラス。
	/// </summary>
	void Rotation();

private:

	float m_moveSpeed = 10.f;								//移動速度。

	CVector3 m_position = CVector3::Zero();					//プレイヤーの座標。
	CVector3 m_characonPos = CVector3::Zero();				//キャラコンの座標。
	CVector3 m_scale = CVector3::One();						//拡大率。
	CVector3 m_move = CVector3::Zero();						//キャラコンとかプレイヤーの移動速度を計算したもの。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	CharacterController m_characon;							//キャラコン。

	SkinModelRender* m_skinModelRender = nullptr;			//スキンモデル。

};

