#pragma once

//====================================================
//
// �e�N�X�`���N���X
//
//====================================================
class KdTexture
{
public:

	//====================================================
	//
	// �擾
	//
	//====================================================
	// �V�F�[�_���\�[�X�r���[�擾
	ID3D11ShaderResourceView*	GetSRView() const { return m_srv; }
	// �����_�[�^�[�Q�b�g�r���[�擾
	ID3D11RenderTargetView*		GetRTView() const { return m_rtv; }
	// �[�x�X�e���V���r���[�擾
	ID3D11DepthStencilView*		GetDSView() const { return m_dsv; }

	// �V�F�[�_���\�[�X�r���[�̃A�h���X�擾
	ID3D11ShaderResourceView* const*	GetSRViewAddress() const { return &m_srv; }

	// �摜���擾
	const D3D11_TEXTURE2D_DESC& GetInfo() const { return m_desc; }

	//====================================================
	//
	// �ǂݍ��݁E�쐬
	//
	//====================================================

	// �摜�t�@�C����ǂݍ��ށBShaderResourceView�͕K�����������B
	// �Efilename		�c �摜�t�@�C����
	// �ErenderTarget	�c �����_�[�^�[�Q�b�g�r���[�𐶐�����
	// �EdepthStencil	�c �[�x�X�e���V���r���[�𐶐�����
	// �EgenerateMipmap	�c �~�b�v�}�b�v��������H
	bool Load(const std::string& filename, bool renderTarget = false, bool depthStencil = false, bool generateMipmap = false);

	// desc��񂩂�e�N�X�`�����\�[�X���쐬����
	// �Edesc		�c �쐬����e�N�X�`�����\�[�X�̏��
	// �EfillData	�c �o�b�t�@�ɏ������ރf�[�^�@nullptr���Ə������݂Ȃ�
	// �߂�l�Ftrue �c ����
	bool Create(const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// �ʏ�e�N�X�`���Ƃ��č쐬
	// ���e�N�X�`�����\�[�X���쐬���AShaderResourceView�݂̂��쐬���܂�
	// �Ew			�c �摜�̕�(�s�N�Z��)
	// �Eh			�c �摜�̍���(�s�N�Z��)
	// �Eformat		�c �摜�̌`���@DXGI_FORMAT���g�p
	// �EarrayCnt	�c �u�e�N�X�`���z��v���g�p����ꍇ�A���̐��B1�Œʏ��1���e�N�X�`��
	// �EfillData	�c �o�b�t�@�ɏ������ރf�[�^�@nullptr���Ə������݂Ȃ�
	// �߂�l�Ftrue �c ����
	bool Create(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// �����_�[�^�[�Q�b�g�e�N�X�`���Ƃ��č쐬
	// ���e�N�X�`�����\�[�X���쐬���ARenderTargetView��ShaderResourceView��2��ނ��쐬���܂�
	// �Ew			�c �摜�̕�(�s�N�Z��)
	// �Eh			�c �摜�̍���(�s�N�Z��)
	// �Eformat		�c �摜�̌`���@DXGI_FORMAT���g�p
	// �EarrayCnt	�c �u�e�N�X�`���z��v���g�p����ꍇ�A���̐��B1�Œʏ��1���e�N�X�`��
	// �EfillData	�c �o�b�t�@�ɏ������ރf�[�^�@nullptr���Ə������݂Ȃ�
	// �߂�l�Ftrue �c ����
	bool CreateRenderTarget(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	// Z�o�b�t�@�e�N�X�`���Ƃ��č쐬
	// ���e�N�X�`�����\�[�X���쐬���ADepthStencilView��ShaderResourceView��2��ނ��쐬���܂�
	// �Ew			�c �摜�̕�(�s�N�Z��)
	// �Eh			�c �摜�̍���(�s�N�Z��)
	// �Eformat		�c �摜�̌`���@DXGI_FORMAT���g�p�@32bit�FDXGI_FORMAT_R32_TYPELESS  �X�e���V���t���FDXGI_FORMAT_R24G8_TYPELESS
	// �EarrayCnt	�c �u�e�N�X�`���z��v���g�p����ꍇ�A���̐��B1�Œʏ��1���e�N�X�`��
	// �EfillData	�c �o�b�t�@�ɏ������ރf�[�^�@nullptr���Ə������݂Ȃ�
	// �߂�l�Ftrue �c ����
	bool CreateDepth(int w, int h, DXGI_FORMAT format = DXGI_FORMAT_R32_TYPELESS, UINT arrayCnt = 1, const D3D11_SUBRESOURCE_DATA* fillData = nullptr);

	//===================================================================
	//
	// �N���A�֌W
	//
	//===================================================================

	// RenderTarget���N���A
	// ��RenderTargetView���쐬����K�v������܂�
	// �EColorRGBA	�c �N���A����F
	void ClearRenerTarget(const Math::Color& ColorRGBA);

	// DepthStencil���N���A
	// ��DepthStencilView���쐬����K�v������܂�
	// �EbDepth		�c Z�o�b�t�@�N���A����H
	// �EbStencil	�c �X�e���V���o�b�t�@�N���A����H
	// �Edepth		�c �N���A����Z�o�b�t�@�̒l
	// �Estencil	�c �N���A����X�e���V���o�b�t�@�̒l
	void ClearDepth(bool bDepth = true, bool bStencil = true, FLOAT depth = 1.0f, UINT8 stencil = 0);

	// 
	KdTexture() {}

	//====================================================
	// ���
	//====================================================
	void Release();

	// 
	~KdTexture()
	{
		Release();
	}

	//====================================================
	// �ÓI�֐�
	//====================================================

	// view����摜�����擾
	static void GetTextureInfo(ID3D11View* view, D3D11_TEXTURE2D_DESC& outDesc);


	//�����_�[�^�[�Q�b�g�̐؂�ւ�(�P�N���p)
	void SetRenderTarget()
	{
		D3D.GetDevContext()->OMSetRenderTargets(1, &m_rtv, D3D.GetZBuffer());
	}

private:

	//--------------------------------------------------------------------------
	// m_resource�̐ݒ�����ɁA�e�r���[���쐬����
	//--------------------------------------------------------------------------
	bool CreateViewsFromResource();

private:

	// �摜���\�[�X
	ID3D11Texture2D*			m_resource = nullptr;
	// �摜���
	D3D11_TEXTURE2D_DESC		m_desc = {};

	// �V�F�[�_���\�[�X�r���[(�ǂݎ��p)
	ID3D11ShaderResourceView*	m_srv = nullptr;
	// �����_�[�^�[�Q�b�g�r���[(�������ݗp)
	ID3D11RenderTargetView*		m_rtv = nullptr;
	// �[�x�X�e���V���r���[(Z�o�b�t�@�p)
	ID3D11DepthStencilView*		m_dsv = nullptr;

	// �摜�t�@�C����
	std::string					m_filepath;

private:
	// �R�s�[�֎~�p
	KdTexture(const KdTexture& src) = delete;
	void operator=(const KdTexture& src) = delete;
};

