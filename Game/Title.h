#pragma once
class Title : public GameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();


private:

	SpriteRender* m_spriteRender = nullptr;		//SpriteÅB

};

