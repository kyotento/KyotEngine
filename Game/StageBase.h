/// <summary>
/// �t�B�[���h�̊��N���X�B
/// </summary>
#pragma once
#include "level/Level.h"
#include "StageObject.h"
#include "Desk.h"
#include "DishHold.h"
#include "GasStove.h"
#include "DustBox.h"
#include "CuttingDesk.h"
#include "Kitchen.h"
#include "Delivery.h"
#include "TomatoBox.h"
#include "OnionBox.h"
#include "Knife.h"
#include "Pot.h"
#include "Belongings.h"
#include "Dish.h"

class Desk;
class DishHold;
class GasStove;
class DustBox;
class CuttingDesk;
class Kitchen;
class Delivery;
class TomatoBox;
class OnionBox;
class Knife;
class StageBase : public GameObject
{
public:
	StageBase();
	~StageBase();

	bool Start();
	void Update();

	/// <summary>
	/// ���x����ΐ�������}���B
	/// </summary>
	/// <remarks>
	/// �e�I�u�W�F�N�g�̐�������������B
	/// �e�X�e�[�W�̃��x���������ɕK���Ă΂��B
	/// </remarks>
//	bool LevelGeneration(LevelObjectData& objData);

protected:

	Level m_level;							//���x���B
	Desk* m_desk = nullptr;					//���B
	DishHold* m_dishHold = nullptr;			//���M�u���B
	GasStove* m_gasStove = nullptr;			//�K�X�R�����B
	DustBox* m_dustbox = nullptr;			//�S�~���B
	CuttingDesk* m_cuttingDesk = nullptr;	//�܂Ȕt�����B
	Kitchen* m_kitchen = nullptr;			//���􂢏�B
	Delivery* m_delivery = nullptr;			//�󂯓n�����B
	TomatoBox* m_tomatoBox = nullptr;		//�g�}�g�̔��B
	OnionBox* m_onionBox = nullptr;			//�ʂ˂��̔��B
	Knife* m_knife = nullptr;				//�i�C�t�B
	Pot* m_pot = nullptr;					//��B
	Belongings* m_belongings = nullptr;		//�����Ƃ̂ł�����́B
	Dish* m_dish = nullptr;					//���M�B

private:

};

