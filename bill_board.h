#pragma once

class BillBoard : public GameObject {
private:
	//頂点バッファ
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture;
public:
	void Init(char* fileName);
	void Draw();
	void Update();
	void UnInit();
	void SetTexture(char* fileName);
	BillBoard();
	virtual ~BillBoard();
};