#pragma once
#include "Title.h"

class Title;
class Game : public GameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();


private:

	Title* m_title = nullptr;

};

