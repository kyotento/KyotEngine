/// <summary>
/// ���U���g�B
/// </summary>

#pragma once
#include "GameObject.h"
#include "Score.h"
class Result : public GameObject
{
public:
	Result();
	~Result();

	bool Start();
	void Update();

	/// <summary>
	/// �t�H���g�𐶐�����B
	/// </summary>
	void AfterFontRender();

	/// <summary>
	/// �X�R�A�ɉ����Ăق���ύX����B
	/// </summary>
	void ChangeStar();

	/// <summary>
	/// ���̐��܂ł̃X�R�A��Ԃ��B
	/// </summary>
	/// <returns>���̐��܂ł̃X�R�A</returns>
	int NexStarNum();

private:

	static const int m_starNum = 3;			//��������鐯�̐��B

	float m_timer = 0.f;					//�^�C�}�[�B

	bool m_changeStarFlag[m_starNum] = { false };			//����ύX�������ǂ����B
	bool m_deleteOKFlag = false;							//�Q�[�����I�����邱�Ƃ��ł����Ԃ��B

	CVector3 m_positionSheet = CVector3::Zero();															//�V�[�g�̍��W�B
	CVector3 m_positionStar[m_starNum] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//���̍��W�B
	CVector3 m_scaleSheet = CVector3::One();																//�V�[�g�̃X�P�[���B
	CVector3 m_scaleStar[m_starNum] = { CVector3::One(),CVector3::One(),CVector3::One() };					//���̃X�P�[���B

	CVector2 m_positionFont = CVector2::Zero();				//�t�H���g�̍��W�B
	float m_scaleFont = 0.7f;								//�t�H���g�̃X�P�[���B
		
	CVector4 m_colorFont = CVector4::Black;					//�t�H���g�̐F�B

	SpriteRender* m_spriteRenderSheet = nullptr;					//�V�[�g�𐶐�����摜�����N���X�B
	SpriteRender* m_spriteRenderStar[m_starNum] = { nullptr };		//���𐶐�����摜�����N���X�B		

	Score* m_score = nullptr;					//�X�R�A�B
	
	Font m_font;		//�t�H���g�B

};

