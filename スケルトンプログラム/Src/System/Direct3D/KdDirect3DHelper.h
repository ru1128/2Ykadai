#pragma once

//========================================================
//
// Direct3D�p�֗��@�\
//
//========================================================



//============================
// �X�e�[�g�쐬�֗��֐�
//============================

// �[�x�X�e���V���X�e�[�g�쐬
// �Edevice				�c D3D�f�o�C�X
// �EzEnable			�c �[�x�e�X�g�L��
// �EzWriteEnable		�c �[�x�������ݗL��
ID3D11DepthStencilState* KdCreateDepthStencilState(ID3D11Device* device, bool zEnable, bool zWriteEnable);

// ���X�^���C�U�[�X�e�[�g�쐬
// �Edevice				�c D3D�f�o�C�X
// �EcullMode			�c �J�����O���[�h
// �EfillMode			�c �O�p�`�̕`�惂�[�h
// �EdepthClipEnable	�c Z�N���b�s���O��L���ɂ���
// �EscissorEnable		�c �؂蔲���͈͂�L���ɂ���
ID3D11RasterizerState* KdCreateRasterizerState(ID3D11Device* device, D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, bool depthClipEnable, bool scissorEnable);

// �T���v���X�e�[�g
enum class SamplerFilterMode {
	Point,			// �|�C���g�t�B���^
	Linear,			// ���`�t�B���^
	Anisotropic,	// �ٕ����t�B���^
};

enum class SamplerAddressingMode {
	Wrap,			// ���b�v���[�h
	Clamp,			// �N�����v���[�h
};

// �Edevice				�c D3D�f�o�C�X
// �EfilterType			�c 0:��ԂȂ� 1:���`�t�B���^ 2:�ٕ����t�B���^
// �EmaxAnisotropy		�c �ٕ����t�B���^���̍ő�l�@2, 4, 6, 8, 10, 12, 14, 16 �̂����ꂩ
// �EaddressingMode		�c �e�N�X�`���A�h���b�V���O���[�h 0:Wrap 1:Clamp
// �EcomparisonModel	�c ��r���[�hON�@�V���h�E�}�b�s���O�ȂǂŎg�p����
ID3D11SamplerState* KdCreateSamplerState(ID3D11Device* device, SamplerFilterMode filterType, UINT maxAnisotropy, SamplerAddressingMode addressingMode, bool comparisonModel);

// �u�����h���[�h�p�萔
enum class BlendMode {
	NoBlend,		// �u�����h�����Ȃ�
	Alpha,			// �������u�����h
	Add,			// ���Z�u�����h
	Stencil			// �X�e���V��
};

// �u�����h�X�e�[�g�쐬
// �Edevice				�c D3D�f�o�C�X
// �Emode				�c �������[�h
ID3D11BlendState* KdCreateBlendState(ID3D11Device* device, BlendMode mode);


