#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "texture_manager.h"
#include "model_animation.h"


void ModelAnimation::Load(const char* FileName)
{
	m_Scene[0] = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate);
	m_Scene[1] = aiImportFile("asset/model/human_jump.fbx", aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate);
	m_Scene[2] = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate);
	m_MeshNum = m_Scene[0]->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];
	for (int i = 0; i < m_MeshNum; i++) {
		aiMesh* mesh = m_Scene[0]->mMeshes[i];
		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];
		aiMaterial* material = m_Scene[0]->mMaterials[mesh->mMaterialIndex];
		aiColor4D specularColor;
		aiColor4D diffuseColor;
		aiColor4D ambientColor;
		float shininess;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
		aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);

		const std::string modelPath = FileName;
		size_t pos = modelPath.find_last_of("\\/"); //テクスチャの場所を取得
		std::string basePath = modelPath.substr(0, pos + 1);

		for (unsigned int m = 0; m < m_Scene[0]->mNumMaterials; m++) {
			aiString path;
			if (m_Scene[0]->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				std::string fileloc = basePath + path.data;
				
				m_Mesh[i].texture = TextureManager::Load(fileloc);
				if (m_Mesh[i].texture != nullptr)
					continue;

				if (m_Scene[0]->mTextures[m]->mHeight == 0) {
					//int id = atoi(path.data);
					m_Mesh[i].texture = TextureManager::MemoryLoad(fileloc, m_Scene[0]->mTextures[m]);
				}
			}
			else {
				m_Mesh[i].texture = TextureManager::Load("asset/nothing.png");
			}
		}

		//m_Scene->mMaterials[mesh->mMaterialIndex]->GetTexture();
		for (int i = 0; i < mesh->mNumVertices; i++) {
			vertex[i].Position = XMFLOAT3{ mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z };
			vertex[i].Normal = XMFLOAT3{ mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z };
			vertex[i].Diffuse = XMFLOAT4{ diffuseColor.r,diffuseColor.g,diffuseColor.b,diffuseColor.a };
			if (mesh->HasTextureCoords(0)) {
				vertex[i].TexCoord = XMFLOAT2{ mesh->mTextureCoords[0][i].x,-mesh->mTextureCoords[0][i].y };
			}
			else {
				vertex[i].TexCoord = XMFLOAT2{ 0,0 };
			}
			//vertex[i].TexCoord = XMFLOAT2{ 0,0 };
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
}

void ModelAnimation::Unload()
{
//	m_VertexBuffer->Release();
//	m_IndexBuffer->Release();
	for (int i = 0; i < m_MeshNum; i++) {
		m_Mesh[i].VertexBuffer->Release();
		m_Mesh[i].IndexBuffer->Release();
	}
	for (int i = 0; i < 3; i++) {
		aiReleaseImport(m_Scene[i]);
	}
}

void ModelAnimation::SetAnimation(int id)
{
	m_AnimationID = id;
}

int ModelAnimation::GetAnimationID()
{
	return m_AnimationID;
}



void ModelAnimation::Update(int AnimationID,int AnimationID2 ,float Blend ,int Frame)
{
	if (m_Scene[AnimationID]->mAnimations == nullptr)
		return;
	aiAnimation* animation = m_Scene[AnimationID]->mAnimations[0];
	aiAnimation* animation2 = m_Scene[AnimationID2]->mAnimations[0];
	for (int c = 0; c < animation->mNumChannels; c++) {
		aiNodeAnim* nodeAnim = animation->mChannels[c]; //channnels //1パーツ分のアニメーションのデータが配列ごとに入っている
		aiNodeAnim* nodeAnim2 = animation->mChannels[c]; //channnels //1パーツ分のアニメーションのデータが配列ごとに入っている
		int f = Frame % nodeAnim->mNumRotationKeys;
		int f2 = Frame % nodeAnim->mNumRotationKeys;
		aiQuaternion blendQuaternion;
		aiQuaternion::Interpolate(blendQuaternion,nodeAnim->mRotationKeys[f].mValue, nodeAnim2->mRotationKeys[f2].mValue,Blend);
//		m_NodeRotation[nodeAnim->mNodeName.C_Str()] = nodeAnim->mRotationKeys[f].mValue;
		m_NodeRotation[nodeAnim->mNodeName.C_Str()] = blendQuaternion;
		f = Frame % nodeAnim->mNumPositionKeys;
		f2 = Frame % nodeAnim2->mNumPositionKeys;
		m_NodePosition[nodeAnim->mNodeName.C_Str()] = { nodeAnim->mPositionKeys[f].mValue.x + (nodeAnim2->mPositionKeys[f2].mValue.x - nodeAnim->mPositionKeys[f].mValue.x) * (Blend - f),nodeAnim->mPositionKeys[f].mValue.y + (nodeAnim2->mPositionKeys[f2].mValue.y - nodeAnim->mPositionKeys[f].mValue.y) * (Blend - f),nodeAnim->mPositionKeys[f].mValue.z + (nodeAnim2->mPositionKeys[f2].mValue.z - nodeAnim->mPositionKeys[f].mValue.z) * (Blend - f) };
	}
}

void ModelAnimation::Draw(XMMATRIX &Matrix)
{
	
	if (m_Scene[0]->mAnimations == nullptr) {
		DrawMesh(m_Scene[0]->mRootNode, Matrix);//親ノードから呼ぶ
	}
	else {
		DrawMeshAnimation(m_Scene[0]->mRootNode, Matrix);
	}
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
	//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
		if(m_Mesh[m].texture != nullptr)
			CRenderer::SetTexture(m_Mesh[m].texture);
		CRenderer::SetVertexBuffers(m_Mesh[m].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[m].IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[m].IndexNum, 0, 0);
	}
	for (int i = 0; i < Node->mNumChildren; i++) {
		DrawMesh(Node->mChildren[i], world); //再帰呼び出し
	}
}

void ModelAnimation::DrawMeshAnimation(aiNode* Node, XMMATRIX& Matrix)
{
	aiQuaternion aiQuat = m_NodeRotation[Node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w)); //directxで使える形にQuartanionに変換
	XMMATRIX world = XMMatrixRotationQuaternion(quat);
	aiVector3D aiPos = m_NodePosition[Node->mName.C_Str()];
	world *= XMMatrixTranslation(aiPos.x, aiPos.y, aiPos.z);
	world *= Matrix; //親のマトリクス　directxは後ろのマトリクス（階層）からかける
	CRenderer::SetWorldMatrix(&world);
	//ノードとメッシュの関係
	//形状を表しているのがメッシュ,形がない入れ物がノード、ノードが階層構造を持っているが形状はない。ノードの中にっメッシュが入っていて親子関係を表している
	//
	for (int n = 0; n < Node->mNumMeshes; n++) {
		unsigned int m = Node->mMeshes[n]; //メッシュの番号がわかる

		//メッシュ描画
	//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
		if (m_Mesh[m].texture != nullptr)
			CRenderer::SetTexture(m_Mesh[m].texture);
		CRenderer::SetVertexBuffers(m_Mesh[m].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[m].IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[m].IndexNum, 0, 0);
	}
	for (int i = 0; i < Node->mNumChildren; i++) {
		DrawMeshAnimation(Node->mChildren[i], world); //再帰呼び出し
	}
}


