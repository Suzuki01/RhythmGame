#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

class TitleScene : public Scene{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	CAudioClip* m_SE;

};

#endif // !TITLE_SCENE_H_
