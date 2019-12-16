/// <summary>
/// ���ꂽ���M�B
/// </summary>
#pragma once
#include "Belongings.h"

class DishDirty : public Belongings
{
public:
	DishDirty();
	~DishDirty();

	bool Start();
	void Update();

	/// <summary>
	/// ����Ă��邨�M�̐��𑝂₷�����B
	/// </summary>
	void AddDish();

	/// <summary>
	/// ����Ă��邨�M�̐������炷�����B
	/// </summary>
	void DeleteDishs();

	/// <summary>
	/// ���ꂽ���M�̐���ݒ肷��B
	/// </summary>
	/// <param name="dirtyDishNum">���ꂽ���M�̐�</param>
	void SetDirtyDishNum(int dirtyDishNum)
	{
		m_dirtyDishNum = dirtyDishNum;
	}

	void GaugeUpdate();

	/// <summary>
	/// ���ꂽ���M�̐����擾����B
	/// </summary>
	/// <returns>���ꂽ���M�̐�</returns>
	int GetDirtyDishNum()
	{
		return m_dirtyDishNum;
	}

	/// <summary>
	/// ���ꂽ���M�N���X�Ő������ꂽ�Q�[�W�̃C���X�^���X���擾����B
	/// </summary>
	/// <returns>�Q�[�W�̃C���X�^���X</returns>
	Gauge* GetGauge()
	{
		return m_gauge;
	}

private:

	int m_dirtyDishNum = 0;			//���ꂽ���M�̐��B

	typedef std::list<SkinModelRender*>DishDirtyList;			//���M���d�˂邽�߂̃��X�g�B
	DishDirtyList m_dishDirtyList;								//���X�g�B

};

