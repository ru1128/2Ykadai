#include "System/KdSystem.h"

#include "KdTexture.h"


bool KdTexture::Load(const std::string & filename, bool renderTarget, bool depthStencil, bool generateMipmap)
{
	Release();
	if (filename.empty())return false;

	// �t�@�C������WideChar�֕ϊ�
	std::wstring wFilename = sjis_to_wide(filename);

	// Bind Flags
	UINT bindFlags = 0;
	bindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if (renderTarget)bindFlags |= D3D11_BIND_RENDER_TARGET;
	if (depthStencil)bindFlags |= D3D11_BIND_DEPTH_STENCIL;

	// ��DirectX Tex���C�u�������g�p���ĉ摜��ǂݍ���

	DirectX::TexMetadata meta;
	DirectX::ScratchImage image;

	bool bLoaded = false;

	// WIC�摜�ǂݍ���
	//  WIC_FLAGS_ALL_FRAMES �c gif�A�j���Ȃǂ̕����t���[����ǂݍ���ł����
	if (SUCCEEDED(DirectX::LoadFromWICFile(wFilename.c_str(), DirectX::WIC_FLAGS_ALL_FRAMES, &meta, image)))
	{
		bLoaded = true;
	}

	// DDS�摜�ǂݍ���
	if (bLoaded == false) {
		if (SUCCEEDED(DirectX::LoadFromDDSFile(wFilename.c_str(), DirectX::DDS_FLAGS_NONE, &meta, image)))
		{
			bLoaded = true;
		}
	}

	// TGA�摜�ǂݍ���
	if (bLoaded == false) {
		if (SUCCEEDED(DirectX::LoadFromTGAFile(wFilename.c_str(), &meta, image)))
		{
			bLoaded = true;
		}
	}

	// HDR�摜�ǂݍ���
	if (bLoaded == false) {
		if (SUCCEEDED(DirectX::LoadFromHDRFile(wFilename.c_str(), &meta, image)))
		{
			bLoaded = true;
		}
	}

	// ���s
	if (bLoaded == false)
	{
		Release();
		return false;
	}

	// �~�b�v�}�b�v����
	if (meta.mipLevels == 1 && generateMipmap)
	{
		DirectX::ScratchImage mipChain;
		if (SUCCEEDED(DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipChain)))
		{
			image.Release();
			image = std::move(mipChain);
		}
	}

	//------------------------------------
	// �e�N�X�`�����\�[�X�쐬
	//------------------------------------
	D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
	UINT cpuAccessFlags = 0;

	if (FAILED(DirectX::CreateTextureEx(
		D3D.GetDev(),						// Direct3D Device
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		usage,								// Usage
		bindFlags,							// Bind Flags
		cpuAccessFlags,						// CPU Access Flags
		0,									// MiscFlags
		false,								// ForceSRGB
		(ID3D11Resource**)&m_resource)
	)) {
		Release();
		return false;
	}

	//------------------------------------
	// �e�N�X�`�����\�[�X(m_resource)����A�e�r���[���쐬����
	//------------------------------------
	if (CreateViewsFromResource() == false)
	{
		Release();
		return false;
	}

	m_filepath = filename;

	return true;
}

bool KdTexture::Create(const D3D11_TEXTURE2D_DESC & desc, const D3D11_SUBRESOURCE_DATA * fillData)
{
	Release();

	//--------------------------------------------
	// 2D�e�N�X�`���̐���
	//--------------------------------------------
	HRESULT hr = D3D.GetDev()->CreateTexture2D(&desc, fillData, &m_resource);
	if (FAILED(hr)) {
		Release();
		return false;
	}

	//--------------------------------------------
	// m_pTexture2D����A�e�r���[���쐬����
	//--------------------------------------------
	if (CreateViewsFromResource() == false) {
		Release();
		return false;
	}

	return true;
}

bool KdTexture::Create(int w, int h, DXGI_FORMAT format, UINT arrayCnt, const D3D11_SUBRESOURCE_DATA * fillData)
{
	Release();

	// �쐬����2D�e�N�X�`���ݒ�
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = (UINT)w;
	desc.Height = (UINT)h;
	desc.CPUAccessFlags = 0;
	desc.MipLevels = 1;
	desc.ArraySize = arrayCnt;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// �쐬
	if (Create(desc, fillData) == false)return false;

	return true;
}

bool KdTexture::CreateRenderTarget(int w, int h, DXGI_FORMAT format, UINT arrayCnt, const D3D11_SUBRESOURCE_DATA * fillData)
{
	Release();

	// �쐬����2D�e�N�X�`���ݒ�
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.Width = (UINT)w;
	desc.Height = (UINT)h;
	desc.CPUAccessFlags = 0;
	desc.MipLevels = 1;
	desc.ArraySize = arrayCnt;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// �쐬
	if (Create(desc, fillData) == false)return false;

	// �t�@�C�����L��
	m_filepath = "";

	return true;
}

bool KdTexture::CreateDepth(int w, int h, DXGI_FORMAT format, UINT arrayCnt, const D3D11_SUBRESOURCE_DATA* fillData)
{
	Release();

	// 2D�e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	desc.Width = (UINT)w;
	desc.Height = (UINT)h;
	desc.CPUAccessFlags = 0;
	desc.MipLevels = 1;
	desc.ArraySize = arrayCnt;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// �쐬
	if (Create(desc, fillData) == false)return false;

	// �t�@�C�����L��
	m_filepath = "";

	return true;
}

void KdTexture::ClearRenerTarget(const Math::Color & ColorRGBA)
{
	assert(m_rtv != nullptr && "RenderTarget����Ȃ��̂�Clear�ł��܂���");

	D3D.GetDevContext()->ClearRenderTargetView(m_rtv, ColorRGBA);
}

void KdTexture::ClearDepth(bool bDepth, bool bStencil, FLOAT depth, UINT8 stencil)
{
	assert(m_dsv != nullptr && "DepthStencil����Ȃ��̂�Clear�ł��܂���");

	UINT flags = 0;
	if (bDepth)flags |= D3D11_CLEAR_DEPTH;		// Z�o�b�t�@�������N���A
	if (bStencil)flags |= D3D11_CLEAR_STENCIL;	// �X�e���V���o�b�t�@�������N���A

	D3D.GetDevContext()->ClearDepthStencilView(m_dsv, flags, depth, stencil);
}


void KdTexture::Release()
{
	KdSafeRelease(m_resource);
	KdSafeRelease(m_srv);
	KdSafeRelease(m_rtv);
	KdSafeRelease(m_dsv);

	m_filepath = "";
}

bool KdTexture::CreateViewsFromResource()
{
	// ���\�[�X������
	if (m_resource == nullptr)return false;

	// �e�N�X�`���{�̂̏��擾
	m_resource->GetDesc(&m_desc);

	//===========================================================
	//
	// RenderTargetView���쐬����
	//
	//===========================================================
	KdSafeRelease(m_rtv);

	// �����_�[�^�[�Q�b�g�t���O�����Ă鎞�̂�
	if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		// �쐬����r���[�̐ݒ�
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = m_desc.Format;	// Format
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;			// �P�i�e�N�X�`��

		// �����_�[�^�[�Q�b�g�r���[�쐬
		HRESULT hr = D3D.GetDev()->CreateRenderTargetView(m_resource, &rtvDesc, &m_rtv);
		if (FAILED(hr))
		{
			Release();
			assert(0 && "RenderTargetView�̍쐬�Ɏ��s");
			return false;
		}
	}

	//===========================================================
	//
	// ShaderResourceView�̏����쐬����
	//
	//===========================================================
	KdSafeRelease(m_srv);

	// �V�F�[�_���\�[�X�r���[�t���O�����Ă鎞�̂�
	if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		// �쐬����r���[�̐ݒ�
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

		// �e�N�X�`����Z�o�b�t�@�̏ꍇ�́A�œK�ȃt�H�[�}�b�g�ɂ���
		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
		{
			switch (m_desc.Format) {
				// 16�r�b�g
			case DXGI_FORMAT_R16_TYPELESS:
				srvDesc.Format = DXGI_FORMAT_R16_UNORM;
				break;
				// 32�r�b�g
			case DXGI_FORMAT_R32_TYPELESS:
				srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
				break;
				// 24�r�b�g(Z�o�b�t�@) + 8�r�b�g(�X�e���V���o�b�t�@) 
			case DXGI_FORMAT_R24G8_TYPELESS:
				srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				break;
			default:
				assert(0 && "[ShaderResource] �Ή����Ă��Ȃ��t�H�[�}�b�g�ł�");
				break;
			}
		}
		// Z�o�b�t�@�łȂ��ꍇ�́A���̂܂ܓ����t�H�[�}�b�g���g�p
		else
		{
			srvDesc.Format = m_desc.Format;
		}

		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = m_desc.MipLevels;
		if (srvDesc.Texture2D.MipLevels <= 0)srvDesc.Texture2D.MipLevels = -1;

		// �V�F�[�_���\�[�X�r���[�쐬
		HRESULT hr = D3D.GetDev()->CreateShaderResourceView(m_resource, &srvDesc, &m_srv);
		if (FAILED(hr))
		{
			Release();
			assert(0 && "ShaderResourceView�̍쐬�Ɏ��s");
			return false;
		}
	}

	//===========================================================
	//
	// DepthStencilView���쐬����
	//
	//===========================================================
	KdSafeRelease(m_dsv);

	// Z�o�b�t�@�t���O�����Ă鎞�̂�
	if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL) {
		// �쐬����r���[�̐ݒ�
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

		// �e�N�X�`���[�쐬���Ɏw�肵���t�H�[�}�b�g�ƌ݊���������A�[�x�X�e���V���r���[�Ƃ��Ďw��ł���t�H�[�}�b�g���w�肷��
		switch (m_desc.Format) {
			// 16�r�b�g
		case DXGI_FORMAT_R16_TYPELESS:
			dsvDesc.Format = DXGI_FORMAT_D16_UNORM;
			break;
			// 32�r�b�g
		case DXGI_FORMAT_R32_TYPELESS:
			dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
			break;
			// 24�r�b�g(Z�o�b�t�@) + 8�r�b�g(�X�e���V���o�b�t�@) 
		case DXGI_FORMAT_R24G8_TYPELESS:
			dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			break;
		default:
			assert(0 && "[DepthStencil] �Ή����Ă��Ȃ��t�H�[�}�b�g�ł�");
			break;
		}

		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		//-------------------------------
		// �f�v�X�X�e���V���r���[�쐬
		//-------------------------------
		HRESULT hr = D3D.GetDev()->CreateDepthStencilView(m_resource, &dsvDesc, &m_dsv);
		if (FAILED(hr)) {
			Release();
			assert(0 && "DepthStencilView�̍쐬�Ɏ��s");
			return false;
		}
	}

	return true;
}

void KdTexture::GetTextureInfo(ID3D11View * view, D3D11_TEXTURE2D_DESC & outDesc)
{
	outDesc = {};

	ID3D11Resource* res;
	view->GetResource(&res);

	ID3D11Texture2D* tex2D;
	if (SUCCEEDED(res->QueryInterface<ID3D11Texture2D>(&tex2D)))
	{
		tex2D->GetDesc(&outDesc);
		tex2D->Release();
	}
	res->Release();
}
