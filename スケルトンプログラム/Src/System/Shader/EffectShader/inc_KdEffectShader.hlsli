
//===========================================
//
// �萔�o�b�t�@
//  �Q�[���v���O���������玝���Ă���f�[�^
//
//===========================================

// �萔�o�b�t�@(�I�u�W�F�N�g�P�ʍX�V)
cbuffer cbPerObject : register(b0)
{
    // �I�u�W�F�N�g���
    row_major float4x4 g_mW; // ���[���h�ϊ��s��

    // UV�֌W
    float2 g_UVOffset;
    float2 g_UVTiling;
};


//===========================================
// ���_�V�F�[�_����o�͂���f�[�^
//===========================================
struct VSOutput
{
    float4 Pos : SV_Position;   // �ˉe���W
    float2 UV : TEXCOORD0;      // UV���W
    float4 Color : TEXCOORD1;   // �F
};
