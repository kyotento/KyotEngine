#pragma once

class StageSelectDetailed : public GameObject
{
public:
	StageSelectDetailed();
	~StageSelectDetailed();

	bool Start();
	void Update();

	/// <summary>
	/// �X�e�[�W�̏ڍ׉摜�𐶐����鏈���B
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�摜</param>
	void NewDetailedImage(int stageNum);

	/// <summary>
	/// �ڍ׉摜�����������B
	/// </summary>
	void DeleteDetailedImage();

	/// <summary>
	/// ���W���w�肷��A
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�P�[�����w�肷��B
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

private:

	bool m_newImage = false;						//�摜����������Ă��邩�B

	CVector3 m_position = CVector3::Zero();			//���W�B
	CVector3 m_scale = CVector3::One();				//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SpriteRender* m_spriteRender = nullptr;			//�摜�����p�B

};

