#pragma once
//#include"CSV.h"
class Scene;
class C_CharaPara
{
public:
	C_CharaPara() {}
	~C_CharaPara() {}

	void Init();

	//�G�l�~�[�������\���ǂ����̃t���O��n��
	bool GetCreatedChara() { return CreatedChara; }

	//�G�l�~�[�𐶐�����
	void SetCreatedChara(bool flg, int type);

	//�p�����[�^HP�Z�b�g
	void SetHp(int hp);

	//X���̔��a���Z�b�g
	void SetRadiusX(float radiusx);

	//Y���̔��a���Z�b�g
	void SetRadiusY(float radiusy);

	//X�����a�̃Q�b�^�[
	float GetRadiusX() { return RadiusX; }

	//Y�����a�̃Q�b�^�[
	float GetRadiusY() { return RadiusY; }

	//���W�̃Z�b�^�[�@�F�@���݈ʒu�ƃW�����v�̗L��
	void SetPos(Math::Vector2 pos, bool jump) { Pos = pos, Jump = jump; }

	//���W�̃Z�b�^�[�@�F�@���݈ʒu�ƃW�����v�̗L���ƈړ���
	void SetPos(Math::Vector2 pos, bool jump, Math::Vector2 move) { Pos = pos, Jump = jump, Move = move; }

	//���W�̃Z�b�^�[�@�F�@���ݍ��W�ƈړ���
	void SetPos(Math::Vector2 pos, Math::Vector2 move) { Pos = pos, Move = move; }

	//�������Ă邩�ǂ����̃Z�b�^�[�@�F�@�������Ă�t���O�ƃ_���[�W��
	void SetHit(bool hit, float damage);


	//�t���[���A�b�v�f�[�g�@�F�@�_���[�W����������̃t���[�����������Ă���
	void FrameUpdete();

	bool GetHit() { return Hit; }

	bool Getdamageframe() { return damageframe; }

	bool GetView() { return Viewflg; }


	Math::Vector2 GetPos() { return Pos; }

	Math::Vector2 GetMove() { return Move; }

	void SetAtkPower(float AtkPower);

	bool GetJump() { return Jump; }

	void SetFuturePos(Math::Vector2 pos, Math::Vector2 move) { Pos = pos, Move = move; }

	Math::Vector2 GetFuturePos() { return Pos + Move; }

	float  GettouchDamage() { return touchDamage; }	//�����Ƀ_���[�W�ƃv���C���[�Ȃ�W���u�ԍ��A�G�l�~�[�Ȃ�G�l�~�[�ԍ�

	void   SettouchDamage(float tuoch) { touchDamage = tuoch; }

	float  GetDamage() { return Damage; }					//�_���[�W

	float GetNumber() { return Number; }

	int GetType() { return Type; }

	void rannsuusyokika();

	int Getrannsuu() { return clitik; }

	int SetGetMoney(int money) { MoneyCount += money; }

	int GetMoney() { return MoneyCount; }

	void SetEXP(float pexp);

	float GetEXP() { return EXP; }

	void Levelcount();

	void SetLowAtkPow(float low) { LowAtk = low; }

	void SetHiAtkPow(float Hi) { HiAtk = Hi; }

	void SetPlayerAlive(bool flg) { PlayerAlive = flg; };

	bool GetPlayerAlive() { return PlayerAlive; }

	float GetHiAtk() { return HiAtk; }

	float GetLowAtk() { return LowAtk; }

	void Setclitelikaru(float cli) { clit = cli; }

	void Setdoroppubuff(int buf) { doroppu = buf; }

	float Getdoroppubuff() { return doroppu; }

	////�֐�
	int GetHp();		    //�̗͗p

	float Get_sAtk();	//�ߋ����U���͍��v�p


	float GetLevel() { return Lv; }		//���x���p

	void Setseveflg(bool flg) { saveflg = flg; }

	bool Getsaveflg() { return saveflg; }


private:
	static const int Atkp = 3;
	static const int CHp = 2;
	//static const int kaisinn = 2;
	bool CreatedChara = false;
	//��b�X�e�[�^�X
	int Hp;				//�̗�
	float Mhp[CHp];				//�ő�̗�
	float Mmp;				//�ő喂��
	float sAtk[Atkp];				//�ߋ����U����

	int doroppu;
	float lAtk;				//�������U����
	float mAtk;				//���@�U����

	static const int LvNum = 100;
	float clit;



	int  clitik;

	bool PlayerAlive;

	float LowAtk = 10;

	float HiAtk = 1000;



	bool saveflg;



	float Damage = 0;
	float touchDamage;
	int Number = 0;

	float Atkgoukei;

	float Lv;		//���x���@

	float exp;		//�o���l

	float EXP;

	int drop;					//�A�C�e���h���b�v

	int Type;
	float RadiusX;
	float RadiusY;
	bool Jump;
	bool Hit;
	bool Viewflg = true;
	int damageframe;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	C_CharaPara* CharaPara;
	//C_CSV csv;
	int MoneyCount = 0;

};
class  C_Para
{
public:

	static const int MapWidth = 64;
	static const int MapHeight = 12;

	void Init();
	void Update();
	void Draw();
	int CreateEnemy(float hp);
	void DeleteEnemy(int EnemyIndex);
	int EnemyDethCount = 0;


	int CreateAtkObject(int AtkPower, float radiusX, float radiusY);
	void DeleteAtkObject(int AtkIndex);

	C_CharaPara* GetPlayerPara() { return &PlayerPara; }
	C_CharaPara* GetEnemyPara(int Index) { return &EnemyPara[Index]; }
	C_CharaPara* GetAtkPara(int Index) { return &AtkPara[Index]; }
	C_CharaPara* GetMapPara(int h, int w) { return &MapPara[h][w]; }
	C_CharaPara* GetBackMapPara() { return &MapBackpara; }
	int GetAtkCount() { return Atkcount; }
	int GetEnemycount() { return Enemycount; }



private:
	static const int Enemycount = 10;
	static const int EnemyAtkcount = 100;
	static const int Atkcount = 100;
	C_CharaPara EnemyPara[Enemycount];
	C_CharaPara AtkPara[Atkcount];
	//C_CharaPara EnemyAtkPara[EnemyAtkcount];
	C_CharaPara PlayerPara;
	C_CharaPara MapPara[MapHeight][MapWidth];
	C_CharaPara MapBackpara;

	static const int hight = 300;
	static const int low = 500;
	static const int mobNum = 1000;

};