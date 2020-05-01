#include "stdafx.h"
#include "Stage_1.h"


Stage_1::Stage_1()
{
}

Stage_1::~Stage_1()
{	
	DeleteGO(m_stageFloor);
	DeleteGOs("dish");
	DeleteGOs("desk");
	DeleteGOs("dishhold");
	DeleteGOs("gasstove");

	DeleteGOs("pot");
	DeleteGOs("dustbox");
	DeleteGOs("cuttingdesk");
	DeleteGOs("kitchen");

	DeleteGOs("delivery");
	DeleteGOs("tomatobox");
	DeleteGOs("onionbox");
	DeleteGOs("knife");
}

bool Stage_1::Start()
{

	m_level.Init(L"Assets/level/stage_1.tkl", [&](LevelObjectData& objData)
		{
			
		//	LevelGeneration(objData);

			//地面。
			if (objData.EqualObjectName(L"kari_floor") == true)
			{
				m_stageFloor = NewGO<StageFloor>(0, "stagefloor");
				m_stageFloor->NewSelectFloor(1);
				m_stageFloor->SetPosition(objData.position);
				m_stageFloor->SetScale(objData.scale);
				m_stageFloor->SetRotation(objData.rotation);

			}

			//机。
			if (objData.EqualObjectName(L"Desk") == true)
			{
				m_desk = NewGO<Desk>(0, "desk");
				m_desk->SetPosition(objData.position);
				m_desk->SetRotation(objData.rotation);
				m_desk->SetScale(objData.scale);

				m_dishNum += 1;			//生成したお皿の数を増やす。

				//お皿。
				if (m_dishNum <= m_dishNumUpperLimit) {
					m_dish = NewGO<Dish>(0, "dish");		//お皿を生成する、
					CVector3 pos;							//お皿の座標。
					pos = objData.position;					//机の座標をお皿の座標に代入。
					pos.y += 80.f;							//Y座標を上げてやる。
					m_dish->SetPosition(pos);				//お皿の座標を設定。	
					m_desk->PutThings(m_dish);				//机の上にお皿を置く処理。
					m_desk->SetState(ObjectAbove::en_onObject);					//お皿を置いた机のステートを変更。
				}

			}

			//お皿置き。
			if (objData.EqualObjectName(L"DishHold") == true)
			{
				m_dishHold = NewGO<DishHold>(0, "dishhold");
				m_dishHold->SetPosition(objData.position);
				m_dishHold->SetRotation(objData.rotation);
				m_dishHold->SetScale(objData.scale);
			}

			//ガスコンロ。
			if (objData.EqualObjectName(L"gas_stove") == true)
			{
				m_gasStove = NewGO<GasStove>(0, "gasstove");
				m_gasStove->SetPosition(objData.position);
				m_gasStove->SetRotation(objData.rotation);
				m_gasStove->SetScale(objData.scale);

				//お鍋。
				m_pot = NewGO<Pot>(0, "pot");		//鍋をNew。
				CVector3 position;				//鍋の仮値。
				position = objData.position;		//ガスコンロの座標を代入。
				position.y += 80.f;				//ｙ座標のみ上げてやる。
				m_pot->SetPosition(position);		//鍋の座標指定。

				m_gasStove->PutThings(m_pot);		//ガスコンロの上に鍋を置く処理。

				m_gasStove->SetState(ObjectAbove::en_onObject);			//ガスコンロのステート変更。

			}

			//ゴミ箱。
			if (objData.EqualObjectName(L"DustBox") == true)
			{
				m_dustbox = NewGO<DustBox>(0, "dustbox");
				m_dustbox->SetPosition(objData.position);
				m_dustbox->SetRotation(objData.rotation);
				m_dustbox->SetScale(objData.scale);

			}

			//まな板付き机。
			if (objData.EqualObjectName(L"cutting_desk") == true)
			{
				m_cuttingDesk = NewGO<CuttingDesk>(0, "cuttingdesk");
				m_cuttingDesk->SetPosition(objData.position);
				m_cuttingDesk->SetRotation(objData.rotation);
				m_cuttingDesk->SetScale(objData.scale);
			}

			//水洗い場。
			if (objData.EqualObjectName(L"kitchen") == true)
			{
				m_kitchen = NewGO<Kitchen>(0, "kitchen");
				m_kitchen->SetPosition(objData.position);
				m_kitchen->SetRotation(objData.rotation);
				m_kitchen->SetScale(objData.scale);
			}

			//受け渡し所。
			if (objData.EqualObjectName(L"derivery") == true)
			{
				m_delivery = NewGO<Delivery>(0, "delivery");
				m_delivery->SetPosition(objData.position);
				m_delivery->SetRotation(objData.rotation);
				m_delivery->SetScale(objData.scale);
			}

			//トマトの箱。
			if (objData.EqualObjectName(L"TomatoBox") == true)
			{
				m_tomatoBox = NewGO<TomatoBox>(0, "tomatobox");
				m_tomatoBox->SetPosition(objData.position);
				m_tomatoBox->SetRotation(objData.rotation);
				m_tomatoBox->SetScale(objData.scale);
			}

			//玉ねぎの箱。
			if (objData.EqualObjectName(L"OnionBox") == true)
			{
				m_onionBox = NewGO<OnionBox>(0, "onionbox");
				m_onionBox->SetPosition(objData.position);
				m_onionBox->SetRotation(objData.rotation);
				m_onionBox->SetScale(objData.scale);
			}

			//包丁。
			if (objData.EqualObjectName(L"Knife") == true)
			{
				m_knife = NewGO<Knife>(0, "knife");
				m_knife->SetPosition(objData.position);
				m_knife->SetRotation(objData.rotation);
				m_knife->SetScale(objData.scale);
			}

			return true;

		});

		m_delivery->SetDishHold(m_dishHold);		//お皿置きのインスタンスを料理受け渡し口で送る。

	return true;
}

void Stage_1::Update()
{
}
