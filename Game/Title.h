#pragma once
class Player;
class Title : public GameObject
{
public:
	Title();
	~Title();

	bool Start()override;
	void Update();


private:

	CVector3 m_position = CVector3::Zero();

	SpriteRender* m_spriteRender = nullptr;		//SpriteÅB
	Pad* m_pad = nullptr;
	Player* m_player = nullptr;
};

