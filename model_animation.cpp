#include "model_animation.h"


void ModelAnimation::Load(const char* FileName)
{
	m_Scene = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality);
	m_MeshNum = m_Scene->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];

	for (int i = 0; i < m_MeshNum; i++) {
		aiMesh* mesh = m_Scene->mMeshes[i];
		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];
		aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];
		aiColor4D specularColor;
		aiColor4D diffuseColor;
		aiColor4D ambientColor;
		float shininess;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
		aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

		for (int i = 0; i < mesh->mNumVertices; i++) {
			vertex[i].Position = XMFLOAT3{ mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z };
			vertex[i].Normal = XMFLOAT3{ mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z };
			vertex[i].Diffuse = XMFLOAT4{ diffuseColor.r,diffuseColor.g,diffuseColor.b,diffuseColor.a };
			//		vertex[i].TexCoord = XMFLOAT2{ mesh->mTextureCoords[i]->x,mesh->mTextureCoords[i]->y };
			vertex[i].TexCoord = XMFLOAT2{ 0,0 };
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

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[i].VertexBuffer);
		}
		delete[] vertex;


		unsigned short* index;
		m_Mesh[i].IndexNum = mesh->mNumFaces * 3;
		index = new unsigned short[m_Mesh[i].IndexNum]; //assimpは三角形の面ごとにしまってある
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
			bd.ByteWidth = sizeof(unsigned short) * m_Mesh[i].IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[i].IndexBuffer);
		}
		delete[] index;
	}
	m_Texture = new CTexture;
	m_Texture = TextureManager::Load("asset/jo.png");
}

void ModelAnimation::Unload()
{
//	m_VertexBuffer->Release();
//	m_IndexBuffer->Release();
	for (int i = 0; i < m_MeshNum; i++) {
		m_Mesh[i].VertexBuffer->Release();
		m_Mesh[i].IndexBuffer->Release();
	}
	aiReleaseImport(m_Scene);
}

void ModelAnimation::Draw(XMMATRIX &Matrix)
{
	DrawMesh(m_Scene->mRootNode,Matrix);//親ノードから呼ぶ
/*	for (int i = 0; i < m_MeshNum; i++) {
		CRenderer::SetVertexBuffers(m_Mesh[i].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[i].IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[i].IndexNum, 0, 0);
	}*/
}

void ModelAnimation::DrawMesh(aiNode* Node,XMMATRIX &Matrix)
{
	
	aiMatrix4x4 matrix = Node->mTransformation; //相対的な位置　（親から見た位置）
	aiTransposeMatrix4(&matrix); //転置行列作成 assimpとdirectxの行列が逆のため
	XMMATRIX world = XMLoadFloat4x4((XMFLOAT4X4*)& matrix);
	world *= Matrix; //親のマトリクス　directxは後ろのマトリクス（階層）からかける
	CRenderer::SetWorldMatrix(&world);
	//ノードとメッシュの関係
	//形状を表しているのがメッシュ,形がない入れ物がノード、ノードが階層構造を持っているが形状はない。ノードの中にっメッシュが入っていて親子関係を表している
	//
	for (int n = 0; n < Node->mNumMeshes; n++) {
		unsigned int m = Node->mMeshes[n]; //メッシュの番号がわかる

		//メッシュ描画
		CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
	//	CRenderer::SetTexture(m_Texture);
		CRenderer::SetVertexBuffers(m_Mesh[m].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[m].IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[m].IndexNum, 0, 0);
	}
	for (int i = 0; i < Node->mNumChildren; i++) {
		DrawMesh(Node->mChildren[i], world); //再帰呼び出し
	}
}

