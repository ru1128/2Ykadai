#include "../inc_KdCommon.hlsli"
#include "inc_KdEffectShader.hlsli"

//================================
// �G�t�F�N�g�p ���_�V�F�[�_
//================================
VSOutput main(float4 pos : POSITION, // ���_���W
              float2 uv : TEXCOORD0,  // �e�N�X�`��UV���W
              float4 color : COLOR    // �F
){
    VSOutput Out;

    // ���W�ϊ�
    Out.Pos = mul(pos, g_mW);       // ���[�J�����W�n -> ���[���h���W�n�֕ϊ�
    Out.Pos = mul(Out.Pos, g_mV);   // ���[���h���W�n -> �r���[���W�n�֕ϊ�
    Out.Pos = mul(Out.Pos, g_mP);   // �r���[���W�n -> �ˉe���W�n�֕ϊ�

    // UV���W
    Out.UV = uv * g_UVTiling + g_UVOffset;

    // �F
    Out.Color = color;

    // �o��
    return Out;
}
