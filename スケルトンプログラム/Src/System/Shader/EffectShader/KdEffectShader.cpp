#include "System/KdSystem.h"

#include "KdEffectShader.h"


void KdEffectShader::DrawLine(const Math::Vector3 & p1, const Math::Vector3 & p2, const Math::Color & color)
{
	Vertex vertex[2] = {
		{p1, {0,0}, color},
		{p2, {1,1}, color},
	};

	// ���_��`��
	D3D.DrawVertices(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, 2, &vertex[0], sizeof(Vertex));
}

bool KdEffectShader::Init()
{
	//-------------------------------------
	// ���_�V�F�[�_
	//-------------------------------------
	{
		// �R���p�C���ς݂̃V�F�[�_�[�w�b�_�[�t�@�C�����C���N���[�h
		#include "KdEffectShader_VS.inc"

		// ���_�V�F�[�_�[�쐬
		if (FAILED(D3D.GetDev()->CreateVertexShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_VS))) {
			assert(0 && "���_�V�F�[�_�[�쐬���s");
			Release();
			return false;
		}

		// �P���_�̏ڍׂȏ��
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		// ���_���̓��C�A�E�g�쐬
		if (FAILED(D3D.GetDev()->CreateInputLayout(
			&layout[0],			// ���̓G�������g�擪�A�h���X
			layout.size(),		// ���̓G�������g��
			&compiledBuffer[0],				// ���_�o�b�t�@�̃o�C�i���f�[�^
			sizeof(compiledBuffer),			// ��L�̃o�b�t�@�T�C�Y
			&m_inputLayout))					// 
		) {
			assert(0 && "CreateInputLayout���s");
			Release();
			return false;
		}
	}


	//-------------------------------------
	// �s�N�Z���V�F�[�_
	//-------------------------------------
	{
		// �R���p�C���ς݂̃V�F�[�_�[�w�b�_�[�t�@�C�����C���N���[�h
		#include "KdEffectShader_PS.inc"

		if (FAILED(D3D.GetDev()->CreatePixelShader(compiledBuffer, sizeof(compiledBuffer), nullptr, &m_PS))) {
			assert(0 && "�s�N�Z���V�F�[�_�[�쐬���s");
			Release();
			return false;
		}
	}

	//-------------------------------------
	// �萔�o�b�t�@�쐬
	//-------------------------------------
	m_cb0.Create();

	return true;
}

void KdEffectShader::Release()
{
	KdSafeRelease(m_VS);
	KdSafeRelease(m_PS);
	KdSafeRelease(m_inputLayout);
	m_cb0.Release();
}

void KdEffectShader::SetToDevice()
{
	// ���_�V�F�[�_���Z�b�g
	D3D.GetDevContext()->VSSetShader(m_VS, 0, 0);
	// ���_���C�A�E�g���Z�b�g
	D3D.GetDevContext()->IASetInputLayout(m_inputLayout);

	// �s�N�Z���V�F�[�_���Z�b�g
	D3D.GetDevContext()->PSSetShader(m_PS, 0, 0);

	// �萔�o�b�t�@���Z�b�g
	D3D.GetDevContext()->VSSetConstantBuffers(0, 1, m_cb0.GetAddress());
	D3D.GetDevContext()->PSSetConstantBuffers(0, 1, m_cb0.GetAddress());
}

// �e�N�X�`���Z�b�g

void KdEffectShader::SetTexture(ID3D11ShaderResourceView * srv)
{
	if (srv)
	{
		D3D.GetDevContext()->PSSetShaderResources(0, 1, &srv);
	}
	else
	{
		// �e�N�X�`���������ꍇ�́A���e�N�X�`�����Z�b�g����
		D3D.GetDevContext()->PSSetShaderResources(0, 1, D3D.GetWhiteTex()->GetSRViewAddress());
	}
}
