/// <summary>
/// �^�C�g���B
/// </summary>

#pragma once
#include "Game.h"

class Game;
class Title : public GameObject
{
public:
	Title();
	~Title();

	bool Start()override;
	void Update();

private:

	CVector3 m_position = CVector3::Zero();		//���W�B

	SpriteRender* m_spriteRender = nullptr;		//Sprite�B
	Sound* se = nullptr;
	Pad* m_pad = nullptr;						//�R���g���[��Pad�N���X�B
	Game* m_game = nullptr;						//Game�N���X�B

	FontRender* m_fontRender = nullptr;			//�t�H���g�����N���X�B
	FontRender* m_fontRender2 = nullptr;		//�t�H���g�����N���X�B

};

