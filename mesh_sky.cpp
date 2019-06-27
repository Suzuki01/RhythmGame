#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "math.h"
#include "input.h"

//3D�|���S�����_�@�\����
typedef struct
{
	XMFLOAT3 pos;	//	���Wx,y,z
	XMFLOAT3 normal;
	XMFLOAT4 color;
	XMFLOAT2 uv;		//  �e�N�X�`��

}MeshSkyVertex;

//�AFVF�̒�`
#define FVF_VERTEX3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		// 3D�|���S�����_�t�H�[�}�b�g
#define MAX_MESH_FIELD (5000)

MeshSkyVertex* g_pMfield[MAX_MESH_FIELD];

static int g_VertexCount = { 0 };
static int g_PrimitiveCount = { 0 };
static int g_IndexCount = 0;

//���_�o�b�t�@
ID3D11Buffer* fm_VertexBuffer = NULL;

//�C���f�b�N�X�o�b�t�@
ID3D11Buffer* fm_IndexBuffer = NULL;


void Mesh_Skydome_Initialize(float meshH, float radius, int meshXnum, int meshYnum)
{
	int VertexX = meshXnum + 1;	//	�ő咸�_X
	int VertexY = meshYnum + 1;	//	�ő咸�_Z

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



	// ���z�A�h���X�@
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

	// ���_�o�b�t�@����
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

	// �C���f�b�N�X�o�b�t�@����
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
	// �e�N�X�`���ݒ�
	CRenderer::SetTexture();
	// ���_�o�b�t�@�ݒ�
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	//D3DXMatrixIdentity(&mtxWorld);		//�P�ʍs������
	XMMATRIX viewMatrix = XMMatrixTranslation(0,0,0);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�[�ݒ�i���_���ǂ�����Č��Ԃ��j
	CRenderer::GetDeviceContext()->DrawIndexed(g_IndexCount, 0, 0);

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MeshSkyVertex));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_VertexCount, 0, g_PrimitiveCount);
	*/
}