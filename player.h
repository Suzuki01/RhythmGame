#pragma once

class CModel;

class Player : public GameObject {
public:
	CModel* m_Model;
	//‰eƒNƒ‰ƒX‚ª“ü‚é
	void Init();
	void Update();
	void Draw();
	void UnInit();
};