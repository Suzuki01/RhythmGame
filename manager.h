#pragma once

class Scene; //�O���錾 �v���g�^�C�v�錾�̂悤�Ȃ���

class CManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Scene* GetScene();
};