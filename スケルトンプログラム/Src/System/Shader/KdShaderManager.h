#pragma once

#include "EffectShader/KdEffectShader.h"
#include "StandardShader/KdStandardShader.h"
#include "SpriteShader/KdSpriteShader.h"

//==========================================================
//
// �V�F�[�_�֌W���܂Ƃ߂��N���X
//
//==========================================================
class KdShaderManager
{
public:

	//==============================================================
	//
	// �������E���
	//
	//==============================================================

	// ������
	void Init();

	// ���
	void Release();

	//==========================
	// �V�F�[�_
	//==========================
	KdStandardShader		m_standardShader;		// 3D���f���`��V�F�[�_
	KdEffectShader			m_effectShader;			// �G�t�F�N�g�`��V�F�[�_
	KdSpriteShader			m_spriteShader;			// 2D�e�N�X�`���`��V�F�[�_

	//==========================
	// �J�����֌W
	//==========================

	// �J�����萔�o�b�t�@�p�\����
	struct cbCamera
	{
		Math::Matrix		mV;			// �r���[�s��
		Math::Matrix		mP;			// �ˉe�s��
		Math::Vector3		CamPos;		// �J�������[���h���W

		int					DistanceFogEnable = 0;			// �����t�H�O�L��
		Math::Vector3		DistanceFogColor = { 1, 1, 1 };	// �����t�H�O�F
		float				DistanceFogDensity = 0.001f;	// �����t�H�O������
	};

	// �J�����萔�o�b�t�@
	KdConstantBuffer<cbCamera>	m_cb7_Camera;

	//==========================
	// ���C�g�֌W
	//==========================

	// ���C�g�萔�o�b�t�@�p�\����
	struct cbLight
	{
		// ����
		Math::Vector3		AmbientLight = {0.3f, 0.3f, 0.3f};
		float					tmp;

		// ���s��
		Math::Vector3		DL_Dir = {0,-1,0};    // ���̕���
		float					tmp2;

		Math::Vector3		DL_Color = {1,1,1};  // ���̐F
		float					tmp3;
	};

	// ���C�g�萔�o�b�t�@
	KdConstantBuffer<cbLight>		m_cb8_Light;

	//==========================
	// ���̑�
	//==========================





//-------------------------------
// �V���O���g��
//-------------------------------
private:

	KdShaderManager() {}

public:
	static KdShaderManager &GetInstance() {
		static KdShaderManager instance;
		return instance;
	}
};

#define SHADER KdShaderManager::GetInstance()
