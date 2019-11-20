#pragma once

typedef struct {
	XMFLOAT3 position;//VECTOR4は座標変換済み頂点rhw = 1.0が2dの時に入っていた
	XMFLOAT3 normal; //法線ベクトル
	XMFLOAT4 color;
	XMFLOAT2 texcoord;
}MeshFieldVertex;

class MeshField : public GameObject{
private:
	CTexture* m_texture;
	MeshFieldVertex* pMeshFieldVertex;
	float m_width;
	int m_sideMax;
	//頂点バッファ
	ID3D11Buffer* m_VertexBuffer = NULL;
	//インデックスバッファ
	ID3D11Buffer* m_IndexBuffer = NULL;

public:
	void Init(float width, float height, int Max, int sideMax, int lengthMax);
	void UnInit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 position);
};