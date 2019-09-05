#include "model_animation.h"


void ModelAnimation::Load(const char* FileName)
{
	const aiScene* scene = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality);
	aiMesh* mesh = scene->mMeshes[0];
	VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

	for (int i = 0; i < mesh->mNumVertices; i++) {
		vertex[i].Position = XMFLOAT3{ mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z };
		vertex[i].Normal = XMFLOAT3{mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z };
		vertex[i].Diffuse = XMFLOAT4{1.0f,1.0f,1.0f,1.0f};
//		vertex[i].TexCoord = XMFLOAT2{ mesh->mTextureCoords[i]->x,mesh->mTextureCoords[i]->y };
		vertex[i].TexCoord = XMFLOAT2{0,0};
	}

	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT; //使用用途
		bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices; 
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //どのようにこのバッファを使うか　頂点だからVERTEX_BUFFER
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}
	delete[] vertex;


	unsigned short* index;
	this->m_IndexNum = mesh->mNumFaces * 3;
	index = new unsigned short[this->m_IndexNum]; //assimpは三角形の面ごとにしまってある
	for (int i = 0; i < mesh->mNumFaces; i++) {
		index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
		index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
		index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
	}

	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * this->m_IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &this->m_IndexBuffer);
	}
	delete[] index;
	aiReleaseImport(scene);

	m_Texture = new CTexture;
	m_Texture = TextureManager::Load("asset/jo.png");
}

void ModelAnimation::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
}

void ModelAnimation::Draw()
{
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	CRenderer::DrawIndexed(m_IndexNum,0,0);	
}

