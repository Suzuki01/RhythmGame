#pragma once

#include "main.h"
#include "renderer.h"
#include "texture.h"

static const char* TEXTURE_FILES[] = {
	"asset/jo.png",
	"asset/shiina.tga",
	"asset/field004.tga",
	"asset/number.tga"
};

enum {
	TEXTURE_JO,
	TEXTURE_SHINA,
	TEXTURE_FIELD,
	TEXTURE_NUMBER,
	TEXTURE_MAX,
};


class CTexture
{

public:
	void Unload();
	bool LoadTexture(const char* FileName);
	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_ShaderResourceView; }
	~CTexture();
private:
	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;

};