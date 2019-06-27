#pragma once

class MeshField : public GameObject{
private:
	CTexture* m_texture;
public:
	void Init(float width, float height, int Max, int sideMax, int lengthMax);
	void UnInit();
	void Update();
	void Draw();
};