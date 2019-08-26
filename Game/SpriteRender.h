#pragma once
class SpriteRender
{
public:
	SpriteRender();
	~SpriteRender();

	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="textureFilePath">�e�N�X�`���t�@�C���p�X�B</param>
	/// <param name="w">���B</param>
	/// <param name="h">�����B</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	
	/// <summary>
	/// ���W�ݒ�B
	/// </summary>
	/// <param name="pos">�RD�x�N�g���B</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns>���W�B</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}

private:

	float m_w = 0;					//���B
	float m_h = 0;					//�����B

	CVector3 m_position;			//���W�B

	Sprite m_sprite;//Sprite�B
};

