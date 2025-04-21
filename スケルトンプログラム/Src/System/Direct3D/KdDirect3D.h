#pragma once

// �֗��@�\
#include "KdDirect3DHelper.h"

class KdTexture;

//=======================================================================================
//
// Direct3D�N���X
//
//	Direct3D11�ɕK�v�ȕϐ���A�悭�s��������܂Ƃ߂Ă��܂��B
//
//
//=======================================================================================
class KdDirect3D {
public:

	//==============================================================
	//
	// �擾
	//
	//==============================================================

	// Direct3D�f�o�C�X�擾
	ID3D11Device*			GetDev() { return m_pDevice; }

	// Direct3D�f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext*	GetDevContext() { return m_pDeviceContext; }

	// SwapChain�擾
	IDXGISwapChain*			GetSwapChain() { return m_pGISwapChain; }

	// �o�b�N�o�b�t�@�擾
	ID3D11RenderTargetView*	GetBackBuffer() { return m_rtvBackBuffer; }

	// Z�o�b�t�@�擾
	ID3D11DepthStencilView*	GetZBuffer() { return m_dsvZBuffer; }

	// �r���[�|�[�g�擾
	void					GetViewport(Math::Viewport& out) const;

	// 1x1 ���e�N�X�`���擾
	const std::shared_ptr<KdTexture>&		GetWhiteTex() const { return m_texWhite; }

	//==============================================================
	//
	// �������E���
	//
	//==============================================================

	// ������
	bool Init(HWND hWnd, int w, int h, bool deviceDebug, std::string& errMsg);

	// ���
	void Release();

	//==============================================================
	//
	// �ȈՃX�e�[�g�ݒ�֐�
	// ������쐬�E������邽�ߌ����͈���
	//
	//==============================================================

	// �ȈՔ� �[�x�X�e���V���X�e�[�g�ݒ�@������쐬�E������邽�ߌ����͈���
	// �Eenable				�c �[�x�e�X�g�L��/����
	// �EwriteEnable		�c �[�x�������ݗL��/����
	void SetDepthStencilState(bool enable, bool writeEnable);

	// �ȈՔ� ���C�X�^���C�U�[�X�e�[�g�ݒ�
	// �EcullMode			�c �J�����O���[�h
	// �EfillMode			�c �O�p�`�̕`�惂�[�h
	// �EdepthClipEnable	�c Z�N���b�s���O��L���ɂ���
	void SetRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool depthClipEnable, bool scissorEnable);

	// �ȈՔ� �T���v���[�X�e�[�g�ݒ�@������쐬�E������邽�ߌ����͈���
	// �EslotNo				�c �Z�b�g����X���b�g�ԍ�
	// �EfilterType			�c �t�B���^�[
	// �EmaxAnisotropy		�c �ٕ����t�B���^(Anisotropic)���̍ő�l�@2, 4, 6, 8, 10, 12, 14, 16 �̂����ꂩ
	// �EaddressingMode		�c �e�N�X�`���A�h���b�V���O���[�h
	// �EcomparisonModel	�c ��r���[�hON�@�V���h�E�}�b�s���O�ȂǂŎg�p����
	void SetSamplerState(int slotNo, SamplerFilterMode filterType, UINT maxAnisotropy, SamplerAddressingMode addressingMode, bool comparisonModel);

	// �ȈՔ� �u�����h�X�e�[�g�ݒ�@������쐬�E������邽�ߌ����͈���
	// �Emode				�c ���[�h
	void SetBlendState(BlendMode mode);

	//==============================================================

	// ���_��`�悷��ȈՓI�Ȋ֐�
	// �����_�o�b�t�@���g���񂵂ĕ`�悵�Ă��܂��̂Ō����͈��߁B���p�t�H�[�}���X���グ�����ꍇ�͍H�v����K�v����B
	// �Etopology		�c ���_���ǂ̂悤�Ȍ`��ŕ`�悷�邩�@D3D_PRIMITIVE_TOPOLOGY�}�N�����g�p
	// �EvertexCount	�c ���_��
	// �EpVertexStream	�c ���_�z��̐擪�A�h���X
	// �Estride			�c �P���_�̃o�C�g�T�C�Y
	void DrawVertices(D3D_PRIMITIVE_TOPOLOGY topology, int vertexCount, const void* pVertexStream, UINT stride);

	//==============================================================

	//�o�b�N�o�b�t�@�֐؂�ւ�(�P�N���p�j
	void SetBackBuffer()
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_rtvBackBuffer, m_dsvZBuffer);
	}

	// 
	~KdDirect3D() {
		Release();
	}

private:

	ID3D11Device*			m_pDevice = nullptr;			// Direct3D11�̒��S�ɂȂ�N���X�B�S�̂̊Ǘ��ƃo�b�t�@�A�V�F�[�_�A�e�N�X�`���Ȃǂ̃��\�[�X�쐬�Ȃǂ��s���BD3D9�Ƃ͈���āA���̃N���X�͕`��֌W�̃����o�֐��������Ȃ��B
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;		// �`�揈�����s���N���X�B
															// �����I�ɂ́A�����_�����O�R�}���h�ƌĂ΂��o�C�i���f�[�^���쐬���AGPU�ɑ���BGPU�������_�����O�R�}���h����͂��邱�ƂŎ��ۂ̕`�揈�����s����B

	IDXGIAdapter*			m_pGIAdapter = nullptr;			// �f�B�X�v���C �T�u�V�X�e��(1�܂��͕�����GPU�ADAC�A����уr�f�I �������[)�B
	IDXGIFactory*			m_pGIFactory = nullptr;			// �t���X�N���[���؂�ւ��ȂǂŎg�p�B
	IDXGISwapChain*			m_pGISwapChain = nullptr;		// �E�C���h�E�ւ̕\����_�u���o�b�t�@�����O�Ȃǂ��s���N���X�B�}���`�T���v�����O�A���t���b�V�����[�g�Ȃǂ̐ݒ���ł���݂����B

	// �o�b�t�@
	ID3D11RenderTargetView*	m_rtvBackBuffer = nullptr;		// �o�b�N�o�b�t�@
	ID3D11DepthStencilView*	m_dsvZBuffer = nullptr;			// Z�o�b�t�@

	// DrawVertices�p ���_�o�b�t�@
	KdBuffer					m_tempVertexBuffer;

	//------------------------
	// �֗��e�N�X�`��
	//------------------------
	// 1x1 ���e�N�X�`��
	std::shared_ptr<KdTexture>	m_texWhite;

//-------------------------------
// �V���O���g��
//-------------------------------
private:

	KdDirect3D() {
	}

public:
	static KdDirect3D &GetInstance() {
		static KdDirect3D instance;
		return instance;
	}
};

// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define D3D KdDirect3D::GetInstance()
