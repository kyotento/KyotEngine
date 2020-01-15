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
	/// fps���Œ肷��B
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


private:

	std::list<float> m_frameDeltaTimeQue;

	float m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB60fps.

	/// <summary>
	/// �N���X�̃C���X�^���X��Ԃ��B
	/// </summary>
	/// <returns>�C���X�^���X��Ԃ��֐�</returns>
	static GameTime& GameTimer()
	{
		return GameTime::GetInstance();
	}

};
