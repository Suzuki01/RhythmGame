#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "main.h"
#include "transform.h"

class GameObject {
public:
	bool m_Destroy = false;
	Transform m_Transform;
	GameObject() {};
	virtual ~GameObject() {};
	virtual void Init() {};
	virtual void Update() {};
	virtual void UnInit() {};
	virtual void Draw() {};

	void SetDestroy() {
		m_Destroy = true;
	}
	
	bool Destroy() {
		if (m_Destroy) {
			UnInit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}
};


#endif