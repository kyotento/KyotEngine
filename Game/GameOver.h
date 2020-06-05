/// <summary>
/// �Q�[���I�[�o�[�N���X�B
/// </summary>
#pragma once
#include "GameOver.h"
#include "Result.h"

class GameOver : public GameObject
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

	/// <summary>
	/// �Q�[���ł����������ꂽ���̂������B
	/// </summary>
	void DeleteField();

	/// <summary>
	/// �X�P�[���̍X�V�����B
	/// </summary>
	void ScaleUpdate();

private:

	float m_scalefloat = 0.f;						//�X�P�[���X�V�p�B
	float m_timer = 0.f;							//�摜�������^�C�}�[�B

	CVector3 m_position = CVector3::Zero();			//���W�B
	CVector3 m_scale = CVector3::Zero();			//�X�P�[���B

	SpriteRender* m_spriteRender = nullptr;			//�摜�����N���X�B

	Result* m_result = nullptr;						//���U���g�B

};

