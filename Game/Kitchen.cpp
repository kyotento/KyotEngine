#include "stdafx.h"
#include "Kitchen.h"


Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{

}


bool Kitchen::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/kitchen/kitchen.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBoxLong.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enKitchen);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

//お皿を洗う。
void Kitchen::DishWashing()
{
	//お皿洗いの上に汚れたお皿があるとき。
	//todo 絶　2Dのバグな直ったらGaugeを生成する。
	//拡大処理をして拡大値が１になったら汚れたお皿を消して新しいお皿を生成する。
	//todo 仮　今はゲージを描画できないので条件をタイマーにする。

	if (m_dishDirty->GetDirtyDishNum() > 0) {
		m_timerK += 1;

		if (m_timerK >= 120) {		//２秒以上たったとき。

			//乗っているお皿が1個の時。
			if (m_dishDirty->GetDirtyDishNum() <= 1 && m_dishDirty->GetDirtyDishNum() > 0) {
				DeleteGO(m_dishDirty);						//汚れたお皿クラスを消す。

				if (m_dish != nullptr) {			//お皿があるとき。

					m_dish->AddDishList();			//お皿を生成する。
				}

				if (m_dish == nullptr) {			//お皿がないとき。

					m_dish = NewGO<Dish>(0, "dish");			//お皿を生成する。
				}

				SetDishPos(m_dish);					//お皿の座標を指定。
				m_timerK = 0;
			}

			//乗っている汚れたお皿の数が2個以上のとき。
			if (m_dishDirty->GetDirtyDishNum() > 1) {
				m_dishDirty->DeleteDishs();					//汚れたお皿を消す。

				if (m_dish != nullptr) {

					m_dish->AddDishList();			//お皿を生成する。
				}

				if (m_dish == nullptr) {

					m_dish = NewGO<Dish>(0, "dish");			//お皿を生成する。
				}

				SetDishPos(m_dish);
				m_timerK = 0;
			}
		}
	}
}

//お皿のインスタンスを消す処理。
void Kitchen::DeleteDishInstance()
{
	if (m_dish != nullptr) {					//お皿のインスタンスがあるとき。
		if (m_dish->GetDisListNum() <= 0)		//リストの中身がないとき。
		{
			m_dish = nullptr;					//お皿のインスタンスをnullに。
		}
	}

}

//更新処理。
void Kitchen::Update()
{
	if (m_dish == nullptr)			//お皿のインスタンスがNullのとき。
	{
		m_state = en_default;			//状態を何も乗っていない状態に。
	}

}
