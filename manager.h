#pragma once

class Scene; //�O���錾 �v���g�^�C�v�錾�̂悤�Ȃ���

class CManager
{
public:
	static Scene* m_pScene;
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Scene* GetScene();
	template <typename T>
	static void SetScene() {
		if (m_pScene != nullptr) {
			m_pScene->UnInit();
			delete m_pScene;
		}

		m_pScene = new T();
		m_pScene->Init();
	}
};