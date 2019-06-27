#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "math.h"
#include "input.h"

//3Dポリゴン頂点　構造体
typedef struct
{
	XMFLOAT3 pos;	//	座標x,y,z
	XMFLOAT3 normal;
	XMFLOAT4 color;
	XMFLOAT2 uv;		//  テクスチャ

}MeshSkyVertex;

//②FVFの定義
#define FVF_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		// 3Dポリゴン頂点フォーマット
#define MAX_MESH_FIELD (5000)

MeshSkyVertex* g_pMfield[MAX_MESH_FIELD];

static int g_VertexCount = { 0 };
static int g_PrimitiveCount = { 0 };
static int g_IndexCount = 0;

//頂点バッファ
ID3D11Buffer* fm_VertexBuffer = NULL;

//インデックスバッファ
ID3D11Buffer* fm_IndexBuffer = NULL;


void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum)
{
	int VertexX = meshXnum + 1;	//	最大頂点X
	int VertexY = meshYnum + 1;	//	最大頂点Z

	g_VertexCount = (VertexX)* (VertexY);
    g_IndexCount = (meshXnum + 2) * (meshYnum * 2) - 2;
	g_PrimitiveCount = (meshXnum * 2 + 4) * meshYnum - 4;


	float Subtotal = 0;
	MeshSkyVertex* m_pMfield = new MeshSkyVertex[g_VertexCount];

	for (int y = 0; y < VertexY; y++)
	{
		if (y == 0)
		{
			for (int x = 0; x < VertexX; x++)
			{
				int n = x + VertexX * y;
				m_pMfield[n].pos = XMFLOAT3(0, meshYnum * meshH, 0);
				m_pMfield[n].normal = XMFLOAT3(0.0, 1.0, 0.0);
				m_pMfield[n].color = XMFLOAT4(255, 255, 255, 255);
				m_pMfield[n].uv = XMFLOAT2(x * (1.0f / meshXnum), y * (1.0f / meshYnum));
			}
		}
		else
		{

			Subtotal += (y * meshH / VertexY) * 2;
			for (int x = 0; x < VertexX; x++)
			{
				int n = x + VertexX * y;
				float angle = 360 / meshXnum * x;

				m_pMfield[n].pos = XMFLOAT3(radius / VertexY * y * sinf(XMConvertToRadians(angle)), (meshYnum * meshH) - Subtotal, radius / VertexY * y * cosf(XMConvertToRadians(angle)));
				m_pMfield[n].normal = XMFLOAT3(0.0, 1.0, 0.0);
				m_pMfield[n].color = XMFLOAT4(255, 255, 255, 255);
				m_pMfield[n].uv = XMFLOAT2(x * (1.0f / meshXnum), y * (1.0f / meshYnum));
			}
		}

	}



	// 仮想アドレス　
	WORD *Ipv;

	for (int y = 0; y < meshYnum * 2 - 1; y++)
	{
		if (y < meshYnum)
		{
			for (int x = 0; x < VertexX * 2; x++)
			{
				if (x % 2 == 0)
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = VertexX + (VertexX * y) + (x * 0.5);
				}
				else
				{
					Ipv[(VertexX + 1) * (2 * y) + x] = (VertexX * y) + ((x - 1) * 0.5);
				}
			}
		}
		else
		{
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum))] = VertexX * (y - meshYnum + 1) - 1;
			Ipv[(VertexX * 2)*(y - meshYnum + 1) + (2 * (y - meshYnum)) + 1] = VertexX * (y - meshYnum + 2);
		}
	}

	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(MeshSkyVertex) * g_VertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_pMfield;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &fm_VertexBuffer);
	}

	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * (g_IndexCount);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Ipv;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &fm_IndexBuffer);
	}



}


void MeshSky_Finalize(void)
{
}

void MeshSky_Update(void)
{
//	D3DXVECTOR3 CameraFront = GetCameraFrontVector();
//	D3DXVECTOR3 CameraRight = GetCameraRightVector();
//	D3DXVECTOR3 f(CameraFront);
//	f.y = 0.0f;
//	D3DXVECTOR3 r(CameraRight);
//	r.y = 0.0f;
/*
	for (int j = 0; j <= g_height; j++)						//row
	{
		for (int i = 0; i <= g_n; i++)					//column
		{
			if (!Keyboard_IsPress(DIK_LALT) && Keyboard_IsPress(DIK_LCONTROL) && Keyboard_IsPress(DIK_W))
			{
				pV[(g_n + 1)*j + i].position += 0.03f*f;
			}
			if (!Keyboard_IsPress(DIK_LALT) && Keyboard_IsPress(DIK_LCONTROL) && Keyboard_IsPress(DIK_S))
			{
				pV[(g_n + 1)*j + i].position -= 0.03f*f;
			}
			if (!Keyboard_IsPress(DIK_LALT) && Keyboard_IsPress(DIK_LCONTROL) && Keyboard_IsPress(DIK_A))
			{
				pV[(g_n + 1)*j + i].position -= 0.03f*r;
			}
			if (!Keyboard_IsPress(DIK_LALT) && Keyboard_IsPress(DIK_LCONTROL) && Keyboard_IsPress(DIK_D))
			{
				pV[(g_n + 1)*j + i].position += 0.03f*r;
			}
		}
	}*/
}

void MeshSky_Draw(int texture_index)
{/*
	// テクスチャ設定
	CRenderer::SetTexture();
	// 頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	// インデックスバッファ設定
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	//D3DXMatrixIdentity(&mtxWorld);		//単位行列を作る
	XMMATRIX viewMatrix = XMMatrixTranslation(0,0,0);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //トポロジー設定（頂点をどうやって結ぶか）
	CRenderer::GetDeviceContext()->DrawIndexed(g_IndexCount, 0, 0);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MeshSkyVertex));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_VertexCount, 0, g_PrimitiveCount);
	*/
}