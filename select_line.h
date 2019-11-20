#ifndef SELECT_LINE_H_
#define SELECT_LINE_H_

class SelectLine : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL; //頂点バッファ
	CTexture* m_Texture = NULL;
	void SetOffset();
	void RaneLimitation();
public:
	BillBoard* m_Billboard;
	float m_BeatsOffset;	//オフセットビート数（現在の曲の位置からどれくらい離れているか）
	int m_MaxRane;			//全部で何個レーンがあるか
	float m_MoveAmount;		//横移動の移動量
	int m_RaneNumber;		//現在いるレーン番号
	void Init(char* fileName,XMFLOAT3 startPos,float verticalSize, float horizontalSize, int maxRane, float moveAmount);
	void Update();
	void UnInit();
	void Draw();
};

#endif // !SELECT_LINE_H_
