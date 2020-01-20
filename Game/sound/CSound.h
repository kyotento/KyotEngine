#pragma once

class Sound : public GameObject 
{
public:
	Sound();
	~Sound();
	bool Start() override;
	void Update() override;;
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="">�t�@�C���p�X</param>
	/// <param name="">���[�v���邩</param>
	void Init(const wchar_t*, bool = false);

	/// <summary>
	/// �Đ��B
	/// </summary>
	void Play();
	bool isPlaying();

	/// <summary>
	/// ��~�B
	/// </summary>
	/// <remarks>
	/// �C���X�^���X���j�������B
	/// </remarks>
	void Stop();
	/// <summary>
	/// �{�����[����ݒ肷��B
	/// </summary>
	/// <param name="vol">�{�����[��</param>
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

