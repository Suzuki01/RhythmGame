#pragma once


class CCamera : public GameObject
{
private:

	RECT m_Viewport;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMMATRIX GetViewMatrix();
	XMMATRIX	m_ViewMatrix;
};