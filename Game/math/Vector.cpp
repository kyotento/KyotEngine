/*!
 * @brief	�x�N�g���N���X�B
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
*@brief	�s�񂩂�N�H�[�^�j�I�����쐬�B
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
		//�قړ��������Ȃ̂ŒP�ʃN�H�[�^�j�I���ɂ���B
		CQuaternion::Identity;
	}
	else if (t < -0.998f) {
		//�قڋt�����Ȃ̂ŁA
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