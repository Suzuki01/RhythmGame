#pragma once

class CModel;

class Player : public GameObject {
public:
	CModel* m_Model;
	//�e�N���X������
	void Init();
	void Update();
	void Draw();
	void UnInit();
};