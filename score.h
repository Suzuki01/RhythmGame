#ifndef SCORE_H_
#define SCORE_H_

#include "main.h"
#include "manager.h"
#include "input.h"
#include "polygon.h"
#include "sound.h"

#define DIGIT_MAX (7)

typedef struct{
	int perfect;
	int attack;
	int miss;
	int maxCombo;
	int combo;
}Classification;

class Score : public GameObject{
private:
	static int score;
	static CPolygon* m_pPolygon[DIGIT_MAX];
	static CPolygon* m_pComboPoly[];
	static CPolygon* m_pMaxComboPoly[];
	static CPolygon* m_pPerfectPoly[];
	static CPolygon* m_pAttackPoly[];
	static CPolygon* m_pMissPoly[];
	static CModel* m_pPercentage;
	static int digit;
	static Classification items;
public:
	static void Init(int digit);
	static void UnInit();
	static void Update();
	static void ResultDraw();
	static void Draw();
	static int GetScore();
	static void AddScore(int judge);
	static void SetPosition(XMFLOAT3 position);
	static void SongPositionDraw();
};

#endif // !SCORE_H_
