#pragma once

class CPolygon : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL; //���_�o�b�t�@
	CTexture* m_Texture = NULL;
public:
	void Init(char* fileName,int startX, int startY, int x, int y);
	void Uninit();
	void Update();
	void Draw();
};
