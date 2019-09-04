#ifndef THUMBNAIL_H_
#define THUMBNAIL_H_

#include "main.h"
#include "manager.h"
#include "input.h"
#include "polygon.h"


class Thumbnail {
public:
	static void Init(char* fileName);
	static void UnInit();
	static void Draw();
	static void SetPosition(XMFLOAT3 position);
private:
	static CPolygon* m_pPolygon;
};

#endif // !THUMBNAIL_H_
