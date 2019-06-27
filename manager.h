#pragma once

class Scene; //前方宣言 プロトタイプ宣言のようなもの

class CManager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Scene* GetScene();
};