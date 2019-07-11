#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "mesh_field.h"


//頂点バッファ
ID3D11Buffer* m_VertexBuffer = NULL;

//インデックスバッファ
ID3D11Buffer* m_IndexBuffer = NULL; 

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
	vertexNum = ((sideMax + 1) * (lengthMax + 1));
	indexNum = ((sideMax + 1) * 2 * lengthMax) + ((lengthMax - 1) * 2);
	Texture = new CTexture();
	Texture->LoadTexture("asset/field004.tga");
	
	pMeshFieldVertex = new MeshFieldVertex[vertexNum];
	float posX = 0, posZ = 0;
	int num = 0;
	for (int i = 0; i < lengthMax + 1; i++) {
		float startX = -(width * sideMax / 2);
		float startZ = (height * lengthMax / 2);
		posX = 0;
		for (int j = 0; j < sideMax + 1; j++) {
			pMeshFieldVertex[num].position = XMFLOAT3( startX + (j * width),g_FieldHeight[i][j],startZ - (i * height) );
			pMeshFieldVertex[num].normal =   XMFLOAT3( 0,1.0f,0 );
			pMeshFieldVertex[num].color = XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
			pMeshFieldVertex[num].texcoord = XMFLOAT2(j, i);
			num++;
		}
	}
	num = 0;
	XMFLOAT3 va, vb;
	for (int i = 1; i < lengthMax; i++) {
		float startX = -(width * sideMax / 2);
		float startZ = (height * lengthMax / 2);
		posX = 0;
		for (int j = 1; j < sideMax; j++) {
			va.x = pMeshFieldVertex[(i - 1) * lengthMax + j].position.x - pMeshFieldVertex[(i + 1) * 5 + j].position.x;
			va.y = pMeshFieldVertex[(i - 1) * lengthMax + j].position.y - pMeshFieldVertex[(i + 1) * 5 + j].position.y;
			va.z = pMeshFieldVertex[(i - 1) * lengthMax + j].position.z - pMeshFieldVertex[(i + 1) * 5 + j].position.z;

			vb.x = pMeshFieldVertex[i * lengthMax + (j + 1)].position.x - pMeshFieldVertex[i * lengthMax + (j - 1)].position.x;
			vb.y = pMeshFieldVertex[i * lengthMax + (j + 1)].position.y - pMeshFieldVertex[i * lengthMax + (j - 1)].position.y;
			vb.z = pMeshFieldVertex[i * lengthMax + (j + 1)].position.z - pMeshFieldVertex[i * lengthMax + (j - 1)].position.z;
			
			//外積の計算
			XMFLOAT3 n = { va.y * vb.z - va.z * vb.y,va.z * vb.x - va.x * vb.z,va.x * vb.y - va.y * vb.x };
			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z); //三平方の定理を使う
			
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length; //正規化（ノーマライズ）　長さ1に
			pMeshFieldVertex[i * 5 + j].normal = n;
		}
	}

	WORD* g_pMeshFieldVertexIndex = new WORD[indexNum];
	int VertexNum = 0;

	for (int i = 0; i < sideMax; i++) {
		for (int j = 0; j < (lengthMax + 1); j++) {
			g_pMeshFieldVertexIndex[VertexNum] = j * (sideMax + 1) + i;
			g_pMeshFieldVertexIndex[VertexNum + 1] = g_pMeshFieldVertexIndex[VertexNum] + 1;
			VertexNum += 2;
		}
		if (i != sideMax - 1) {
			g_pMeshFieldVertexIndex[VertexNum] = g_pMeshFieldVertexIndex[VertexNum - 1];
			g_pMeshFieldVertexIndex[VertexNum + 1] = i + 1;
			VertexNum += 2;
		}
	}



	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(MeshFieldVertex) * vertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pMeshFieldVertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * (indexNum);
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
}

void MeshField::UnInit() {
	delete pMeshFieldVertex;
}

void MeshField::Update() {

}

void MeshField::Draw() {
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
