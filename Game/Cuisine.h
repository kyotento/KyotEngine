/// <summary>
/// �����N���X�B
/// </summary>
#include "StageObject.h"
#pragma once

class Cuisine : public StageObject
{
public:
	Cuisine();
	~Cuisine();

	bool Start();
	void Update();

	//�X�[�v�𐶐����鏈���B
	void NewSoup();

private:


};

