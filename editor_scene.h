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
	static float m_CurrentPosition; //�r�[�g���Ŕ��f����
	static float m_CurrentTime;
	static float m_CurrentBeats;
	int i;
	CAudioClip* audio;
	void NoteCreate();
	int JudgeRane(
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		XMMATRIX* View,
		XMMATRIX* Prj,
		XMMATRIX* world);
};

#endif