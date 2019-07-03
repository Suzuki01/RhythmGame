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
};

#endif // !TRANSFORM_H_
