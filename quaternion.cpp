#include "main.h"
#include "quaternion.h"

void Quaternion::EulerToQuaternion(float x, float y, float z) {
//	XMQuaternionBaryCentric
	float c1 = XMScalarCos(x * 0.5f);
	float c2 = XMScalarCos(y * 0.5f);
	float c3 = XMScalarCos(z * 0.5f);

	float s1 = XMScalarSin(x * 0.5f);
	float s2 = XMScalarSin(y * 0.5f);
	float s3 = XMScalarSin(z * 0.5f);

	q.x = s1 * c2 * c3 + c1 * s2 * s3;
	q.y = c1 * s2 * c3 - s1 * c2 * s3;
	q.z = c1 * c2 * s3 - s1 * s2 * c3;
	q.w = c1 * c2 * c3 + s1 * s2 * s3;
}

void Quaternion::QuaternionToEuler(float qx, float qy, float qz, float qw) {
	float x2 = qx * qx;
	float y2 = qy * qy;
	float z2 = qz * qz;

	float xy = qx * qy;
	float xz = qx * qz;
	float yz = qy * qz;
	float wx = qw * qx;
	float wy = qw * qy;
	float wz = qw * qz;

	// 1 - 2y^2 - 2z^2
	float m00 = 1.0f - (2.0f * y2) - (2.0f * z2);

	// 2xy + 2wz
	float m01 = (2.0f * xy) + (2.0f * wz);

	// 2xy - 2wz
	float m10 = (2.0f * xy) - (2.0f * wz);

	// 1 - 2x^2 - 2z^2
	float m11 = 1.0f - (2.0f * x2) - (2.0f * z2);

	// 2xz + 2wy
	float m20 = (2.0f * xz) + (2.0f * wy);

	// 2yz+2wx
	float m21 = (2.0f * yz) - (2.0f * wx);

	// 1 - 2x^2 - 2y^2
	float m22 = 1.0f - (2.0f * x2) - (2.0f * y2);


	float tx, ty, tz;
	
	if (m21 == 1.0f)
	{
		
		tx = XM_PI / 2.0f;
		ty = 0;
		tz = atan2f(m10, m00);
	}
	else if (m21 == -1.0f)
	{
		tx = -XM_PI / 2.0f;
		ty = 0;
		tz = atan2f(m10, m00);
	}
	else
	{
		tx = XMScalarASin(-m21);
		ty = atan2f(m20, m22);
		tz = atan2f(m01, m11);
	}

	tx = XMConvertToDegrees(tx);
	ty = XMConvertToDegrees(ty);
	tz = XMConvertToDegrees(tz);

}

XMMATRIX Quaternion::QuaternionToRotationMatrix() {
	XMMATRIX RotationMatrix = XMMatrixRotationQuaternion(XMLoadFloat4(&q));
/*	XMMATRIX RotationMatrix;
	RotationMatrix = {
		{1 - 2 * q.y * q.y - 2 * q.z * q.z,         2 * q.x * q.y + 2 * q.w * q.z,   2 * q.x * q.z - 2 * q.w * q.y,  0.0f},
		{2 * q.x * q.y - 2 * q.w * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z + 2 * q.w * q.x,  0.0f},
		{2 * q.x * q.z + 2 * q.w * q.y, 2 * q.y * q.z - 2 * q.w * q.x,   1 - 2 * q.x * q.x - 2 * q.y * q.y,0.0f},
		{0.0f,0.0f,0.0f,1.0f},
	};*/
	return RotationMatrix;
}

XMMATRIX Quaternion::QuaternionRotationAxis(float angle) {
	XMMATRIX RotationMatrix = XMMatrixRotationQuaternion(XMQuaternionRotationAxis(XMLoadFloat4(&q),angle));
	return RotationMatrix;
}

XMMATRIX Quaternion::QuaternionLerp(XMFLOAT3 start, XMFLOAT3 goal, float t) {
	XMMATRIX TranslationMatrix = XMMatrixTranslationFromVector(XMVectorLerp(XMLoadFloat3(&start), XMLoadFloat3(&goal), t));
	return TranslationMatrix;
}

XMMATRIX Quaternion::QuaternionSlerp(XMFLOAT4 startQ, XMFLOAT4 goalQ, float t) {
	XMMATRIX TranslationMatrix = XMMatrixRotationQuaternion(XMQuaternionSlerp(XMLoadFloat4(&startQ), XMLoadFloat4(&goalQ), t));
	return TranslationMatrix;
}