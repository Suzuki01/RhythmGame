#pragma once

class CModel;

class Player : public GameObject {
public:
	CModel* m_Model;
	//影クラスが入る
	void Init();
	void Update();
	void Draw();
	void UnInit();
};