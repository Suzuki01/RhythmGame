#include "main.h"
#include "transform.h"


XMFLOAT3 Transform::GetPosition() {
	return Position;
}

XMFLOAT3 Transform::GetRotation() {
	return Rotation;
}

XMFLOAT3 Transform::GetScale() {
	return Scale;
}