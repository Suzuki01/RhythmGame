#ifndef EDITOR_SCENE_H_
#define EDITOR_SCENE_H_


class EditorScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	static float GetCurrentBeats();
private:
	static float m_CurrentPosition; //ビート数で判断する
	static float m_CurrentTime;
	static float m_CurrentBeats;
	int i;
	CAudioClip* audio;
	void NoteCreate();
	int JudgeRane(
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
		int Screen_w,
		int Screen_h,
		XMMATRIX* View,
		XMMATRIX* Prj,
		XMMATRIX* world);
};

#endif