#ifndef BILL_BOARD_H_
#define BILL_BOARD_H_

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

#endif // !BILL_BOARD_H_
