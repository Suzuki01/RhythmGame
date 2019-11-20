#include <list>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game_object.h"
#include "input.h"
#include "camera.h"
#include "texture.h"
#include "texture_manager.h"
#include "scene.h"
#include "bill_board.h"

typedef struct {
	XMFLOAT3 position;//VECTOR4は座標変換済み頂点rhw = 1.0が2dの時に入っていた
	XMFLOAT3 normal; //法線ベクトル
	XMFLOAT4 color;
	XMFLOAT2 texcoord;
}BillBoardVertex;


BillBoard::BillBoard() {

}

BillBoard::~BillBoard() {
	m_VertexBuffer->Release();
}

void BillBoard::Init(char* fileName) {
	// 頂点バッファ生成
	{
		m_Transform.Position = { 0,0,0 };
		m_Transform.Scale = { 3.0f,3.0f,3.0f };
		//頂点データ
		static const BillBoardVertex v[] = {
			{ XMFLOAT3(0.0f,1.0f,0.0f),XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(0,0) },
			{ XMFLOAT3(1.0f,1.0f,0.0f),XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(1,0) },
			{ XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(0,1) },
			{ XMFLOAT3(1.0f,0.0f,0.0f),XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(1,1) },
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(BillBoardVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = v;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}
	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture = TextureManager::Load(fileName);
}

void BillBoard::UnInit() {

}

void BillBoard::Draw() {
	CRenderer::SetZBuffer(false);
	// テクスチャ設定
	CRenderer::SetTexture(m_Texture);
	// 頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	m_Transform.SetBillBoardWorldMatrix();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
	CRenderer::GetDeviceContext()->Draw(4, 0);//ポリゴン描画
	CRenderer::SetZBuffer(true);
}

void BillBoard::Update()
{
}

void BillBoard::SetTexture(char* fileName) {
	m_Texture = TextureManager::Load(fileName);
}

/*
void BillBoardAnimation_Draw(int texture_index, float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int tx, int ty, int tw, int th) {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//�Cワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorld; //4*4
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScale;
	float v0, v1;
	float u0, u1;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	v0 = (float)ty / h;
	v1 = (float)ty / h + (float)th / h;
	u0 = (float)tx / w;
	u1 = (float)tx / w + (float)tw / w;

	BillBoardVertex* pBillBoardVertex = NULL;
	g_pVertexBuffer->Lock(0, 0, (void**)& pBillBoardVertex, 0);

	//頂点データ
	BillBoardVertex v[] = {
		{ D3DXVECTOR3(-0.5f, 0.5f,0.0f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR3(0.5f, 0.5f,0.0f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR3(-0.5f,-0.5f,0.0f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR3(0.5f,-0.5f,0.0f), D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) },
	};

	memcpy(pBillBoardVertex, &v, sizeof(v));
	g_pVertexBuffer->Unlock();


	D3DXMatrixTranslation(&mtxTranslation, posX, posY, posZ); //行列の平行移動
	D3DXMatrixScaling(&mtxScale, scaleX, scaleY, scaleZ);
	//D3DXMatrixInverse(&mtxInvV, NULL, &GetViewMatrix()); //逆行列の作成
	D3DXMatrixTranspose(&mtxInvV, &GetViewMatrix());	//転置行列の作成
	mtxInvV._14 = 0.0f; //せん断の部分の値を0に
	mtxInvV._24 = 0.0f;
	mtxInvV._34 = 0.0f;

	mtxWorld = mtxScale * mtxInvV * mtxTranslation;
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld); //第1引数：どういう変換タイプ？第2引数：その行列のアドレスは？

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //ライトを使うか使わないか
													//アンビエントの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); //αテスト有効　デバイス作成時はFALSE
	pDevice->SetRenderState(D3DRS_ALPHAREF, THRESHOLD_VALUE); // 第2引数にしきい値の値を入れる
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//zテスト
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	//テクスチャの設定
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillBoardVertex));
	pDevice->SetFVF(FVF_BILL_BOARD_VERTEX);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
*/
