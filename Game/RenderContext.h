#pragma once
#include "RenderTarget.h"
#include <stack>
class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	/// <summary>
	/// ���݂̃����_�����O�X�e�[�g���X�^�b�N�Ƀv�b�V���B
	/// </summary>
	void PushRenderState()
	{
		m_renderStateStack.push(m_currentRenderState);
	}

	/// <summary>
	/// �X�^�b�N�ɑޔ����������_�����O�X�e�[�g���|�b�v�B
	/// </summary>
	/// <param name="isSetRenderSyayeToRenderPipline">�|�b�v���������_�����O�X�e�[�g�������_�����O�p�C�v���C���ɐݒ�</param>
	void PopRenderState(bool isSetRenderSyayeToRenderPipline)
	{
		m_currentRenderState = m_renderStateStack.top();		//���݂̃����_�����O�X�e�[�g���X�^�b�N�̐擪�ɕύX�B
		m_renderStateStack.pop();
		if (isSetRenderSyayeToRenderPipline){
			m_pD3DDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
			m_pD3DDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
			m_pD3DDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
		}
	}


private:
	/// <summary>
	/// �e�탌���_�����O�X�e�[�g�B
	/// </summary>
	struct SRenderState {
		ID3D11DepthStencilState* depthStencilState = nullptr;	//���݂̃f�v�X�X�e���V���X�e�[�g�B
		ID3D11RasterizerState* rasterrizerState = nullptr;		//���݂̃��X�^���C�U�X�e�[�g�B
		ID3D11BlendState* blendState = nullptr;					//���݂̃u�����h�X�e�[�g�B
	};

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�B
	/// </summary>
	struct SRenderTarget {
		RenderTarget* renderTargets[8] = { nullptr };
		unsigned int numRenderTargetViews = 0;
	};
	ID3D11DeviceContext* m_pD3DDeviceContext = nullptr;			//�`��R�}���h��ς�ł����R���e�L�X�g�B

	SRenderState m_currentRenderState;				//���݂̃����_�����O�X�e�[�g�B
	std::stack<SRenderState> m_renderStateStack;	//�����_�����O�X�e�[�g�̃X�^�b�N�B
	std::stack<SRenderTarget> m_renderTargetStack;	//�����_�����O�^�[�Q�b�g�̃X�^�b�N�B

};

