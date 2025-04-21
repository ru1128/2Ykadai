#pragma once

//============================================================
//
// ��{�V�F�[�_
//
//============================================================
class KdStandardShader
{
public:

	//================================================
	// �ݒ�E�擾
	//================================================

	// ���̃V�F�[�_���f�o�C�X�փZ�b�g
	void SetToDevice();

	// ���[���h�s��Z�b�g
	void SetWorldMatrix(const Math::Matrix& m)
	{
		m_cb0.Work().mW = m;
//		m_mTransform = m;
	}

	// UV�^�C�����O�ݒ�
	void SetUVTiling(const Math::Vector2& tiling)
	{
		m_cb0.Work().UVTiling = tiling;
	}
	// UV�I�t�Z�b�g�ݒ�
	void SetUVOffset(const Math::Vector2& offset)
	{
		m_cb0.Work().UVOffset = offset;
	}

	// ���C�g�L��/����
	void SetLightEnable(bool enable)
	{
		m_cb0.Work().LightEnable = enable ? 1 : 0;
	}

	// Set�n�ŃZ�b�g�����f�[�^���A���ۂɒ萔�o�b�t�@�֏�������
	void WriteToCB()
	{
		m_cb0.Write();
	}

	//================================================
	// �`��
	//================================================

	// Model�`��
	// �Emodel			�c �`�悷�郂�f���f�[�^
	// �EnodeTransforms	�c �S�m�[�h�p�̍s����w�肷��
	//                     nullptr��n���ƁAmodel���̃m�[�h�̍s�񂪎g�p�����
	void DrawModel(const KdModel* model, const std::vector<Math::Matrix>* nodeTransforms = nullptr);

	//================================================
	// �������E���
	//================================================

	// ������
	bool Init();
	// ���
	void Release();
	// 
	~KdStandardShader()
	{
		Release();
	}


private:

	// 3D���f���p�V�F�[�_
	ID3D11VertexShader*	m_VS = nullptr;				// ���_�V�F�[�_�[
	ID3D11InputLayout*	m_inputLayout = nullptr;	// ���_���̓��C�A�E�g

	ID3D11PixelShader*	m_PS = nullptr;				// �s�N�Z���V�F�[�_�[

	// �s��ێ��p
	Math::Matrix		m_mTransform;

	// �萔�o�b�t�@
	//  ���萔�o�b�t�@�́A�p�b�L���O�K���Ƃ������̂����炵�Ȃ���΂Ȃ�Ȃ�
	//  <�p�b�L���O�K��> �Q�l�Fhttps://docs.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules
	//  �E�\���̂̃T�C�Y��16�o�C�g�̔{���ɂ���B
	//  �E�e����(�ϐ�)�́A16�o�C�g���E���܂����Ȃ��悤�ɂ���B

	// �萔�o�b�t�@(�I�u�W�F�N�g�P�ʍX�V)
	struct cbObject
	{
		Math::Matrix		mW;		// ���[���h�s��@�s���16�o�C�gx4�o�C�g��64�o�C�g�Ȃ̂Ńs�b�^���B

		// UV����
		Math::Vector2		UVOffset = { 0,0 };
		Math::Vector2		UVTiling = { 1,1 };

		// ���C�g�L��
		int					LightEnable = 1;	// ���C�g�L��
		float tmp[3];
	};
	KdConstantBuffer<cbObject>	m_cb0;

	// �萔�o�b�t�@(�}�e���A���P�ʍX�V)
	struct cb {
		Math::Vector4	BaseColor;
		Math::Vector3	Emissive;
		float			Metallic;
		float			Roughness;
		float			tmp[3];
	};
	KdConstantBuffer<cb>	m_cb1_Material;

};


