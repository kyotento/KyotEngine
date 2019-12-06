/*!
 * @brief	ベクトルクラス。
 */

#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"

const CVector4 CVector4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector4 CVector4::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
const CVector4 CVector4::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
const CVector4 CVector4::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
const CVector4 CVector4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };


/*!
*@brief	行列からクォータニオンを作成。
*/
void CQuaternion::SetRotation(const CMatrix& m)
{
	DirectX::XMStoreFloat4(&vec, DirectX::XMQuaternionRotationMatrix(m));
}

void CQuaternion::SetRotation(CVector3 from, CVector3 to)
{
	from.Normalize();
	to.Normalize();
	auto t = Dot(from, to);
	CVector3 rotAxis;
	if (t > 0.998f) {
		//ほぼ同じ向きなので単位クォータニオンにする。
		CQuaternion::Identity;
	}
	else if (t < -0.998f) {
		//ほぼ逆向きなので、
		//if (fabsf(to.x) < 1.0f) {
		//	//
		//	rotAxis = Cross(CVector3::AxisX, to);
		//}
		//else {
		//	rotAxis = Cross(CVector3::AxisY, to);
		//}
	}
	else {
		rotAxis = Cross(from, to);
	}
	rotAxis.Normalize();
	SetRotation(rotAxis, acos(t));
}