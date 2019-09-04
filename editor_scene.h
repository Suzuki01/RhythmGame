#ifndef EDITOR_SCENE_H_
#define EDITOR_SCENE_H_

#include "scene.h"

class EditorScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	int i;
};

#endif