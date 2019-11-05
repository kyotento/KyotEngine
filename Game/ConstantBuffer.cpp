#include "stdafx.h"
#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer()
{
}


ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::Create(const void* pInitData, int bufferSize)
{
	//ConstantBuffer�p�̃o�b�t�@��`���쐬����B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	return GPUBuffer::Create(pInitData, bufferDesc);
}