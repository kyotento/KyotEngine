/// <summary>
/// �X�e�[�W�̏��B(�N���X�����ł̐������A���܂����f����Delete����Ȃ��������ߍ쐬)�B
/// </summary>
#pragma once
#include "physics/PhysicsStaticObject.h"
#include "StageObject.h"

class StageFloor : public StageObject
{
public:
	StageFloor();
	~StageFloor();

	bool Start();
	
	/// <summary>
	/// �X�e�[�W�̏��𐶐����鏈���B
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	void NewSelectFloor(int stageNum);


private:

};

