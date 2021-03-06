#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	マップチップ。
*/
class MapChip {
public:
	/*!
	* @brief	コンストラクタ。
	*@param[in] objData			オブジェクト情報。
	*/
	MapChip(const LevelObjectData& objData);
	/*!
	* @brief	描画。
	*/
	void Draw();
private:
	SkinModel m_model;		//!<モデル。
	SkinModelRender* m_skinModelRender;
	PhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。

	const char* m_psmain;
	const char* m_vsmain;
	
};