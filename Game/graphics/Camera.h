#pragma once
class Camera
{
public:

	enum EnUpdateProjMatrixFunc {
		enUpdateProjMatrixFunc_Perspective,		//!<�����ˉe�s��
		enUpdateProjMatrixFunc_Ortho,			//!<���s���e
	};

	/*!
	 * @brief	�J�����s��A�v���W�F�N�V�����s��̍X�V�B
	 *@details
	 * ���ݐݒ肳��Ă���A�����_�A���_�A��p�Ȃǂ̏������Ƃ�
	 * �J�����s��ƃv���W�F�N�V�����s����X�V���܂��B
	 * ���̊֐����Ă΂Ȃ��ƁA�J�����͓����Ȃ��̂Œ��ӂ��K�v�ł��B
	 */
	void Update();
	/*!
	 * @brief	�J�����s����擾�B
	 */
	CMatrix GetViewMatrix()
	{
		return m_viewMatrix;
	}
	/*!
	 * @brief	�v���W�F�N�V�����s����擾�B
	 */
	CMatrix GetProjectionMatrix() 
	{
		return m_projMatrix;
	}
	/*!
	 * @brief	���_���擾�B
	 */
	CVector3 GetPosition()
	{
		return m_position;
	}
	/*!
	 * @brief	�����_���擾�B
	 */
	CVector3 GetTarget()
	{
		return m_target;
	}
	/*!
	 * @brief	�J�����̏�������擾�B
	 */
	CVector3 GetUp()
	{
		return m_up;
	}
	/*!
	 * @brief	���_��ݒ�B
	 */
	void SetPosition( CVector3 pos )
	{
		m_position = pos;
	}
	/*!
	 * @brief	�����_��ݒ�B
	 */
	void SetTarget( CVector3 target )
	{
		m_target = target;
	}
	/*!
	 * @brief	�J�����̏������ݒ�B
	 */
	void SetUp( CVector3 up )
	{
		m_up = up;
	}
	/*!
	 * @brief	�����ʂ�ݒ�B
	 */
	void SetFar( float f )
	{
		m_far = f;
	}
	/*!
	 * @brief	�ߕ��ʂ�ݒ�B
	 */
	void SetNear( float n )
	{
		m_near = n;
	}
	/*!
	 * @brief	��p��ݒ�B
	 */
	void SetViewAngle( float angle )
	{
		m_viewAngle = angle;
	}

	/// <summary>
	/// ���s���e���˖@���e�ɂ��邩�����߂�B
	/// </summary>
	/// <param name="a">a = 0 = �˖@���e�B a = true = ���s���e</param>
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
	/// �J�����̉�]���擾����B
	/// </summary>
	/// <returns>�J�����̉�]</returns>
	CQuaternion GetCameraQuauternion()
	{
		CVector3 rot = m_target - m_position;		//�����_���王�_�����Z�B
		rot.Normalize();							//���K�����A�������v�Z�B
		CQuaternion camerarot;						//�J�����̉�]�B
		camerarot.SetRotation(m_front, rot);		//�J�����̉�]���v�Z�B
		return camerarot;							//�J�����̉�]�B
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//�r���[�s��B���͋t�B
	CMatrix m_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B
	CVector3 m_target = { 0.f,0.f,10.f };			//�����_�B
	CVector3 m_position = CVector3::Zero();			//���_�B
	CVector3 m_up = CVector3::Up();					//������B
	CVector3 m_front = CVector3::Front();			//�O�������B
	float m_viewAngle = CMath::DegToRad(60.0f);		//��p�B
	float m_far = 10000.0f;							//�������ʂ܂ł̋����B
	float m_near = 1.0f;							//�ߕ��ʂ܂ł̋����B

	EnUpdateProjMatrixFunc m_UpdateCameraMatrix = enUpdateProjMatrixFunc_Perspective;			//���s���f���˖@���e���B
};

extern Camera g_camera3D;		//!<3D�J�����B
extern Camera camera2d;			//2D�J�����B
