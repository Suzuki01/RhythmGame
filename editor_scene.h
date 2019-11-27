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
	static float m_CurrentPosition; //ÉrÅ[ÉgêîÇ≈îªífÇ∑ÇÈ
	static float m_CurrentTime;
	static float m_CurrentBeats;
	int i;
	CAudioClip* audio;
	void NoteCreate();
	int JudgeRane(float startPosX,float x);
	XMFLOAT3 CalcScreenToWorld(
		int Sx,  // 
		int Sy,  // 
		float fZ,  //
		int Screen_w,
		int Screen_h,
		XMMATRIX* View,
		XMMATRIX* Prj
	);
	XMFLOAT3 CalcScreenToXZ(
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		XMMATRIX* View,
		XMMATRIX* Prj
	);
};

#endif