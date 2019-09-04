#ifndef SKY_DOME_H_
#define SKY_DOME_H_

#include "main.h"
#include "game_object.h"

class SkyDome : public GameObject {
public:
	void Init();
	void UnInit();
	void Draw();
	void Update();
};

#endif // !SKY_DOME_H_
