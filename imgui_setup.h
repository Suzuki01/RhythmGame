#ifndef IMGUI_SETUP_H_
#define IMGUI_SETUP_H_

class ImguiSetup {
public :
	static void Init();
	static void Update();
	static void Draw();
	static void UnInit();
	static float GetStartBeats();
private:
	static bool m_isChange;
	static float m_beats;
};

#endif // !IMGUI_SETUP_H_
