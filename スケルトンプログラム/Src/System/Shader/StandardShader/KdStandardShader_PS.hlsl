#include "../inc_KdCommon.hlsli"
#include "inc_KdStandardShader.hlsli"

// �e�N�X�`��
Texture2D g_baseTex : register(t0);         // �x�[�X�J���[�e�N�X�`��
Texture2D g_emissiveTex : register(t1);     // �G�~�b�V�u�e�N�X�`��
Texture2D g_mrTex : register(t2);            // ���^���b�N/���t�l�X�e�N�X�`��


// �T���v��
SamplerState g_ss : register(s0);

/*
// Unity��Build-In Shader�ł̎�@
// Roughness����SpecularPower���Z�o
float RoughnessToSpecPower(float roughness)
{
    float trueRoughness = roughness * roughness; // �w�p�I�ɐ��������t�l�X�����߂�
    float sq = max(0.0001, trueRoughness * trueRoughness);
    float n = (2.0 / sq) - 2.0;
    // Roughness��1.0��NdotH���[���̏ꍇ�ɔ�������\���̂���pow(0,0)�̃P�[�X��h�~
    n = max(n, 0.0001);
    return n;
}
*/

//================================
// �s�N�Z���V�F�[�_
//================================
float4 main(VSOutput In) : SV_Target0
{
    // �J�����ւ̕���
    float3 vCam = g_CamPos - In.wPos;
    float camDist = length(vCam);       // �J���� - �s�N�Z������
    vCam = normalize(vCam);

    // �@�����K��
    float3 wN = normalize(In.wN);


    //------------------------------------------
    // �ގ��F
    //------------------------------------------

    float4 mr = g_mrTex.Sample(g_ss, In.UV);
    // ������
    float metallic = mr.b * g_Material.Metallic;
    // �e��
    float roughness = mr.g * g_Material.Roughness;


    // �ގ��̐F
    float4 baseColor = g_baseTex.Sample(g_ss, In.UV) * g_Material.BaseColor;

    //------------------------------------------
    //
    // ���C�e�B���O
    //
    //------------------------------------------
    // �ŏI�I�ȐF
    float3 color = 0;

    // ���C�g�L����
    if(g_LightEnable)
    {
        // �ގ��̊g�U�F�@������قǍގ��̐F�ɂȂ�A�����قǊg�U�F�͖����Ȃ�
        const float3 baseDiffuse = lerp(baseColor.rgb, float3(0, 0, 0), metallic);
        // �ގ��̔��ːF�@������قǌ��̐F�����̂܂ܔ��˂��A�����قǍގ��̐F�����
        const float3 baseSpecular = lerp(0.04, baseColor.rgb, metallic);

        //------------------
        // ���s��
        //------------------

        // Diffuse(�g�U��) ���K��Lambert���g�p
        {
            // ���̕����Ɩ@���̕����Ƃ̊p�x�������̋����ɂȂ�
            float lightDiffuse = dot(-g_DL_Dir, wN);
            lightDiffuse = saturate(lightDiffuse);  // �}�C�i�X�l��0�ɂ���@0(��)�`1(��)�ɂȂ�

            // ���K��Lambert
            lightDiffuse /= 3.1415926535;

            // ���̐F * �ގ��̊g�U�F
            color += (g_DL_Color * lightDiffuse) * baseDiffuse;
        }

        // Specular(���ːF) ���K��Blinn-Phong NDF���g�p
        {

            // ���˂������̋��������߂�

            // ���t�l�X����ABlinn-Phong�p��SpecularPower�����߂�
            // Call of Duty : Black Ops��FarCry3�ł̂ł̎�@���g�p
            // specPower = 2^(13*g)�@�O���X�lg = 0�`1��1�`8192�̃X�y�L�������x�����߂�
            // �Q�l�Fhttps://hanecci.hatenadiary.org/entry/20130511/p1
            float smoothness = 1.0 - roughness;         // ���t�l�X���t�]�����u���炩�v���ɂ���
            float specPower = pow(2, 13 * smoothness);  // 1�`8192

            // Unity��Build-In Shader�ł̎�@
            //float specPower = RoughnessToSpecPower(roughness);

            // Blinn-Phong NDF
            float3 H = normalize(-g_DL_Dir + vCam);
            float NdotH = saturate( dot(wN, H) ); // �J�����̊p�x��(0�`1)
            float spec = pow(NdotH, specPower);

            // ���K��Blinn-Phong
            spec *= ((specPower + 2) / (2 * 3.1415926535));
        
            // ���̐F * ���ˌ��̋��� * �ގ��̔��ːF * ���K���W��
            color += (g_DL_Color * spec) * baseSpecular;
        }


        //------------------
        // ����
        //------------------
        color += g_AmbientLight * baseColor.rgb;

        //------------------
        // �G�~�b�V�u
        //------------------
        color += g_emissiveTex.Sample(g_ss, In.UV).rgb * g_Material.Emissive;
    }
    // ���C�g������
    else
    {
        // �ގ��̐F�����̂܂܎g�p
        color = baseColor.rgb;
    }

    //------------------------------------------
    // �����t�H�O
    //------------------------------------------
    if (g_DistanceFogEnable)
    {
		// �t�H�O 1(�߂�)�`0(����)
        float f = saturate(1.0 / exp(camDist * g_DistanceFogDensity));
        // �K�p
        color.rgb = lerp(g_DistanceFogColor, color.rgb, f);
    }

    
    //------------------------------------------
    // �o��
    //------------------------------------------
    return float4(color, baseColor.a);

}
