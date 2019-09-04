#pragma once

class CPolygon : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL; //頂点バッファ
	CTexture* m_Texture = NULL;
public:
	void Init(char* fileName,int startX, int startY, int x, int y);
	void UnInit();
	void Update();
	void Draw();
	void Draw(char* fileName);
};
