#pragma once

class CModel;

class Enemy : public GameObject {
public:
	CModel* m_Model;
	Enemy();
	virtual ~Enemy();
	//影クラスが入る
	void Init();
	void Update();
	void Draw();
	void UnInit();
	void SetPosition(XMFLOAT3 position);
};
