#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "manager.h"
#include "sound.h"
#include "score.h"
#include "scene.h"
#include "test_scene.h"
#include "audio_clip.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_setup.h"
#include "notes.h"

bool ImguiSetup::m_isChange = false;
float ImguiSetup::m_beats = 0;
bool ImguiSetup::m_isNoteCreate = false;
void ImguiSetup::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
	ImGui::StyleColorsDark();
}

void ImguiSetup::UnInit() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImguiSetup::Update() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (m_isChange) {
		m_isChange = false;
		CManager::SetScene<TestScene>();
	}
}

void ImguiSetup::Draw() {
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("SoundData");                          // Create a window called "Hello, world!" and append into it.

	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	if (ImGui::Button("Button")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
		Notes::Create(1,counter);
		counter++;
	}
	if (ImGui::Button("ResetButton"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter = 0;

	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Score = %f", Score::GetScore());
	ImGui::Checkbox("Transition Test Scene", &m_isChange);
	ImGui::Checkbox("Editor Note Create Push Button", &m_isNoteCreate);
	Sound::ImguiSoudData();
	ImGui::BeginChild("Scrolling");
//	for(int n = 0; n < Notes::)
	ImGui::EndChild();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

float ImguiSetup::GetStartBeats() {
	return m_beats;
}