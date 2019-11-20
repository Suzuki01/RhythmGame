#include "main.h"
#include "game_object.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "notes.h"
#include "notes_object.h"

void NotesObject::Init()
{

}

void NotesObject::UnInit()
{
	
}

void NotesObject::Update()
{
	if (Input::Keyboard_IsTrigger('W')) {
		int judge = Judgement(Sound::GetCurrentBeats(),Notes::GetNotesTime(0));
		if (judge == 1 && judge == 2) {
			Notes::Destory();
			m_pModel.erase(m_pModel.begin());
		}
	}
	
	if (Sound::GetCurrentBeats() <= Notes::GetCurrentNotesTime(0) - 10 ) {
		Create();
	//	Notes::Create(0);
	}
	int i = 0;
	for (CModel* object : m_pModel) {
		object->Position.z = Notes::GetNotesTime(i) - Sound::GetCurrentBeats();
		object->Update();
		i++;
	}
}

void NotesObject::Draw()
{
	XMMATRIX world;
	for (CModel* object : m_pModel) {
		world = XMMatrixTranslation(object->Position.x, object->Position.y, object->Position.z);
		CRenderer::SetWorldMatrix(&world);
		object->Draw();
	}

}

void NotesObject::Create()
{
	CModel* model = new CModel;
	model->Load("asset/miku_01.obj");
//	model->Position = { 0.0f, 0.0f,18.0f };
	m_pModel.push_back(model);
}


int Judgement(float currentBeats, float judgeBeats) {
	float inequality = judgeBeats - currentBeats;
	if (inequality > 0.3 && inequality <= 0.5) {
		return 3;
	}
	else if (inequality > 0.2 && inequality <= 0.3) {
		return 2;
	}
	else if (inequality <= 0.2 && inequality >= -0.2) {
		return 1;
	}
	else {
		return 0;
	}
}