#ifndef IMGUI_SETUP_H_
#define IMGUI_SETUP_H_

class ImguiSetup {
public :
	static void Init();
	static void Update();
	static void Draw();
	static void UnInit();
private:
	static bool m_isChange;
};

#endif // !IMGUI_SETUP_H_
