#pragma once

// ���_�\����
struct VERTEX_3D
{
    XMFLOAT3 Position;
    XMFLOAT3 Normal;
    XMFLOAT4 Diffuse;
    XMFLOAT2 TexCoord;
};


// �F�\����
struct COLOR
{
	COLOR(){}
	COLOR( float _r, float _g, float _b, float _a )
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;
};

// �}�e���A���\����
struct MATERIAL
{
	COLOR		Ambient;
	COLOR		Diffuse;
	COLOR		Specular;
	COLOR		Emission;
	float		Shininess;
	float		Dummy[3];//16bit���E�p
};




// �}�e���A���\����
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};


// �`��T�u�Z�b�g�\����
struct DX11_SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	XMFLOAT4	Direction;
	COLOR		Diffuse;
	COLOR		Ambient;
};


class CVertexBuffer;
class CIndexBuffer;
class CTexture;


class CRenderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_D3DDevice;
	static ID3D11DeviceContext*    m_ImmediateContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;



	static ID3D11VertexShader*     m_VertexShader;
	static ID3D11PixelShader*      m_PixelShader;
	static ID3D11InputLayout*      m_VertexLayout;
	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11BlendState*		m_pBlendState;

/*
	static XMMATRIX				m_WorldMatrix;
	static XMMATRIX				m_ViewMatrix;
	static XMMATRIX				m_ProjectionMatrix;
*/
	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;


public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D(XMFLOAT3 pos);
	static void SetWorldMatrix(XMMATRIX * WorldMatrix);
	static void SetViewMatrix(XMMATRIX * ViewMatrix);
	static void SetProjectionMatrix(XMMATRIX * ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetVertexBuffers( ID3D11Buffer* VertexBuffer );
	static void SetIndexBuffer( ID3D11Buffer* IndexBuffer );
	static void SetTexture( CTexture* Texture );
	static void DrawIndexed( unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation );

	static ID3D11Device* GetDevice( void ){ return m_D3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_ImmediateContext; }


};
