
#include "main.h"
#include "renderer.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <unordered_map>
#include <map>


CTexture::~CTexture() {
	Unload();
}


void CTexture::Unload()
{
	m_Texture->Release();
	m_ShaderResourceView->Release();
}

bool CTexture::LoadTexture(std::string FileName) {

	unsigned char* pixels;
	unsigned int texture;
	int width;
	int height;
	int bpp;
	// �t�@�C����ǂݍ��݁A�摜�f�[�^�����o��
	//   �Ō�̈����Ńs�N�Z��������̃o�C�g���������ł���
	pixels = stbi_load(FileName.c_str(), &width, &height, &bpp, STBI_default);
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pixels;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = bpp;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
