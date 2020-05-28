#pragma once
#include "level/Level.h"
#include "GameObject.h"
#include "Flag.h"
#include "Bus.h"
#include "Bridge.h"
#include "River.h"
#include "StageSelectFloor.h"
#include "StageSelectDetailed.h"

class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();

	bool Start();

	void Update();


private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�X�P�[���B
	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	Flag* m_flag[3] = { nullptr,nullptr,nullptr };					//���B
	Bus* m_bus = nullptr;					//�o�X�B
	Bridge* m_bridge = nullptr;				//���B
	River* m_river = nullptr;				//��B
	StageSelectFloor* m_stageSelectFloor = nullptr;			//���B
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//�X�e�[�W�̏ڍ׉摜�G
	SpriteRender* m_spriteRender = nullptr;					//�X�v���C�g�B
	Sound* m_sound = nullptr;								//BGM�B

	Level m_level;							//���x���B

};

