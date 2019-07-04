#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "quaternion.h"

class Transform {
public:
	Quaternion Quaternion;
	XMFLOAT3 Position;
	XMFLOAT3 Scale;
	XMFLOAT3 Rotation;
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();
	XMFLOAT3 GetScale();
	void SetWorldMatrix();
	void SetWorldQuaternionMatrix();
	void SetBillBoardWorldMatrix();
	void SetWorldLerpMatrix(XMFLOAT3 start, XMFLOAT3 goal, float t);
	void SetWorldSlerpMatrix(XMFLOAT4 startQ, XMFLOAT4 goalQ, float t);
};

#endif // !TRANSFORM_H_
