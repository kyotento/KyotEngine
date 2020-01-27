#pragma once
#include "GameObject.h"

class Fade : public GameObject
{
public:
	Fade();
	~Fade();

	bool Start();
	void Update();

	/// <summary>
	/// �摜�𐶐�����֐��B
	/// </summary>
	/// <param name="scale">�摜�̊g�嗦</param>
	void ImageGeneration(float scale);

	/// <summary>
	/// �t�F�[�h�C������B
	/// </summary>
	/// <remarks>
	/// ��{�I�ɂ�FadeOut���ꂽ��ɌĂԁB
	/// </remarks>
	void FadeIn();

	/// <summary>
	/// �t�F�[�h�A�E�g����B
	/// </summary>
	void FadeOut();

	/// <summary>
	/// �t�F�[�h�A�E�g��t�F�[�h�C������B
	/// </summary>
	/// <param name="FadeInterval">�t�F�[�h�A�E�g����t�F�[�h�C���܂ł̊Ԋu</param>
	void PlayFade(/*float FadeInterval*/);

private:

	enum  FadeState
	{
		enFadeIn,			//�t�F�[�h�C���B
		enFadeOut,			//�t�F�[�h�A�E�g�B
		enFadeNum			//�t�F�[�h�̐��B
	};

	bool m_newPunching = false;								//�g��k������摜����������Ă��邩�B
	bool m_newCover = false;								//�J�o�[�摜����������Ă��邩�B

	CVector3 m_position = CVector3::Zero();					//�摜�̍��W�B
	CVector3 m_scalePunching = CVector3::One();				//�g��k������������摜�̊g�嗦�B
	CVector3 m_scaleCover = CVector3::One();				//�J�o�[�摜�̊g�嗦�B

	CQuaternion m_rotation = CQuaternion::Identity();		//�摜�̉�]�B

	FadeState m_fadeState = enFadeNum;						//�t�F�[�h�̏�ԁB

	SpriteRender* m_spriteRenderPunching = nullptr;			//�g��k������������摜�B
	SpriteRender* m_spriteRenderCover = nullptr;			//Punching�̊g�嗦���P�ȉ��ɂȂ�ꍇ�ɕ`�悷��B

};

