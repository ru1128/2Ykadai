#include "Parameter.h"
//‰Šú‰»
void C_Para::Init()
{

}
//XV
void C_Para::Update()
{
}
void C_Para::Draw()
{




}
int C_Para::CreateEnemy(float hp)
{
	for (int i = 0; i < Enemycount; i++)
	{
		bool EnemyFlg = EnemyPara[i].GetCreatedChara();
		if (EnemyFlg == false)
		{
			EnemyPara[i].SetCreatedChara(true, 2);
			EnemyPara[i].SetHp(hp);
			return i;
		}


	}


	return-1;
}

void C_CharaPara::SetHp(int hp)
{
	Hp = hp;
}
void C_CharaPara::SetRadiusX(float radiusx)
{
	RadiusX = radiusx;
}
void C_CharaPara::SetRadiusY(float radiusy)
{
	RadiusY = radiusy;
}
void C_CharaPara::SetHit(bool hit, float damage)
{
	if (hit == true && Hit == false)
	{
		Hit = hit;
		damageframe = 40;
	}
}
void C_CharaPara::FrameUpdete()

{
	if ((damageframe % 5) == 1)
	{
		Viewflg = !Viewflg;

	}
	if (damageframe > 0)damageframe--;
	if (damageframe == 0)
	{
		Hit = false;
		Viewflg = true;
	}


}

void C_CharaPara::SetAtkPower(float AtkPower)
{

	sAtk[0] = AtkPower;

}




void C_CharaPara::rannsuusyokika()
{
	srand(time(NULL));
}



void C_CharaPara::SetEXP(float pexp)
{
	exp = pexp;

	EXP += exp;


}

void C_CharaPara::Levelcount()
{

	if (EXP > 100)
	{
		Lv += 1;
		EXP = 0;
	}
	else
	{
		return;
	}


}


int C_CharaPara::GetHp()
{

	if ((Mhp[0] + Mhp[1]) < Hp)
	{

		Hp = Mhp[0] + Mhp[1];
	}


	return Hp;
}

float C_CharaPara::Get_sAtk()
{



	Atkgoukei = sAtk[0] + (sAtk[1] * sAtk[2]);
	if (Atkgoukei < LowAtk)
	{
		return LowAtk;
	}

	if (Atkgoukei > HiAtk)
	{
		return HiAtk;
	}
	return Atkgoukei;
}


void C_CharaPara::Init()
{

	Mhp[0] = 0;
	Mhp[1] = 0;
	srand(time(NULL));

}

void C_CharaPara::SetCreatedChara(bool flg, int type)
{
	CreatedChara = flg;
	Type = type;
}

void C_Para::DeleteEnemy(int EnemyIndex)
{

	EnemyPara[EnemyIndex].SetCreatedChara(false, 0);
	EnemyDethCount++;

}
int C_Para::CreateAtkObject(int AtkPower, float radiusX, float radiusY)
{
	for (int i = 0; i < Atkcount; i++)
	{
		bool AtkFlg = AtkPara[i].GetCreatedChara();
		if (AtkFlg == false)
		{
			AtkPara[i].SetCreatedChara(true, 1);
			AtkPara[i].SetAtkPower(AtkPower);
			AtkPara[i].SetRadiusX(radiusX);
			AtkPara[i].SetRadiusY(radiusY);


			return i;
		}
	}
	return -1;
}

void C_Para::DeleteAtkObject(int AtkIndex)
{
	AtkPara[AtkIndex].SetCreatedChara(false, 0);
}
