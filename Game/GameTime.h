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
	/// １フレームの経過時間を取得する。
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

	/// <summary>
	/// フレームレートを取得する。
	/// </summary>
	/// <returns>フレームレート</returns>
	const float GetFrameRate() const
	{
		return m_fps;
	}

private:

	std::list<float> m_frameDeltaTimeQue;

	const float m_fps = 60.f;					//フレームレート。

	float m_frameDeltaTime = 1.0f / m_fps;		//1フレームの経過時間。60fps.

	/// <summary>
	/// クラスのインスタンスを返す。
	/// </summary>
	/// <returns>インスタンスを返す関数</returns>
	static GameTime& GameTimer()
	{
		return GameTime::GetInstance();
	}

};
