#pragma once

class Field : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL; //頂点バッファ
	CTexture* m_Texture = NULL;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};