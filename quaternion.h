#ifndef QUATERNION_H_
#define QUATERNION_H_

class Quaternion {
public:
	XMFLOAT4 q;
	void EulerToQuaternion(float x,float y, float z);
	void QuaternionToEuler(float qx, float qy, float qz, float qw);
	XMMATRIX QuaternionToRotationMatrix();
	XMMATRIX QuaternionRotationAxis(float angle);
	XMMATRIX QuaternionLerp(XMFLOAT3 start, XMFLOAT3 goal, float t);
	XMMATRIX QuaternionSlerp(XMFLOAT4 startQ, XMFLOAT4 goalQ, float t);
};

#endif // !QUATERNION_H_
