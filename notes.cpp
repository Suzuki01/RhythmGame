#include "notes.h"

#define RANE_MAX	(4)	
#define NOTE_MAX	(1000)

int Notes::ID;
int Notes::maxNotes;
int Notes::m_createLeadNoteNumber[RANE_MAX];
int Notes::m_playingNoteNumber;
bool Notes::isEnd;
int Notes::endCount;
JudgmentImage Notes::judgementImage[JUDGMENT_IMAGE_MAX];

std::vector<Note*> Notes::m_Notes;
int Notes::m_CurrentNoteNum;
Note* Notes::m_CurrentNoteData;
bool Notes::isEditorMode;

float cntTime[500] = { 0 };
int cntMaxCombo = 0;


char* musicScore[] = {
	{"asset/music_score/kurumiwari_ningyou.csv"},
	{"asset/music_score/tengokuto_jigoku.csv"},
	{"asset/music_score/note.csv"},
};

char* classImage[] = {
	{"asset/perfect.png"},
	{"asset/attack.png"},
	{"asset/miss.png"},
};

XMFLOAT3 classImageScale[] = {
	{ 3.6f,2.7f,1.0f },
	{ 3.6f,2.7f,1.0f },
};

std::vector<std::string> Notes::split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector <std::string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

void Notes::Load(int id) {
	ID = id;
	std::ifstream ifs(musicScore[id]);
	std::string line;
	maxNotes = 0;
	for (int j = 0; j < RANE_MAX; j++) {
		m_createLeadNoteNumber[j] = 0;
	}
	std::vector<std::string> strvec;

	int cnt = 0;
 	while (std::getline(ifs, line)) {
		strvec = split(line, ',');
		for (int i = 0; i < strvec.size(); i += strvec.size()) {
			Note* note = new Note(stof(strvec.at(i)), stof(strvec.at(i + 1)), true);
			note->m_pModel = new CModel;
			note->m_pModel->Load("asset/miku_01.obj");
			//ノーツの初期位置の計算式　任意のノーツスピード×0.2×ノーツを叩くビート数
			//model->Position = { 0.0f, 0.0f,0.2f * g_Notes[i].time};
			switch (note->rane)
			{
			case 1:
				note->m_pModel->Position = { -6.0f, 0.0f,8.0f * note->time };
				m_Notes.push_back(note);
				break;
			case 2:
				note->m_pModel->Position = { -2.0f, 0.0f,8.0f * note->time };
				m_Notes.push_back(note);
				break;
			case 3:
				note->m_pModel->Position = { 2.0f, 0.0f,8.0f * note->time };
				m_Notes.push_back(note);
				break;
			case 4:
				note->m_pModel->Position = { 6.0f, 0.0f,8.0f * note->time };
				m_Notes.push_back(note);
				break;
			default:
				break;
			}
			maxNotes++;
		}
	}
	ifs.close();
}

void Notes::Init() {

	isEnd = false;
	endCount = 0;
	m_CurrentNoteNum = 0;
	if(m_Notes.size() == 0){
		m_CurrentNoteData = 0;
	}
	else {
		m_CurrentNoteData = *m_Notes.begin();
	}
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		judgementImage[i].billBoard = new BillBoard;
		judgementImage[i].billBoard->Init(classImage[0]);
		judgementImage[i].billBoard->m_Transform.Scale = { 5.0f,2.0f,1.0f };
		judgementImage[i].justiceImageCount = 0;
		judgementImage[i].isDisplay = false;
	}
}

void Notes::UnInit() {
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		judgementImage[i].billBoard->UnInit();
		delete judgementImage[i].billBoard;
		judgementImage[i].justiceImageCount = 0;
		judgementImage[i].isDisplay = false;
	}
	
	m_Notes.clear();
}

void Notes::Draw() {

	if (m_Notes.size() == 0)
		return;

	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		if (judgementImage[i].isDisplay) {
			judgementImage[i].billBoard->Draw();

			if (judgementImage[i].justiceImageCount > 60) {
				ResetJusticeImage(i);
			}
			judgementImage[i].justiceImageCount++;
		}
	}

	for (auto it = m_Notes.begin(); it != m_Notes.end(); ++it) {
		XMMATRIX world;
		if ((*it)->rane == NULL)
			break;
		else if ((*it)->isCreate) {
			world = XMMatrixTranslation((*it)->m_pModel->Position.x, (*it)->m_pModel->Position.y, (*it)->m_pModel->Position.z);
			CRenderer::SetWorldMatrix(&world);
			(*it)->m_pModel->Draw();
		}
	}

}

void Notes::Update() {

	//判定処理
	if (Input::Keyboard_IsTrigger('A')) {
		Judgement(1);
	}
	if (Input::Keyboard_IsTrigger('D')) {
		Judgement(2);
	}
	if (Input::Keyboard_IsTrigger('J')) {
		Judgement(3);
	}
	if (Input::Keyboard_IsTrigger('L')) {
		Judgement(4);
	}


	if (m_Notes.size() == 0)
		return;
	
	for (auto it = m_Notes.begin(); it != m_Notes.end(); ++it) {
		if ((*it)->rane == NULL)
			break;
		else if ((*it)->isCreate) {
			if (Sound::isPlay)
				(*it)->m_pModel->Position.z = 8.0f * (*it)->time - 8.0f * Sound::GetCurrentBeats();
			else {
				(*it)->m_pModel->Position.z = 8.0f * (*it)->time - 8.0f * Sound::GetEditorCurrenntBeats();
			}
		
			(*it)->m_pModel->Update();
			if ((*it)->m_pModel->Position.z <= -0.6f) {
				if ((*it)->isCreate) {
					Miss((*it)->rane);
				}
			}
		}
	}

	if (m_CurrentNoteNum == maxNotes - 1) {
			isEnd = true;
	}

}

int Notes::GetMaxNotes()
{
	return maxNotes;
}


bool Notes::IsCreateNotes(int index)
{
	return false;
}

void Notes::Create(int rane, float beatOffset) {
	Note* note = new Note(((beatOffset / 4.0f) + Sound::GetEditorCurrenntBeats()), rane, true);
	note->m_pModel = new CModel();
	note->m_pModel->Load("asset/miku_01.obj");
	note->m_pModel->Position = { -6.0f + 4.0f * (rane - 1),0.0f,0.0f };
	m_Notes.push_back(note);
}

void Notes::Destory() {

}

float Notes::GetCurrentNotesTime(int rane) {
	return m_CurrentNoteData->time;
}

float Notes::GetFirstNotesTime()
{
	return 0;
}

bool Notes::EndCheck()
{
	if (isEnd) {
		endCount++;
		if (endCount >= 300)
			return true;
	}
	return false;
}

//ノーツを押したタイミングを判定する機能
void Notes::Judgement(int rane) {
	//エディタモード時は判定しない
	if (isEditorMode || m_Notes.size() == 0)
		return;

	float judgeTime = GetCurrentNotesTime(rane) - Sound::GetCurrentBeats();
	if (rane != m_CurrentNoteData->rane || isEditorMode)
		return;

	if (judgeTime <= 0.2 && judgeTime >= -0.2f) {
		Perfect(rane);
		SetJusticeImage(0, rane);
		return;
	}
	else if (judgeTime <= 0.4 && judgeTime >= -0.4) {
		Attack(rane);
		SetJusticeImage(1, rane);
		return;
	}
	else {
		return;
	}
}

void Notes::Delete(int rane) {
	Next();
}

void Notes::Perfect(int rane)
{
	Score::AddScore(1);
	Next();
}

void Notes::Attack(int rane)
{
	Score::AddScore(2);
	Next();
}

void Notes::Miss(int rane)
{
	if (isEditorMode)
		return;
	Score::AddScore(3);
	Next();
}

void Notes::SetJusticeImage(int index, int rane) {
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		if (!judgementImage[i].isDisplay) {
			judgementImage[i].billBoard->SetTexture(classImage[index]);
			judgementImage[i].billBoard->m_Transform.Position = { -6.0f + (rane - 1) * 4, 0.0f,0.0f };
			judgementImage[i].isDisplay = true;
			break;
		}
	}
}

void Notes::ResetJusticeImage(int index) {
	judgementImage[index].isDisplay = false;
	judgementImage[index].justiceImageCount = 0;
}

void Notes::DataSave() {
	FILE* fp;
	if ((fp = fopen("asset/music_score/note.csv", "w")) != NULL) {
		for (int i = 0; i < cntMaxCombo; i++) {
			if (fprintf(fp, "%f,%d\n", cntTime[i]) < 0) {
				//書き込みエラー
				break;
			}
		}
		fclose(fp);
	}
	else {
		//ファイルオープンエラー
	}
}

bool Notes::Save() {
	std::sort(m_Notes.begin(), m_Notes.end(), [](Note*& note,Note*& note2)
	{
		return note->time < note2->time;
	});
	FILE* fp;
	if ((fp = fopen(musicScore[ID], "w")) != NULL) {
		for (auto it = m_Notes.begin(); it != m_Notes.end(); ++it) {
			if (fprintf(fp, "%f,%d\n", (*it)->time, (*it)->rane) < 0) {
				//書き込みエラー
				break;
			}
		}
		fclose(fp);
	}
	else {
		//ファイルオープンエラー
	}

	return true;
}

bool Notes::CheckNotes(XMFLOAT3 pos, float range, int rane) {
	int oldNum = m_Notes.size();
	m_Notes.erase(std::remove_if(m_Notes.begin(), m_Notes.end(), [&pos, &range, &rane](Note* n) { 
		return n->m_pModel->Position.z < pos.z + range && n->m_pModel->Position.z > pos.z - range && n->rane == rane;//キャプチャーの種類 「= … コピー」、「& … 参照コピー」
	}), m_Notes.end());
	int newNum = m_Notes.size();
	std::sort(m_Notes.begin(), m_Notes.end(), [](Note*& note, Note*& note2)
	{
		return note->time < note2->time;
	});

	if (oldNum > newNum) {
		return true;
	}
	return false;
}

//判定するノーツを次のノーツに変更
void Notes::Next() {
	m_CurrentNoteData->isCreate = false;
	m_CurrentNoteNum++;

	//list.endを越えないように
	if (maxNotes - 1 <= m_CurrentNoteNum)
		m_CurrentNoteNum = maxNotes - 1;
	auto data = std::next(m_Notes.begin(), m_CurrentNoteNum);
	m_CurrentNoteData = *data;
}

void Notes::DrawCurrentPosition() {

}