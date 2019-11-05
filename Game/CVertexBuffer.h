#pragma once
class CVertexBuffer
{
public:
	CVertexBuffer();
	~CVertexBuffer();

	bool Create(int numVertex, int stride, const void* pSrcVertexBuffer);
	/*!
	*@brief	�J���B
	*@details
	* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
	* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
	*/
	void Release();
	/*!
	*@brief	���_�X�g���C�h���擾�B
	*/
	int GetStride() const
	{
		return m_stride;
	}
	/*!
	*@brief ID3D11Buffer*���擾�B
	*/
	ID3D11Buffer*& GetBody()
	{
		return m_vertexBuffer;
	}
private:
	ID3D11Buffer * m_vertexBuffer = nullptr;	//!<���_�o�b�t�@�B
	int				m_stride = 0;				//!<���_�X�g���C�h�B

};

