#pragma once
#include "bulletPhysics/src/LinearMath/btIDebugDraw.h"
#include "graphics/Shader.h"

#include "math/Vector.h"

class DebugWireframe :
	public btIDebugDraw
{
public:
	DebugWireframe();
	~DebugWireframe();
	/// <summary>
	/// �ݒ�̏���
	/// </summary>
	void Prepare();
	/// <summary>
	/// �f�o�C�X�R���e�L�X�g�ɐݒ�
	/// 1�t���[�����Ɉ��
	/// </summary>
	void Context();
	//�K�{
	/// <summary>
	/// �����ƂɈ�񂸂Ă΂��
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="color"></param>
	void    drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void    setDebugMode(int debugMode) override {};
	int     getDebugMode() const override 
	{
		return true;
	};

	//�������Ȃ��Ă����Ȃ� {}�@�K�v�ł���Β�`
	void    drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
	void    reportErrorWarning(const char* warningString) override {};
	void    draw3dText(const btVector3& location, const char* textString) override {};
private:
	struct Vertex 
	{
		CVector3 pos;
		CVector3 color;
	};
	
	ID3D11Buffer*		m_vertexBuffer = nullptr;			//���_�o�b�t�@�B
	ID3D11Buffer*		m_constantBuffer = nullptr;			//�萔�o�b�t�@�B
	Shader m_Vshader;	//���_�V�F�[�_�[
	Shader m_Pshader;	//�s�N�Z���V�F�[�_�[
};

