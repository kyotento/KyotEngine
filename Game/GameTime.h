#pragma once
class GameTime
{
public:
	GameTime();
	~GameTime();

	/// <summary>
	/// GameTime�N���X�̃C���X�^���X���擾����B
	/// </summary>
	/// <returns>GameTime�̃C���X�^���X</returns>
	static GameTime& GetInstance()
	{
		static GameTime timer;
		return timer;
	}

	/// <summary>
	/// �P�t���[���̌o�ߎ��Ԃ��擾����B
	/// </summary>
	/// <returns>1.0f/60.f</returns>
	const float GetFrameDeltaTime() const
	{
		return m_frameDeltaTime;
	}

	/// <summary>
	/// 1/60�����o���B
	/// </summary>
	/// <param name="deltaTime"></param>
	void PushFrameDeltaTime(float deltaTime);

	/// <summary>
	/// �t���[�����[�g���擾����B
	/// </summary>
	/// <returns>�t���[�����[�g</returns>
	const float GetFrameRate() const
	{
		return m_fps;
	}

private:

	std::list<float> m_frameDeltaTimeQue;

	const float m_fps = 60.f;					//�t���[�����[�g�B

	float m_frameDeltaTime = 1.0f / m_fps;		//1�t���[���̌o�ߎ��ԁB60fps.

	/// <summary>
	/// �N���X�̃C���X�^���X��Ԃ��B
	/// </summary>
	/// <returns>�C���X�^���X��Ԃ��֐�</returns>
	static GameTime& GameTimer()
	{
		return GameTime::GetInstance();
	}

};
