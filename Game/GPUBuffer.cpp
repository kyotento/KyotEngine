#include "stdafx.h"
#include "GPUBuffer.h"


GPUBuffer::GPUBuffer()
{
}


GPUBuffer::~GPUBuffer()
{
	Release();
}

void GPUBuffer::Release()
{
	if (m_gpuBuffer != nullptr) {
		m_gpuBuffer->Release();
		m_gpuBuffer = nullptr;
	}
}
bool GPUBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
{
	Release();
	HRESULT hr;
	if (pInitData) {
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = pInitData;
		hr = GraphicsEngine().GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_gpuBuffer);
	}
	else {
		hr = GraphicsEngine().GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_gpuBuffer);
	}
	if (FAILED(hr)) {
		return false;
	}
	return true;
}