#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "mesh_field.h"

typedef struct {
	XMFLOAT3 position;//VECTOR4�͍��W�ϊ��ςݒ��_rhw = 1.0��2d�̎��ɓ����Ă���
	XMFLOAT3 normal; //�@���x�N�g��
	XMFLOAT4 color;
	XMFLOAT2 texcoord;
}MeshFieldVertex;

//���_�o�b�t�@
ID3D11Buffer* m_VertexBuffer = NULL;

//�C���f�b�N�X�o�b�t�@
ID3D11Buffer* m_IndexBuffer = NULL; 

float fieldWidth, fieldHeight;
int gridMax;
static int vertexNum;//���_��
static int indexNum; //�C���f�b�N�X��
CTexture* Texture;
float g_FieldHeight[5][5] = {
	{1.0f,2.0f,0.0f,-1.0f,0.0f},
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
	Texture->LoadAllTexture("asset/field004.tga");
	
	MeshFieldVertex* pMeshFieldVertex = new MeshFieldVertex[vertexNum];
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



	// ���_�o�b�t�@����
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

	// �C���f�b�N�X�o�b�t�@����
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
	m_Transform.Scale = { 10.0f,1.0f,10.0f };
}

void MeshField::UnInit() {
}

void MeshField::Update() {

}

void MeshField::Draw() {
	// �e�N�X�`���ݒ�
	CRenderer::SetTexture(Texture);
	// ���_�o�b�t�@�ݒ�
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	m_Transform.SetWorldMatrix();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�[�ݒ�i���_���ǂ�����Č��Ԃ��j
	CRenderer::GetDeviceContext()->DrawIndexed(indexNum, 0, 0);

}
