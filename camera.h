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
	XMMATRIX GetProjectMatrix();
	XMMATRIX GetWorldMatrix();
	XMMATRIX m_ViewMatrix;
	XMMATRIX m_ProjectionMatrix;
	XMMATRIX m_InvViewMatrix;
	void Roll(float time, bool x, bool y, bool z);
	bool GetVisibility(XMFLOAT3 position);
};