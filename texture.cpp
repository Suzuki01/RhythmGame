
#include "main.h"
#include "renderer.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <unordered_map>

std::unordered_map<std::string, CTexture>g_TextureIdMap;

/*CTexture* CTexture::Load(std::string FileName)
{
	if (g_TextureIdMap.count(FileName) != 0) {
		return &g_TextureIdMap[FileName];
	}
	else {
		LoadTexture(FileName);
	}
}*/


void CTexture::Unload()
{
	m_Texture->Release();
	m_ShaderResourceView->Release();
}

ID3D11Texture2D* CTexture::LoadTexture(std::string FileName) {

	unsigned char* pixels;
	unsigned int texture;
	int width;
	int height;
	int bpp;
	// ファイルを読み込み、画像データを取り出す
	//   最後の引数でピクセルあたりのバイト数を強制できる
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
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}
	g_TextureIdMap[FileName].m_ShaderResourceView = m_ShaderResourceView;
	return m_Texture;
}
