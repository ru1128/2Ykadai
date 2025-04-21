#include "Boss.h"

void C_Boss::Init()
{
	pos = { 0,0 };
	move = { 0,0 };
	aliveFlg = true;
	rect = { 0,0,32,32 };
	rectNum = 0;
}

void C_Boss::Update()
{
	Action();

	if (m_para->GetPlayerPara()->GetLevel() > 1)
	{
		UpdateAtk();
		if (m_para->GetPlayerPara()->GetLevel() > 10)
		{

		}
	}
}

void C_Boss::Action()
{
	if (!aliveFlg)
	{
		for (int i = 0; i < bulletNum; i++)
		{
			bullet[i].m_alive = false;
		}
		return;
	}
	move = { 0,0 };
	
	
	pos += move;
}

void C_Boss::Draw()
{
	if (!aliveFlg)return;

	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex_Color(eTex, rect, Math::Color{ 1,1,1,1 });
}

void C_Boss::InitAtk()
{
	if (!aliveFlg)return;
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i].m_size = 0;
		bullet[i].m_pos.x = pos.x;
		bullet[i].m_pos.y = pos.y;
		bullet[i].m_alive = false;
		bullet[i].m_count = 150 * (i + 1);
		bullet[i].m_speed = 15;

		bullet[i].m_srcRect = { 0,0,32,32 };
		bullet[i].m_color = { 1,1,1,1 };
	}
}

void C_Boss::DrawAtk()
{

}

void C_Boss::UpdateAtk()
{
}

float C_Boss::Rnd()
{
	return 0.0f;
}

float C_Boss::GetAngleDeg(float srcX, float srcY, float destX, float destY)
{
	return 0.0f;
}

void C_Boss::Create(C_Para* para)
{
	m_para = para;
	m_para->GetPlayerPara()->GetLevel();
}
