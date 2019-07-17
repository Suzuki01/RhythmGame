#pragma once

class BillBoard : public GameObject {
private:
	//���_�o�b�t�@
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture;
public:
	void Init();
	void Draw();
	void Update();
	void UnInit();
	BillBoard();
	virtual ~BillBoard();
};