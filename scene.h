#pragma once
#include <list>
#include <typeinfo>
#include <vector>
#include "main.h"
#include "game_object.h"
#include "camera.h"
#include "texture.h"
#include "mesh_field.h"
#include "field.h"
#include "polygon.h"
#include "player.h"
#include "enemy.h"
#include "bill_board.h"
#include "audio_clip.h"

#define SCENE_MAX	(8)

class Scene {
protected:
	std::list<GameObject*> m_GameObject[SCENE_MAX];
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Init() = 0; //純粋仮想関数
//	virtual void UnInit();
//	virtual void Update();
//	virtual void Draw();

	//テンプレートメソッドはヘッダーにしか書けない
	//メモリはよく使うので乱用は控える
	template <typename T>
	T* AddGameObject(int Layer) {
		T* object = new T();
		m_GameObject[Layer].push_back(object);
		return object;
	}

	template <typename Type> 
	Type* GetComponent(int Layer) {
		for (int i = 0; i < SCENE_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				if (typeid(*object) == typeid(Type))
					return static_cast <Type*>(object);
			}
		}
		return nullptr;
	}

	template <typename Type>
	std::vector<Type*> GetComponents(int Layer) {
		std::vector<Type*> objects;
		for (GameObject* object : m_GameObject[Layer]) {
			if (typeid(*object) == typeid(Type)) {
				objects.push_back((Type*)object);
			}
		}
		return objects;
	}
	
	virtual void UnInit() {
		for (int i = 0; i < SCENE_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->UnInit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}
	
	virtual void Update() {
		for (int i = 0; i < SCENE_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object) {
				return object->Destroy();
			});
		}
	}

	virtual void Draw() {
		for (int i = 0; i < SCENE_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

	void DestroyGameObject(GameObject* GameObject) {
		GameObject->SetDestroy();
	}
	
	enum {
		CameraLayer,
		FieldLayer,
		SkyDomeLayer,
		JusticeFieldLayer,
		PlayerLayer,
		BillboardLayer,
		PolygonLayer,
	};
};