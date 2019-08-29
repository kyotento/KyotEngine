/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X�B
/// </summary>

#pragma once

#define _CGAMEOBJECT_H_

class GameObjectManager;
typedef unsigned char GameObjectPriority; //unsigned char�̓��`��B�Q�[���I�u�W�F�N�g�̎��s�D��x�B

class GameObject /*:  Noncopy*/
{

public:
	GameObject() :
		m_priority(0),       //�����D��x�O�B
		m_startflag(false),  //false�B
		m_deadflag(false)    //�ŏ��͎���łȂ��B
	{
	}

	virtual ~GameObject();

	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	virtual bool Start()
	{
		return true;
	}

	/// <summary>
	/// �A�b�v�f�[�g�֐��B
	/// </summary>
	virtual void Update()
	{

	}

	/// <summary>
	/// 
	/// </summary>
	virtual void Render();

	/// <summary>
	/// ���S�t���O�𗧂Ă�B���G���W���O�ł̎��s�֎~�B
	/// </summary>
	/// <param name="dead">���S�t���O</param>
	void SetDeadFlag(bool dead)
	{
		m_deadflag = dead;
	}

	/// <summary>
	/// Start�������ǂ�����ݒ肷��B
	/// </summary>
	/// <param name="start">startflag</param>
	void SetStart(bool start)
	{
		m_startflag = start;
	}

	/// <summary>
	/// ���S����B
	/// </summary>
	/// <returns>���S�t���O�B</returns>
	bool IsDead() const
	{
		return m_deadflag;
	}

	/// <summary>
	/// Start�������ǂ�����Ԃ��B
	/// </summary>
	/// <returns>Start�t���O�B</returns>
	virtual bool IsStart() const
	{
		return m_startflag;
	}

	/// <summary>
	/// �A�N�e�B�u����B
	/// </summary>
	/// <returns>�A�N�e�B�u�t���O�B</returns>
	bool IsActive() const
	{
		return m_activeflag;
	}

	/// <summary>
	/// �A�N�e�B�u�t���O�̐ݒ�B
	/// </summary>
	/// <param name="actflag">�A�N�e�B�u�t���O�B</param>
	void SetActiveFlag(bool actflag)
	{
		m_activeflag = actflag;
	}

	/// <summary>
	/// �^�O�̐ݒ�B
	/// </summary>
	/// <param name="tag">�^�O�B</param>
	void SetTag(unsigned int tag)
	{
		m_tags = tag;
	}

	/// <summary>
	/// �^�O���擾�B
	/// </summary>
	/// <returns>�^�O�B</returns>
	unsigned int GetTag() const
	{
		return m_tags;
	}

	/// <summary>
	/// GameObjectManager��new���ꂽ�B
	/// </summary>
	void SetNewGameObjectManager()
	{
		m_newGameObjectManager = true;
	}

	/// <summary>
	/// GameObjectManager��new���ꂽ����Ԃ��B
	/// </summary>
	/// <returns>GameObjectManger��new���ꂽ���B</returns>
	bool GetNewGameObjectManager() const
	{
		return m_newGameObjectManager;
	}

	/// <summary>
	/// m_registration�t���O�̐ݒ������B
	/// </summary>
	/// <param name="reg">GameObjectManager�Œǉ����ꂽ���B</param>
	void SetRegistration(bool reg)
	{
		m_registration = reg;
	}

	/// <summary>
	/// GemObjectManager�Œǉ����ꂽ����Ԃ��B
	/// </summary>
	/// <returns>GAmeObjectManger�Œǉ����ꂽ���t���O</returns>
	bool GetRegistration() const
	{
		return m_registration;
	}

	/// <summary>
	/// ���s�D��x��ݒ肷��N���X�B
	/// </summary>
	/// <param name="pri">���s�D��x�B</param>
	void SetPriority(GameObjectPriority pri)
	{
		m_priority = pri;
	}

	/// <summary>
	/// �l�[���L�[��ݒ肷��B
	/// </summary>
	/// <param name="snk">���O�L�[�B</param>
	void SetNameKey(unsigned int snk)
	{
		m_nameKey = snk;
	}

	/// <summary>
	/// Render���g���Ƃ��̃t�B���^�[�B
	/// </summary>
	void RenderWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList)
		{
			Render();
		}
	}

	/// <summary>
	/// �A�b�v�f�[�g�t�B���^�[�B
	/// </summary>
	void UpdateWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList)
		{
			Update();
		}
	}

	/// <summary>
	/// Start��D������ݍ��ރt�B���^�[�B
	/// </summary>
	void StartWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList) {
			if (Start()) {
				//���������������B
				m_startflag = true;
			}
		}
	}

protected://�h���N���X�Ŏg�����B

	GameObjectPriority m_priority;    //���s�D��x�B
	 
	bool m_startflag;                 //�X�^�[�g�������ۂ��̃t���O�B
	bool m_deadflag;                  //���S�t���O�B
	bool m_isRegistDeadList = false;  //�l�͂ˁA���S���X�g�ɐς܂ꂽ�������񂾁B
	bool m_activeflag = true;         //�A�N�e�B�u���ۂ��t���O�B
	bool m_newGameObjectManager;      //�Q�[���I�u�W�F�N�g�}�l�[�W����new���ꂽ���B
	bool m_registration = false;      //GameObjectManager�œo�^���ꂽ��(AddGameObject�Ŏg��)�B
	unsigned int m_tags = 0;          //�^�O�B
	unsigned int m_nameKey = 0;	      //���O�L�[�B

};

