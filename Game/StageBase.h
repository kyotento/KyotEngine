#pragma once
#include "level/Level.h"

/// <summary>
/// �t�B�[���h�̊��N���X�B
/// </summary>
class StageBase : public GameObject
{
public:
	StageBase();
	~StageBase();

	bool Start();
	void Update();

protected:

	Level m_level;				//���x���B

private:

};

