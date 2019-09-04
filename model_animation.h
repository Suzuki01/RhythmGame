#ifndef MODEL_ANIMATION_H_
#define MODEL_ANIMATION_H_

#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "texture_manager.h"

class ModelAnimation {
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	CTexture* m_Texture = NULL;
	unsigned int m_IndexNum;
public:
	void Draw();
	void Load(const char* FileName);
	void Unload();
};

#endif