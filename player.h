#ifndef PLAYER_H_
#define PLAYER_H_

class ModelAnimation;

class Player : public GameObject {
public:
	ModelAnimation* m_pModel;
	XMMATRIX matrix;
	//�e�N���X������
	void Init(XMFLOAT3 pos);
	void Update();
	void Draw();
	void UnInit();
	void Jump();
};

#endif