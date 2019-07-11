#pragma once

typedef struct {
	XMFLOAT3 position;//VECTOR4�͍��W�ϊ��ςݒ��_rhw = 1.0��2d�̎��ɓ����Ă���
	XMFLOAT3 normal; //�@���x�N�g��
	XMFLOAT4 color;
	XMFLOAT2 texcoord;
}MeshFieldVertex;

class MeshField : public GameObject{
private:
	CTexture* m_texture;
	MeshFieldVertex* pMeshFieldVertex;
	float m_width;
	int m_sideMax;

public:
	void Init(float width, float height, int Max, int sideMax, int lengthMax);
	void UnInit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 position);
};