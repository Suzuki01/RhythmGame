#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "field.h"
#include "mesh_field.h"
#include "polygon.h"
#include "scene.h"
#include "quaternion.h"
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

void Transform::SetWorldMatrix() {
	XMMATRIX world;
	world = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	world *= XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y,Rotation.z);
	world *= XMMatrixTranslation(Position.x, Position.y, Position.z);
	CRenderer::SetWorldMatrix(&world);
}

//クォータニオンの回転を使ったワールド行列変換
void Transform::SetWorldQuaternionMatrix(){
	XMMATRIX world;
	world = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	world *= Quaternion.QuaternionToRotationMatrix();
	world *= XMMatrixTranslation(Position.x, Position.y, Position.z);
	CRenderer::SetWorldMatrix(&world);
}

//線形補完を使ったワールド行列変換
void Transform::SetWorldLerpMatrix(XMFLOAT3 start,XMFLOAT3 goal,float t) {
	XMMATRIX world;
	world = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	world *= XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);
	world *= Quaternion.QuaternionLerp(start, goal, t);
	CRenderer::SetWorldMatrix(&world);
}

void Transform::SetWorldSlerpMatrix(XMFLOAT4 startQ, XMFLOAT4 goalQ, float t) {
	XMMATRIX world;
	world = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
//	world *= XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);
	world *= Quaternion.QuaternionSlerp(startQ, goalQ, t);
	CRenderer::SetWorldMatrix(&world);
}

void Transform::SetBillBoardWorldMatrix() {
	XMMATRIX translation;
	XMMATRIX scale;
	XMMATRIX mtxInvV;

	translation = XMMatrixTranslation(Position.x, Position.y, Position.z);
	scale = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	Scene* scene = CManager::GetScene();
	scene->GetComponent<CCamera>(0);
	CCamera* camera = scene->GetComponent<CCamera>(0);
	mtxInvV = XMMatrixTranspose(camera->GetViewMatrix());
	mtxInvV.r[0].m128_f32[3] = 0.0f;
	mtxInvV.r[1].m128_f32[3] = 0.0f;
	mtxInvV.r[2].m128_f32[3] = 0.0f;
	XMMATRIX world = scale * mtxInvV * translation;
	CRenderer::SetWorldMatrix(&world);
}


