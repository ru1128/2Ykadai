#pragma once


//============================================================
//
// �G�t�F�N�g�V�F�[�_
//
//============================================================
class KdEffectShader
{
public:

	// �P���_�̌`��
	struct Vertex
	{
		Math::Vector3 Pos;
		Math::Vector2 UV;
		Math::Vector4 Color;
	};

	//================================================
	// �擾�E�ݒ�
	//================================================

	// ���̃V�F�[�_���f�o�C�X�փZ�b�g
	void SetToDevice();

	// �e�N�X�`���Z�b�g
	void SetTexture(ID3D11ShaderResourceView* srv);

	// ���[���h�s��Z�b�g
	void SetWorldMatrix(const Math::Matrix& m)
	{
		m_cb0.Work().mW = m;
	}

	// UV Offset�Z�b�g
	void SetUVOffset(const Math::Vector2& offset)
	{
		m_cb0.Work().UVOffset = offset;
	}

	// UV Tiling�Z�b�g
	void SetUVTiling(const Math::Vector2& tiling)
	{
		m_cb0.Work().UVTiling = tiling;
	}

	// Set�n�ŃZ�b�g�����f�[�^���A���ۂɒ萔�o�b�t�@�ւ̏�������
	void WriteToCB()
	{
		m_cb0.Write();
	}

	//================================================
	// �`��֌W
	//================================================

	// 3D���`��
	void DrawLine(const Math::Vector3& p1, const Math::Vector3& p2, const Math::Color& color);

	//================================================
	// 
	//================================================

	// ������
	bool Init();

	// ���
	void Release();

	// 
	~KdEffectShader()
	{
		Release();
	}


private:

	// 3D���f���p�V�F�[�_
	ID3D11VertexShader*	m_VS = nullptr;				// ���_�V�F�[�_�[
	ID3D11InputLayout*	m_inputLayout = nullptr;	// ���_���̓��C�A�E�g

	ID3D11PixelShader*	m_PS = nullptr;				// �s�N�Z���V�F�[�_�[

	// �萔�o�b�t�@
	//  ���萔�o�b�t�@�́A�p�b�L���O�K���Ƃ������̂����炵�Ȃ���΂Ȃ�Ȃ�
	//  <�p�b�L���O�K��> �Q�l�Fhttps://docs.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules
	//  �E�\���̂̃T�C�Y��16�o�C�g�̔{���ɂ���B
	//  �E�e����(�ϐ�)�́A16�o�C�g���E���܂����Ȃ��悤�ɂ���B

	// �萔�o�b�t�@(�I�u�W�F�N�g�P�ʍX�V)
	struct cbObject
	{
		Math::Matrix		mW;		// ���[���h�s��@�s���16�o�C�gx4�o�C�g��64�o�C�g�Ȃ̂Ńs�b�^���B

		Math::Vector2		UVOffset = { 0, 0 };
		Math::Vector2		UVTiling = { 1, 1 };
	};
	KdConstantBuffer<cbObject>	m_cb0;
};


