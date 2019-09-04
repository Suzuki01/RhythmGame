#include "thumbnail.h"

CPolygon* Thumbnail::m_pPolygon;

void Thumbnail::Init(char* fileName)
{
	m_pPolygon = new CPolygon;
	m_pPolygon->Init(fileName,0,0,200,200);
}

void Thumbnail::UnInit()
{
	m_pPolygon->UnInit();
	delete m_pPolygon;
}

void Thumbnail::Draw()
{
	m_pPolygon->Draw();
}

void Thumbnail::SetPosition(XMFLOAT3 position) {
	m_pPolygon->m_Transform.Position = position;
}