#pragma once


class CCamera : public GameObject
{
private:

	RECT m_Viewport;
	float rollTime;
	float rotationAmount;
	bool isRoll;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMMATRIX GetViewMatrix();
	XMMATRIX	m_ViewMatrix;
	void Roll(float time, bool x, bool y, bool z);
};