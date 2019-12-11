#pragma once

class Gauge : public GameObject
{
public:
	Gauge();
	~Gauge();

	bool Start();
	void Update();

	/// <summary>
	/// �Q�[�W���g�傷��B
	/// </summary>
	/// <param name="a">�g�嗦</param>
	void Expansion(float a);

	/// <summary>
	/// �Q�[�W��X���g�嗦�B
	/// </summary>
	/// <returns>�g�嗦X��</returns>
	float GetScale()
	{
		return m_x;
	}

	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	bool GetGaugeMax()
	{
		return m_gaugeMax;
	}

	void GaugeHalf()
	{
		m_x = m_x / 2;
	}

private:

	bool m_gaugeMax = false;
	float m_x = 0.0f;									//�Q�[�W��X���g�嗦�B

	CVector2 m_pivot = { 0.f,0.5f };					//��_�B

	CVector3 m_position = {0,0,0}/* CVector3::Zero()*/;				//�Q�[�W�Ɗ�Ղ̍��W�B
	CVector3 m_scaleGauge = CVector3::One();			//�Q�[�W�̊g�嗦�B

	//SpriteRender* m_spriteRender = nullptr;				//�Q�[�W��՗p�X�v���C�g�B
	//SpriteRender* m_spriteRenderGauge = nullptr;		//�Q�[�W�p�X�v���C�g�B

	SkinModelRender* m_skinModelRender = nullptr;				//�Q�[�W��՗p�X�L�����f���B
	SkinModelRender* m_skinModelRenderGauge = nullptr;			//�Q�[�W�p�X�L�����f���B

};

