#ifndef QUATERNION_H_
#define QUATERNION_H_

class Quaternion {
public:
	XMFLOAT4 q;
	void EulerToQuaternion(float x,float y, float z);
	void QuaternionToEuler(float qx, float qy, float qz, float qw);
	XMMATRIX QuaternionToRotationMatrix();
};

#endif // !QUATERNION_H_
