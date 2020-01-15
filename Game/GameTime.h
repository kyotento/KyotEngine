#pragma once
class GameTime
{
public:
	GameTime();
	~GameTime();

	/// <summary>
	/// GameTimeクラスのインスタンスを取得する。
	/// </summary>
	/// <returns>GameTimeのインスタンス</returns>
	static GameTime& GetInstance()
	{
		static GameTime timer;
		return timer;
	}

	/// <summary>
	/// fpsを固定する。
	/// </summary>
	/// <returns>1.0f/60.f</returns>
	const float GetFrameDeltaTime() const
	{
		return m_frameDeltaTime;
	}

	/// <summary>
	/// 1/60を作り出す。
	/// </summary>
	/// <param name="deltaTime"></param>
	void PushFrameDeltaTime(float deltaTime);


private:

	std::list<float> m_frameDeltaTimeQue;

	float m_frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。60fps.

	/// <summary>
	/// クラスのインスタンスを返す。
	/// </summary>
	/// <returns>インスタンスを返す関数</returns>
	static GameTime& GameTimer()
	{
		return GameTime::GetInstance();
	}

};
