#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	�}�b�v�`�b�v�B
*/
class MapChip {
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*@param[in] objData			�I�u�W�F�N�g���B
	*/
	MapChip(const LevelObjectData& objData);
	/*!
	* @brief	�`��B
	*/
	void Draw();
private:
	SkinModel m_model;		//!<���f���B
	SkinModelRender* m_skinModelRender;
	PhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B

	const char* m_psmain;
	const char* m_vsmain;
	
};