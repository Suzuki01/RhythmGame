#ifndef SELECT_LINE_H_
#define SELECT_LINE_H_

class SelectLine : public GameObject {
private:
	ID3D11Buffer* m_VertexBuffer = NULL; //���_�o�b�t�@
	CTexture* m_Texture = NULL;
	void SetOffset();
	void RaneLimitation();
public:
	BillBoard* m_Billboard;
	float m_BeatsOffset;	//�I�t�Z�b�g�r�[�g���i���݂̋Ȃ̈ʒu����ǂꂭ�炢����Ă��邩�j
	int m_MaxRane;			//�S���ŉ����[�������邩
	float m_MoveAmount;		//���ړ��̈ړ���
	int m_RaneNumber;		//���݂��郌�[���ԍ�
	void Init(char* fileName,XMFLOAT3 startPos,float verticalSize, float horizontalSize, int maxRane, float moveAmount);
	void Update();
	void UnInit();
	void Draw();
};

#endif // !SELECT_LINE_H_
