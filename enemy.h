#pragma once

class CModel;

class Enemy : public GameObject {
public:
	CModel* m_Model;
	Enemy();
	virtual ~Enemy();
	//�e�N���X������
	void Init();
	void Update();
	void Draw();
	void UnInit();
	void SetPosition(XMFLOAT3 position);
};
