#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

class GameScene : public Scene {
private:
	typedef enum PHASE_INDEX {
		PHASE_INDEX_READY,
		PHASE_INDEX_GO,
		PHASE_INDEX_START,
		PHASE_INDEX_MAX,
	};
	char* m_pFileName;
	PHASE_INDEX m_Phase;
	CPolygon* ready;
	CPolygon* go;
	int count;
public:
//	GameScene(char* fileName) : m_pFileName(fileName) {};
	void Init();
	void UnInit();
	void Update();
	void Draw();
	CAudioClip* m_pBGM;
	//Draw‚Í‹@”\’Ç‰Á‚ª¡‰ñ‚È‚¢‚½‚ßì¬‚µ‚Ä‚¢‚È‚¢
	//Œp³Œ³‚ÌDraw‚ªŒÄ‚Î‚ê‚é
};



#endif // !GAME_SCENE_H_
