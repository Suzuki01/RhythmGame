#pragma once

class Transform {
public:
	XMFLOAT3 Position;
	XMFLOAT3 Scale;
	XMFLOAT3 Rotation;
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();
	XMFLOAT3 GetScale();
	void SetWorldMatrix();
	void SetBillBoardWorldMatrix();
};