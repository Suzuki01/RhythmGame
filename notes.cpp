#include "notes.h"

#define RANE_MAX	(2)	
#define NOTE_MAX	(1000)

int Notes::maxNotes;
int Notes::m_createLeadNoteNumber[RANE_MAX];
int Notes::m_playingNoteNumber;
Note Notes::m_Notes1;
std::vector <Note*> g_Notes1;
std::vector <Note*> g_Notes2;
bool Notes::isEnd;
int Notes::endCount;
JudgmentImage Notes::judgementImage[JUDGMENT_IMAGE_MAX][JUDGMENT_IMAGE_MAX];

float cntTime[500] = {0};
int cntMaxCombo = 0;

char* musicScore[] = {
	{"asset/music_score/kurumiwari_ningyou.csv"},
	{"asset/music_score/kurumiwari_ningyou.csv"},
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
		Note* note = new Note;
		for (int i = 0; i < strvec.size(); i += strvec.size()) {
			note->time = stof(strvec.at(i));
			note->rane = stoi(strvec.at(i + 1));
			note->isCreate = true;
			note->m_pModel = new CModel;
			note->m_pModel->Load("asset/miku_01.obj");
			//ノーツの初期位置の計算式　任意のノーツスピード×0.2×ノーツを叩くビート数
			//model->Position = { 0.0f, 0.0f,0.2f * g_Notes[i].time};
			switch (note->rane)
			{
			case 1:
				note->m_pModel->Position = { -5.0f, 0.0f,4.0f * note->time };
				g_Notes1.push_back(note);
				break;
			case 2:
				note->m_pModel->Position = { 5.0f, 0.0f,4.0f * note->time };
				g_Notes2.push_back(note);
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
	/*for (int i = 0; i < g_Notes1.size(); i++) {
		CModel* model = new CModel;
		model->Load("asset/miku_01.obj");
		//ノーツの初期位置の計算式　任意のノーツスピード×0.2×ノーツを叩くビート数
		//model->Position = { 0.0f, 0.0f,0.2f * g_Notes[i].time};
		model->Position = { -1.0f, 0.0f,4.0f * g_Notes1[i].time };
		g_Notes1[i].isCreate = true;
		m_pModel.push_back(model);
	}

	for (int i = 0; i < g_Notes2.size(); i++) {
		CModel* model = new CModel;
		model->Load("asset/miku_01.obj");
		//ノーツの初期位置の計算式　任意のノーツスピード×0.2×ノーツを叩くビート数
		//model->Position = { 0.0f, 0.0f,0.2f * g_Notes[i].time};
		model->Position = { 1.0f, 0.0f,4.0f * g_Notes1[i].time };
		g_Notes2[i].isCreate = true;
		m_pModel.push_back(model);
	}*/
	isEnd = false;
	endCount = 0;
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		for (int j = 0; j < JUDGMENT_IMAGE_MAX; j++ ) {
			judgementImage[i][j].billBoard = new BillBoard;
			judgementImage[i][j].billBoard->Init(classImage[i]);
			judgementImage[i][j].billBoard->m_Transform.Scale = { 5.0f,2.0f,1.0f };
			judgementImage[i][j].justiceImageCount = 0;
			judgementImage[i][j].isDisplay = false;
		}
	}
}

void Notes::UnInit() {
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		for (int j = 0; j < JUDGMENT_IMAGE_MAX; j++) {
			judgementImage[i][j].billBoard->UnInit();
			delete judgementImage[i][j].billBoard;
			judgementImage[i][j].justiceImageCount = 0;
			judgementImage[i][j].isDisplay = false;
		}
	}

	/*
	for (int i = 0; i < g_Notes1.size(); i++) {
		g_Notes1[i]->m_pModel->UnInit();
		delete g_Notes1[i]->m_pModel;
	//	delete g_Notes1[i];
	}

	for (int i = 0; i < g_Notes2.size(); i++) {
		g_Notes2[i]->m_pModel->UnInit();
		delete g_Notes2[i]->m_pModel;
	//	delete g_Notes2[i];
	}
	*/
	g_Notes1.clear();
	g_Notes2.clear();
}

void Notes::Draw() {
	
	XMMATRIX world;
	//int i = 0;
	/*
	for (CModel* object : m_pModel) {
		if (g_Notes1[i].rane == NULL)
			break;
		else if (g_Notes1[i].isCreate) {
			
			world = XMMatrixTranslation(object->Position.x, object->Position.y, object->Position.z);
			CRenderer::SetWorldMatrix(&world);
			object->Draw();
		}
		i++;
	}*/

	for (int i = 0; i < g_Notes1.size(); i++) {
		if (g_Notes1[i]->rane == NULL)
			break;
		else if (g_Notes1[i]->isCreate) {
			world = XMMatrixTranslation(g_Notes1[i]->m_pModel->Position.x, g_Notes1[i]->m_pModel->Position.y, g_Notes1[i]->m_pModel->Position.z);
			CRenderer::SetWorldMatrix(&world);
			g_Notes1[i]->m_pModel->Draw();
		}
	}	
	for (int i = 0; i < g_Notes2.size(); i++) {
		if (g_Notes2[i]->rane == NULL)
			break;
		else if (g_Notes2[i]->isCreate) {
			world = XMMatrixTranslation(g_Notes2[i]->m_pModel->Position.x, g_Notes2[i]->m_pModel->Position.y, g_Notes2[i]->m_pModel->Position.z);
			CRenderer::SetWorldMatrix(&world);
			g_Notes2[i]->m_pModel->Draw();
		}
	}

	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		for (int j = 0; j < JUDGMENT_IMAGE_MAX; j++) {
			if (judgementImage[i][j].isDisplay) {
				judgementImage[i][j].billBoard->Draw();

				if (judgementImage[i][j].justiceImageCount > 60) {
					ResetJusticeImage(i, j);
				}
				judgementImage[i][j].justiceImageCount++;
			}
		}
	}
}

void Notes::Update() {

	if(Input::Keyboard_IsTrigger('A')){
		if (g_Notes1.size() != m_createLeadNoteNumber[0]) {
			Judgement(1);
		}
	}
	if(Input::Keyboard_IsTrigger('D')){
		if (g_Notes2.size() != m_createLeadNoteNumber[1]) {
			Judgement(2);
		}
	}
	if (Input::Keyboard_IsTrigger('W')) {
		cntTime[cntMaxCombo] = Sound::GetCurrentBeats();
		cntMaxCombo++;
	}
	if (Input::Keyboard_IsTrigger('Y')) {
		DataSave();
	}
	for (int i = 0; i < g_Notes1.size(); i++) {
		if (g_Notes1[i]->rane == NULL)
			break;
		g_Notes1[i]->m_pModel->Position.z = 4.0f * g_Notes1[i]->time - 4.0f * Sound::GetCurrentBeats();
		g_Notes1[i]->m_pModel->Update();
		if (g_Notes1[i]->m_pModel->Position.z <= -0.6) {
			if (g_Notes1[i]->isCreate) {
				Miss(1);
				SetJusticeImage(2,g_Notes1[i]->rane);
				Score::AddScore(3);
			}
		}
	}
	for (int i = 0; i < g_Notes2.size(); i++) {
		if (g_Notes2[i]->rane == NULL)
			break;
		g_Notes2[i]->m_pModel->Position.z = 4.0f * g_Notes2[i]->time - 4.0f * Sound::GetCurrentBeats();
		g_Notes2[i]->m_pModel->Update();
		if (g_Notes2[i]->m_pModel->Position.z <= -0.6) {
			if (g_Notes2[i]->isCreate) {
				Miss(2);
				SetJusticeImage(2, g_Notes2[i]->rane);
				Score::AddScore(3);
			}
		}
	}
	if (m_createLeadNoteNumber[0] + m_createLeadNoteNumber[1] == maxNotes) {
		isEnd = true;
	}
}

void Notes::Update(float currentBeats) {

	for (int i = 0; i < g_Notes1.size(); i++) {
		if (g_Notes1[i]->rane == NULL)
			break;
		g_Notes1[i]->m_pModel->Position.z = 4.0f * g_Notes1[i]->time - 4.0f * currentBeats;
		g_Notes1[i]->m_pModel->Update();
		if (g_Notes1[i]->m_pModel->Position.z <= -0.6) {
			if (g_Notes1[i]->isCreate) {
			//	Miss(1);
			//	SetJusticeImage(2, g_Notes1[i]->rane);
				Score::AddScore(3);
			}
		}
	}
	for (int i = 0; i < g_Notes2.size(); i++) {
		if (g_Notes2[i]->rane == NULL)
			break;
		g_Notes2[i]->m_pModel->Position.z = 4.0f * g_Notes2[i]->time - 4.0f * currentBeats;
		g_Notes2[i]->m_pModel->Update();
		if (g_Notes2[i]->m_pModel->Position.z <= -0.6) {
			if (g_Notes2[i]->isCreate) {
			//	Miss(2);
			//	SetJusticeImage(2, g_Notes2[i]->rane);
				Score::AddScore(3);
			}
		}
	}
	if (m_createLeadNoteNumber[0] + m_createLeadNoteNumber[1] == maxNotes) {
		isEnd = true;
	}
}


int Notes::GetMaxNotes()
{
	return maxNotes;
}

float Notes::GetNotesTime(int index) {
	return g_Notes1[index]->time;
}

bool Notes::IsCreateNotes(int index)
{
	return false;
}

void Notes::Create(int index) {
	g_Notes1[m_createLeadNoteNumber[index]]->isCreate = true;
//	m_Notes[index].isCreate = true;
//	m_createLeadNoteNumber++;
}

void Notes::Destory() {

}

float Notes::GetCurrentNotesTime(int rane) {
	switch (rane)
	{
	case 1:
		return g_Notes1[m_createLeadNoteNumber[rane - 1]]->time;
	case 2:
		return g_Notes2[m_createLeadNoteNumber[rane - 1]]->time;
	default:
		return 10000.0f;
	}
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

int Notes::Judgement(int rane) {
	float judgeTime = GetCurrentNotesTime(rane) - Sound::GetCurrentBeats();

	if (judgeTime <= 0.2 && judgeTime >= -0.2f) {
		Perfect(rane);
		Score::AddScore(1);
		SetJusticeImage(0,rane);
		return 1;
	}
	else if (judgeTime <= 0.4 && judgeTime >= -0.4) {
		Attack(rane);
		Score::AddScore(2);
		SetJusticeImage(1,rane);
		return 2;
	}
	else {
		return 0;
	}
}

void Notes::Delete(int rane) {
	switch (rane)
	{
	case 1:
		g_Notes1[m_createLeadNoteNumber[rane - 1]]->isCreate = false;
		m_createLeadNoteNumber[rane - 1]++;
		break;
	case 2:
		g_Notes2[m_createLeadNoteNumber[rane - 1]]->isCreate = false;
		m_createLeadNoteNumber[rane - 1]++;
		break;
	default:
		break;
	}
}

void Notes::Perfect(int rane)
{
	Delete(rane);
}

void Notes::Attack(int rane)
{
	Delete(rane);
}

void Notes::Miss(int rane)
{
	Delete(rane);
}

void Notes::SetJusticeImage(int index,int rane) {
	for (int i = 0; i < JUDGMENT_IMAGE_MAX; i++) {
		if (!judgementImage[index][i].isDisplay) {
			judgementImage[index][i].billBoard->m_Transform.Position = { -5.0f + (rane - 1) * 10, 0.0f,0.0f };
			judgementImage[index][i].isDisplay = true;
			break;
		}
	}
}

void Notes::ResetJusticeImage(int index,int cnt) {
	judgementImage[index][cnt].isDisplay = false;
	judgementImage[index][cnt].justiceImageCount = 0;
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
	// ファイルのオープン
//	fp = fopen("asset/music_score/note.csv", "w");
//	fprintf(fp, "%f\n", 100);
	// 各データをカンマ区切りで出力する
/*	for (int i = 0; i < cntMaxCombo; i++) {
		fprintf(fp, "%f\n",cntTime[i]);
	}*/
	//fclose(fp);
}