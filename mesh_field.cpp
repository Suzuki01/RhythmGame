#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game_object.h"
#include "texture.h"
#include "texture_manager.h"
#include "scene.h"
#include "input.h"
#include "mesh_field.h"



float fieldWidth, fieldHeight;
int gridMax;
static int vertexNum;//頂点数
static int indexNum; //インデックス数
CTexture* Texture;
float g_FieldHeight[5][5] = {
	{0.0f,0.0f,0.0f,-1.0f,0.0f},
	{3.0f,0.0f,2.0f,-2.0f,-1.0f},
	{5.0f,0.0f,2.0f,1.0f,0.0f},
	{-5.0f,-3.0f,-4.0f,-2.0f,-1.0f},
	{0.0f,2.0f,1.0f,-1.0f,1.0f},
};

void MeshField::Init(float width, float height, int Max, int sideMax, int lengthMax) {
	gridMax = Max;
	indexNum = (sideMax * 2 + 2) * (lengthMax - 1) - 2;
	Texture = TextureManager::Load("asset/rane.png");
	vertexNum = sideMax * lengthMax;
	pMeshFieldVertex = new MeshFieldVertex[vertexNum];
	WORD* g_pMeshFieldVertexIndex = new WORD[indexNum];
	float posX = 0, posZ = 0;
	int num = 0;
/*	for (int z = 0; z < lengthMax + 1; z++) {
		posX = 0;
		for (int x = 0; x < sideMax + 1; x++) {
			pMeshFieldVertex[z * sideMax + x].position = XMFLOAT3( x - sideMax / 2,-0.8f,-z + lengthMax / 2);
			pMeshFieldVertex[z * sideMax + x].normal =   XMFLOAT3( 0,1.0f,0 );
			pMeshFieldVertex[z * sideMax + x].color = XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
			pMeshFieldVertex[z * sideMax + x].texcoord = XMFLOAT2(x, z);
			num++;
		}
	}

//	num = 0;
	XMFLOAT3 va, vb;
	for (int z = 1; z < lengthMax - 1; z++) {
		float startX = -(width * sideMax / 2);
		float startZ = (height * lengthMax / 2);
		posX = 0;
		for (int x = 1; x < sideMax - 1; x++) {
			va.x = pMeshFieldVertex[(z - 1) * sideMax + x].position.x - pMeshFieldVertex[(z + 1) * sideMax + x].position.x;
			va.y = pMeshFieldVertex[(z - 1) * sideMax + x].position.y - pMeshFieldVertex[(z + 1) * sideMax + x].position.y;
			va.z = pMeshFieldVertex[(z - 1) * sideMax + x].position.z - pMeshFieldVertex[(z + 1) * sideMax + x].position.z;

			vb.x = pMeshFieldVertex[z * sideMax + (x + 1)].position.x - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.x;
			vb.y = pMeshFieldVertex[z * sideMax + (x + 1)].position.y - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.y;
			vb.z = pMeshFieldVertex[z * sideMax + (x + 1)].position.z - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.z;
			
			//外積の計算
			XMFLOAT3 n = { va.y * vb.z - va.z * vb.y,va.z * vb.x - va.x * vb.z,va.x * vb.y - va.y * vb.x };
			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z); //三平方の定理を使う
			
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length; //正規化（ノーマライズ）　長さ1に
			pMeshFieldVertex[z * sideMax + x].normal = n;
		}
	}

	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(MeshFieldVertex) * sideMax * lengthMax;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pMeshFieldVertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

//	unsigned  index[(sideMax * 2 + 2) * (lengthMax - 1) - 2];
//	WORD* g_pMeshFieldVertexIndex = new WORD[indexNum];
	unsigned short* g_pMeshFieldVertexIndex = new unsigned short[indexNum];
	int VertexNum = 0;

	for (int z = 0; z < lengthMax; z++) {
		for (int x = 0; x < (sideMax + 1); x++) {
			g_pMeshFieldVertexIndex[VertexNum] = (z + 1) * sideMax + x;
			VertexNum++;
			g_pMeshFieldVertexIndex[VertexNum] = z * sideMax + x;
			VertexNum++;
		}
		if (z != lengthMax - 2)
			break;

		g_pMeshFieldVertexIndex[VertexNum] = z * sideMax + sideMax - 1;
		VertexNum++;
		g_pMeshFieldVertexIndex[VertexNum] = (z + 2) * sideMax;
		VertexNum++;
	}

	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * indexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = g_pMeshFieldVertexIndex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}
	m_Transform.Scale = { 1.0f,1.0f,1.0f };
	m_width = width;
	m_sideMax = sideMax+1;
	*/

	for (int z = 0; z < lengthMax; z++)
	{
		float startX = -(width * (sideMax - 2) / 2);
		float startZ = (height * lengthMax / 2);
		for (int x = 0; x < sideMax; x++)
		{
			pMeshFieldVertex[z * sideMax + x].position.x = startX + x*width - sideMax / 2;
			pMeshFieldVertex[z * sideMax + x].position.z = startZ -z*height + lengthMax / 2;
//			pMeshFieldVertex[z * sideMax + x].position.y = sinf(x * 0.5f) * sinf(z * 0.3f) * 2.0f;
			pMeshFieldVertex[z * sideMax + x].position.y = -0.8;
			pMeshFieldVertex[z * sideMax + x].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pMeshFieldVertex[z * sideMax + x].texcoord = XMFLOAT2(x, z);
			pMeshFieldVertex[z * sideMax + x].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
	}

	for (int z = 1; z < lengthMax - 1; z++)
	{
		for (int x = 1; x < sideMax - 1; x++)
		{
			XMFLOAT3 va, vb, n;
			float len;

			va.x = pMeshFieldVertex[(z - 1) * sideMax + x].position.x - pMeshFieldVertex[(z + 1) * sideMax + x].position.x;
			va.y = pMeshFieldVertex[(z - 1) * sideMax + x].position.y - pMeshFieldVertex[(z + 1) * sideMax + x].position.y;
			va.z = pMeshFieldVertex[(z - 1) * sideMax + x].position.z - pMeshFieldVertex[(z + 1) * sideMax + x].position.z;

			vb.x = pMeshFieldVertex[z * sideMax + (x + 1)].position.x - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.x;
			vb.y = pMeshFieldVertex[z * sideMax + (x + 1)].position.y - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.y;
			vb.z = pMeshFieldVertex[z * sideMax + (x + 1)].position.z - pMeshFieldVertex[(z - 1) * sideMax + (x - 1)].position.z;

			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			len = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			n.x /= len;
			n.y /= len;
			n.z /= len;

			pMeshFieldVertex[z * sideMax + x].normal = n;
		}
	}

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * sideMax * lengthMax;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pMeshFieldVertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}



	unsigned short i = 0;
	for (int z = 0; z < lengthMax - 1; z++)
	{
		for (int x = 0; x < sideMax; x++)
		{
			g_pMeshFieldVertexIndex[i] = (z + 1) * sideMax + x;
			i++;
			g_pMeshFieldVertexIndex[i] = z * sideMax + x;
			i++;
		}

		if (z == lengthMax - 2)
			break;

		g_pMeshFieldVertexIndex[i] = z * sideMax + sideMax - 1;
		i++;
		g_pMeshFieldVertexIndex[i] = (z + 2) * sideMax;
		i++;
	}


	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * ((sideMax * 2 + 2) * (lengthMax - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = g_pMeshFieldVertexIndex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}



	m_Transform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Transform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

}

void MeshField::UnInit() {
	delete pMeshFieldVertex;
}

void MeshField::Update() {
/*
	if (Input::Keyboard_IsPress('A')) {
		m_Transform.Position.x -= 0.1f;
	}
	if (Input::Keyboard_IsPress('D')) {
		m_Transform.Position.x += 0.1f;
	}
	if (Input::Keyboard_IsPress('W')) {
		m_Transform.Position.z += 0.1f;
	}
	if (Input::Keyboard_IsPress('S')) {
		m_Transform.Position.z -= 0.1f;
	}*/
}

void MeshField::Draw() {
	//しすいだカリング
	CCamera* camera;
	camera = CManager::GetScene()->GetComponent<CCamera>(Scene::CameraLayer);
	if (camera->GetVisibility(m_Transform.Position) == false)
		return;


	// テクスチャ設定
	CRenderer::SetTexture(Texture);
	// 頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	// インデックスバッファ設定
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	m_Transform.SetWorldMatrix();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
	CRenderer::GetDeviceContext()->DrawIndexed(indexNum, 0, 0);

}

float MeshField::GetHeight(XMFLOAT3 position) {
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;
	v = XMFLOAT3(0.0f, -10.0f, 0.0f);

	x =  (position.x + (m_width * (m_sideMax-1) * 0.5)) / m_width; //こっちはポリゴン数
	z = -(position.z - (m_width * (m_sideMax-1) * 0.5))/ m_width; //0.1は1マス分の値を入れる

	va.x = pMeshFieldVertex[(z + 1) * m_sideMax + (x + 1)].position.x - pMeshFieldVertex[z * m_sideMax + x].position.x;//こっちは頂点数
	va.y = pMeshFieldVertex[(z + 1) * m_sideMax + (x + 1)].position.y - pMeshFieldVertex[z * m_sideMax + x].position.y;
	va.z = pMeshFieldVertex[(z + 1) * m_sideMax + (x + 1)].position.z - pMeshFieldVertex[z * m_sideMax + x].position.z;

	vb.x = position.x - pMeshFieldVertex[z * m_sideMax + x].position.x;
	vb.y = position.y - pMeshFieldVertex[z * m_sideMax + x].position.y;
	vb.z = position.z - pMeshFieldVertex[z * m_sideMax + x].position.z;

	if (va.z * vb.x - va.x * vb.z > 0.0f) {
		p0 = pMeshFieldVertex[(z + 1) * m_sideMax + x].position;
		p1 = pMeshFieldVertex[z * m_sideMax + x].position;
		p2 = pMeshFieldVertex[(z + 1) * m_sideMax + (x+1)].position;
	}
	else {
		p0 = pMeshFieldVertex[z * m_sideMax + (x + 1)].position;
		p1 = pMeshFieldVertex[(z + 1) * m_sideMax + (x + 1)].position;
		p2 = pMeshFieldVertex[z * m_sideMax + x].position;
	}

	v01 = { p1.x - p0.x,p1.y - p0.y, p1.z - p0.z, };
	v02 = { p2.x - p0.x,p2.y - p0.y, p2.z - p0.z, };;
	n = { v01.y * v02.z - v01.z * v02.y,v01.z * v02.x - v01.x * v02.z,v01.x * v02.y - v01.y * v02.x }; //外積を求める
	dvn = (v.x * n.x) + (v.y * n.y) + (v.z * n.z);
	dp0n = (p0.x * n.x) + (p0.y * n.y) + (p0.z * n.z);
	dpn = (position.x * n.x) + (position.y * n.y) + (position.z * n.z);
	t = (dp0n - dpn) / dvn;
	hp = { position.x + v.x * t,position.y + v.y * t,position.z + v.z * t };
	return hp.y;
	
}
