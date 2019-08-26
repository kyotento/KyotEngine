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

