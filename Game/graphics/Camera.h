#pragma once
class Camera
{
public:

	enum EnUpdateProjMatrixFunc {
		enUpdateProjMatrixFunc_Perspective,		//!<透視射影行列
		enUpdateProjMatrixFunc_Ortho,			//!<平行投影
	};

	/*!
	 * @brief	カメラ行列、プロジェクション行列の更新。
	 *@details
	 * 現在設定されている、注視点、視点、画角などの情報をもとに
	 * カメラ行列とプロジェクション行列を更新します。
	 * この関数を呼ばないと、カメラは動かないので注意が必要です。
	 */
	void Update();
	/*!
	 * @brief	カメラ行列を取得。
	 */
	CMatrix GetViewMatrix()
	{
		return m_viewMatrix;
	}
	/*!
	 * @brief	プロジェクション行列を取得。
	 */
	CMatrix GetProjectionMatrix() 
	{
		return m_projMatrix;
	}
	/*!
	 * @brief	視点を取得。
	 */
	CVector3 GetPosition()
	{
		return m_position;
	}
	/*!
	 * @brief	注視点を取得。
	 */
	CVector3 GetTarget()
	{
		return m_target;
	}
	/*!
	 * @brief	カメラの上方向を取得。
	 */
	CVector3 GetUp()
	{
		return m_up;
	}
	/*!
	 * @brief	視点を設定。
	 */
	void SetPosition( CVector3 pos )
	{
		m_position = pos;
	}
	/*!
	 * @brief	注視点を設定。
	 */
	void SetTarget( CVector3 target )
	{
		m_target = target;
	}
	/*!
	 * @brief	カメラの上方向を設定。
	 */
	void SetUp( CVector3 up )
	{
		m_up = up;
	}
	/*!
	 * @brief	遠平面を設定。
	 */
	void SetFar( float f )
	{
		m_far = f;
	}
	/*!
	 * @brief	近平面を設定。
	 */
	void SetNear( float n )
	{
		m_near = n;
	}
	/*!
	 * @brief	画角を設定。
	 */
	void SetViewAngle( float angle )
	{
		m_viewAngle = angle;
	}

	/// <summary>
	/// 平行投影か射法投影にするかを決める。
	/// </summary>
	/// <param name="a">a = 0 = 射法投影。 a = true = 平行投影</param>
	void SetUpdateCameraMatrix(bool a)
	{
		if (a) {
			m_UpdateCameraMatrix = enUpdateProjMatrixFunc_Ortho;
		}

		if (a == false)
		{
			m_UpdateCameraMatrix = enUpdateProjMatrixFunc_Perspective;
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool GetSetUpdateCameraMatrix()
	{
		return m_UpdateCameraMatrix;
	}

	/// <summary>
	/// カメラの回転を取得する。
	/// </summary>
	/// <returns>カメラの回転</returns>
	CQuaternion GetCameraQuauternion()
	{
		CVector3 rot = m_target - m_position;		//注視点から視点を減算。
		rot.Normalize();							//正規化し、向きを計算。
		CQuaternion camerarot;						//カメラの回転。
		camerarot.SetRotation(m_front, rot);		//カメラの回転を計算。
		return camerarot;							//カメラの回転。
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//ビュー行列。実は逆。
	CMatrix m_projMatrix = CMatrix::Identity();		//プロジェクション行列。
	CVector3 m_target = { 0.f,0.f,10.f };			//注視点。
	CVector3 m_position = CVector3::Zero();			//視点。
	CVector3 m_up = CVector3::Up();					//上方向。
	CVector3 m_front = CVector3::Front();			//前方方向。
	float m_viewAngle = CMath::DegToRad(60.0f);		//画角。
	float m_far = 10000.0f;							//遠い平面までの距離。
	float m_near = 1.0f;							//近平面までの距離。

	EnUpdateProjMatrixFunc m_UpdateCameraMatrix = enUpdateProjMatrixFunc_Perspective;			//平行東映か射法投影か。
};

extern Camera g_camera3D;		//!<3Dカメラ。
extern Camera camera2d;			//2Dカメラ。
