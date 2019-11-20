#ifndef BALL_H_
#define BALL_H_


class Ball : public GameObject {
private:
	XMVECTOR m_Quaternion;
	ModelAnimation* m_pModelAnimation;
	XMMATRIX m_Matrix;
public:
	void Init(char* fileName);
	void Draw();
	void Update();
};

#endif // !BALL_H_

