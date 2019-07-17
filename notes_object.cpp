#include "main.h"
#include "game_object.h"
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
	for (int i = 0; i < Notes::GetMaxNotes(); i++) {
		if (Sound::GetTime() >= Notes::GetNotesTime(i) && !Notes::IsCreateNotes(i)) {
			Create();
			Notes::Create(i);
		}
	}

	for (CModel* object : m_pModel) {

		object->Update();
	}

}

void NotesObject::Draw()
{
	for (CModel* object : m_pModel) {
		object->Draw();
	}

}

void NotesObject::Create()
{
	CModel* model = new CModel;
	model->Load("asset/miku_01.obj");
	m_pModel.push_back(model);
}
