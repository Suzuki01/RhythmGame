#ifndef MODEL_ANIMATION_H_
#define MODEL_ANIMATION_H_

#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "texture_manager.h"

struct MESH {
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	unsigned int IndexNum;
	CTexture* texture;
};


class ModelAnimation {
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	CTexture* m_Texture = NULL;
	MESH* m_Mesh;
	MESH** mesh;
	unsigned int m_MeshNum;
	const aiScene* m_Scene;
	unsigned int m_IndexNum;
public:
	void Draw(XMMATRIX &Matrix);
	void DrawMesh(aiNode* Node, XMMATRIX &Matrix);
	void Load(const char* FileName);
	void Unload();
};

#endif