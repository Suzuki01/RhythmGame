#pragma once

typedef struct SphereCollision_tag {
	XMFLOAT3 position;
	float radius;
	bool flag;
}SphereCollision;

class Judgement{
	void Init();
	void UnInit();
	void Update();
	void Draw();
};