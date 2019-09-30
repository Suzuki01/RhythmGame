#ifndef EDITOR_SCENE_H_
#define EDITOR_SCENE_H_


class EditorScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	float m_CurrentPosition; //ビート数で判断する
	float m_CurrentTime;
	float m_CurrentBeats;
	int i;
};

#endif