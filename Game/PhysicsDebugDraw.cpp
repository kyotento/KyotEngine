/*!
 * @brief	コリジョンなどのデバッグ表示処理。
 */
#include "stdafx.h"
#include "PhysicsDebugDraw.h"


void PhysicsDebugDraw::Init() 
{
		
	//ラインストリップのテスト。
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		static_cast<int>(m_vertexBuffer.size()),
		sizeof(CVector4),
		&m_vertexBuffer[0],
		0,
		CIndexBuffer::enIndexType_32,
		nullptr
	);
	m_vs.Load( "shader/linePrimitive.fx", "VSMain", Shader::EnType::VS );
	m_ps.Load( "shader/linePrimitive.fx", "PSMain", Shader::EnType::PS );
	m_cb.Create(nullptr, sizeof(SConstantBuffer));
}

void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set( CVector3(from.x(), from.y(), from.z()) );
	m_vertexBuffer[baseIndex+1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;
		
}
void PhysicsDebugDraw::EndDraw()
{
	//定数バッファの更新。
	SConstantBuffer cb;
	cb.mView = Camera().GetViewMatrix();
	cb.mProj = Camera().GetProjectionMatrix();
	//m_renderContext->UpdateSubresource(m_cb, &cb);

	//m_renderContext->VSSetShader(m_vs);
	//m_renderContext->PSSetShader(m_ps);
	//m_renderContext->VSSetConstantBuffer(0, m_cb);
	//m_renderContext->UpdateSubresource(m_primitive.GetVertexBuffer(), &m_vertexBuffer[0]);
	//m_primitive.Draw(*m_renderContext, m_numLine*2);

	auto ge = g_graphicsEngine;
	ge->GetD3DDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), nullptr, 0);
	ge->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), nullptr, 0);
	ge->GetD3DDeviceContext()->UpdateSubresource(m_primitive.GetVertexBuffer().GetBody(), 0, NULL, &m_vertexBuffer[0], 0, 0);
	ge->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	ge->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	ge->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, &m_cb);
	m_primitive.Draw(m_numLine * 2);


}


