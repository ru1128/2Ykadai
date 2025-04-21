#include "../inc_KdCommon.hlsli"
#include "inc_KdEffectShader.hlsli"

// �e�N�X�`��
Texture2D g_tex : register(t0);

// �T���v��
SamplerState g_ss : register(s0);

//================================
// �G�t�F�N�g�p�s�N�Z���V�F�[�_
//================================
float4 main(VSOutput In) : SV_Target0
{
    return g_tex.Sample(g_ss, In.UV) * In.Color;
}
