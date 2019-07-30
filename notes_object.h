#ifndef NOTES_OBJECT_H_
#define NOTES_OBJECT_H_



class NotesObject : public GameObject {
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Create();
private:
	std::list<CModel*> m_pModel;
};
int Judgement(float currentBeats, float judgeBeats);
#endif // !NOTES_OBJECT_H_
