#pragma once

class BillBoard;

class Bullet : public GameObject{
public:
	bool m_flag;
	XMFLOAT3 m_vector;
	Bullet();
	~Bullet();
	BillBoard* m_BillBoard;
	void Init();
	void UnInit();
	void Create();
	void Draw();
	void Update();
	void SetPosition(XMFLOAT3 position);
	void Up();
};