#pragma once

class Sound : public GameObject 
{
public:
	Sound();
	~Sound();
	bool Start() override;
	void Update() override;;
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="">ファイルパス</param>
	/// <param name="">ループするか</param>
	void Init(const wchar_t*, bool = false);

	/// <summary>
	/// 再生。
	/// </summary>
	void Play();
	bool isPlaying();

	/// <summary>
	/// 停止。
	/// </summary>
	/// <remarks>
	/// インスタンスが破棄される。
	/// </remarks>
	void Stop();
	/// <summary>
	/// ボリュームを設定する。
	/// </summary>
	/// <param name="vol">ボリューム</param>
	void SetVolume(float vol);
	void SetPitch(float p) {
		pitch = p;
	}
	void SetPan(float pa) {
		pan = pa;
	}
private:
	bool m_isInited = false;
	bool m_roopFlag = false;
	float volume = 1.f * 1.f/8.f;
	float pitch = 0.f;
	float pan = 0.f;
	std::unique_ptr<DirectX::SoundEffect> soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> effect;
};

