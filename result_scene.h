#ifndef RESULT_SCENE_H_
#define RESULT_SCENE_H_

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "title_scene.h"
#include "input.h"
#include "texture.h"
#include "texture_manager.h"
#include "manager.h"
#include "score.h"
#include "thumbnail.h"

class ResultScene : public Scene {
private:
	CPolygon* m_pPolygon;
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !RESULT_SCENE_H_
