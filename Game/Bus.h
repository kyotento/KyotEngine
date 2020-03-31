#pragma once
#include "GameObject.h"
#include "GameCamera.h"
#include "Flag.h"
#include "StageSelectDetailed.h"

#include "character/CharacterController.h"

class Bus : public GameObject
{
public:
	Bus();
	~Bus();

	bool Start();
	void Update();

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move();

	/// <summary>
	///	回転処理。
	/// </summary>
	void Rotation();

	/// <summary>
	/// カメラを追従させる処理。
	/// </summary>
	void FollowCamera();

	/// <summary>
	/// 旗を検索する処理。
	/// </summary>
	void FlagSearch();

	/// <summary>
	/// 座標を指定する。
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

	/// <summary>
	/// 回転を指定する。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	static const int FLAG_NUM = 3;							//旗の数。

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One()*5.f;					//スケール。
	CVector3 m_stickPower = CVector3::Zero();				//左スティックの傾き具合を保持するためのもの。
	CVector3 m_move = CVector3::Zero();						//キャラコンの移動速度を計算したもの。(方向持ち)。
	CVector3 m_resetPosition = CVector3::Zero();			//バスのリセット座標。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SkinModelRender* m_skinModelRender = nullptr;			//スキンモデル。
	GameCamera* m_gameCamera = nullptr;						//カメラ。

	Flag* m_flag[FLAG_NUM] = { nullptr };					//旗。
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//ステージの詳細画像。

	CharacterController m_characon;			//キャラコン。

};

