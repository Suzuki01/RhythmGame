#include "score.h"

int Score::score;
int Score::digit;
CPolygon* Score::m_pPolygon[DIGIT_MAX];
CPolygon* Score::m_pComboPoly[4];
CPolygon* Score::m_pMaxComboPoly[4];
CPolygon* Score::m_pPerfectPoly[4];
CPolygon* Score::m_pAttackPoly[4];
CPolygon* Score::m_pMissPoly[4];
CModel* Score::m_pPercentage;
Classification Score::items;

char* numberImage[] = {
	{"asset/number/0.png"},
	{"asset/number/1.png"},
	{"asset/number/2.png"},
	{"asset/number/3.png"},
	{"asset/number/4.png"},
	{"asset/number/5.png"},
	{"asset/number/6.png"},
	{"asset/number/7.png"},
	{"asset/number/8.png"},
	{"asset/number/9.png"},
};

void Score::Init(int digit)
{
	items = { 0 };
	score = 0;
	for (int i = 0; i < DIGIT_MAX; i++) {
		m_pPolygon[i] = new CPolygon;
		m_pPolygon[i]->Init(numberImage[0], 0, 0, 50, 50);
		m_pPolygon[i]->m_Transform.Position = { 620.0f - i * 50.0f,155.0f, 0.0f };
		m_pPolygon[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}
	for (int i = 0; i < 4; i++) {
		m_pPerfectPoly[i] = new CPolygon;
		m_pPerfectPoly[i]->Init(numberImage[0], 0, 0, 30, 30);
		m_pPerfectPoly[i]->m_Transform.Position = { 380.0f - i * 30.0f, 210.0f, 0.0f };
		m_pPerfectPoly[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}	

	for (int i = 0; i < 4; i++) {
		m_pAttackPoly[i] = new CPolygon;
		m_pAttackPoly[i]->Init(numberImage[0], 0, 0, 30, 30);
		m_pAttackPoly[i]->m_Transform.Position = { 380.0f - i * 30.0f, 265.0f, 0.0f };
		m_pAttackPoly[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}	
	for (int i = 0; i < 4; i++) {
		m_pMissPoly[i] = new CPolygon;
		m_pMissPoly[i]->Init(numberImage[0], 0, 0, 30, 30);
		m_pMissPoly[i]->m_Transform.Position = { 380.0f - i * 30.0f, 315.0f, 0.0f };
		m_pMissPoly[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}

	for (int i = 0; i < 4; i++) {
		m_pMaxComboPoly[i] = new CPolygon;
		m_pMaxComboPoly[i]->Init(numberImage[0], 0, 0, 30, 30);
		m_pMaxComboPoly[i]->m_Transform.Position = { 380.0f - i * 30.0f, 365.0f, 0.0f };
		m_pMaxComboPoly[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}

	for (int i = 0; i < 4; i++) {
		m_pComboPoly[i] = new CPolygon;
		m_pComboPoly[i]->Init(numberImage[0], 0, 0, 30, 30);
		m_pComboPoly[i]->m_Transform.Position = { 380.0f - i * 30.0f, 375.0f, 0.0f };
		m_pComboPoly[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}

	m_pPercentage = new CModel;
	m_pPercentage->Load("asset/miku_01.obj");

}

void Score::UnInit()
{
	for (int i = 0; i < DIGIT_MAX; i++) {
		m_pPolygon[i]->UnInit();
		delete m_pPolygon[i];
	}

	m_pPercentage->UnInit();
}

void Score::Update()
{

}

void Score::Draw()
{
	int sce = items.combo;
	for (int i = 0; i < 4; i++) {
		if (i > 0 && sce == 0)
			break;
		m_pComboPoly[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}
}

void Score::ResultDraw() {
	int sce = score;
	for (int i = 0; i < DIGIT_MAX; i++) {
		m_pPolygon[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}
	sce = items.maxCombo;
	for (int i = 0; i < 4; i++) {
		if (i > 0 && sce == 0)
			break;
		m_pMaxComboPoly[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}
	sce = items.perfect;
	for (int i = 0; i < 4; i++) {
		if (i > 0 && sce == 0)
			break;
		m_pPerfectPoly[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}
	sce = items.attack;
	for (int i = 0; i < 4; i++) {
		if (i > 0 && sce == 0)
			break;
		m_pAttackPoly[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}
	sce = items.miss;
	for (int i = 0; i < 4; i++) {
		if (i > 0 && sce == 0)
			break;
		m_pMissPoly[i]->Draw(numberImage[sce % 10]);
		sce *= 0.1f;
	}

}

int Score::GetScore() {
	return score;
}

void Score::AddScore(int judge) {
	switch (judge)
	{
	//パーフェクト
	case 1:
		score += 100;
		items.perfect++;
		items.combo++;
		if (items.combo >= items.maxCombo)
			items.maxCombo = items.combo;
		break;
	//アタック
	case 2:
		score += 1;
		items.attack++;
		items.combo++;
		if (items.combo >= items.maxCombo)
			items.maxCombo = items.combo;
		break;
	case 3:
		items.miss++;
		items.combo = 0;
	default:
		break;
	}
}

void Score::SetPosition(XMFLOAT3 position) {
	for (int i = 0; i < DIGIT_MAX; i++) {
		m_pPolygon[i]->m_Transform.Position = { position.x - i * 50.0f, position.y, 0.0f };
		m_pPolygon[i]->m_Transform.Scale = { 1.0f,1.0f,1.0f };
	}
}

void Score::SongPositionDraw()
{
	float per = 0;
		if(Sound::GetSamplingNumber() != 0)
			per = (float)Sound::GetSamplingNumber() / Sound::GetSongSize();
	m_pPercentage->Position = { -4 + (20 * per),0,0 };
	XMMATRIX world;
	world = XMMatrixTranslation(m_pPercentage->Position.x, m_pPercentage->Position.y, m_pPercentage->Position.z);
	CRenderer::SetWorldMatrix(&world);

	m_pPercentage->Draw();
}

