#pragma once
//#include"CSV.h"
class Scene;
class C_CharaPara
{
public:
	C_CharaPara() {}
	~C_CharaPara() {}

	void Init();

	//エネミーが生成可能かどうかのフラグを渡す
	bool GetCreatedChara() { return CreatedChara; }

	//エネミーを生成する
	void SetCreatedChara(bool flg, int type);

	//パラメータHPセット
	void SetHp(int hp);

	//X軸の半径をセット
	void SetRadiusX(float radiusx);

	//Y軸の半径をセット
	void SetRadiusY(float radiusy);

	//X軸半径のゲッター
	float GetRadiusX() { return RadiusX; }

	//Y軸半径のゲッター
	float GetRadiusY() { return RadiusY; }

	//座標のセッター　：　現在位置とジャンプの有無
	void SetPos(Math::Vector2 pos, bool jump) { Pos = pos, Jump = jump; }

	//座標のセッター　：　現在位置とジャンプの有無と移動量
	void SetPos(Math::Vector2 pos, bool jump, Math::Vector2 move) { Pos = pos, Jump = jump, Move = move; }

	//座標のセッター　：　現在座標と移動量
	void SetPos(Math::Vector2 pos, Math::Vector2 move) { Pos = pos, Move = move; }

	//当たってるかどうかのセッター　：　当たってるフラグとダメージ量
	void SetHit(bool hit, float damage);


	//フレームアップデート　：　ダメージくらった時のフレーム処理をしている
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

	float  GettouchDamage() { return touchDamage; }	//引数にダメージとプレイヤーならジョブ番号、エネミーならエネミー番号

	void   SettouchDamage(float tuoch) { touchDamage = tuoch; }

	float  GetDamage() { return Damage; }					//ダメージ

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

	////関数
	int GetHp();		    //体力用

	float Get_sAtk();	//近距離攻撃力合計用


	float GetLevel() { return Lv; }		//レベル用

	void Setseveflg(bool flg) { saveflg = flg; }

	bool Getsaveflg() { return saveflg; }


private:
	static const int Atkp = 3;
	static const int CHp = 2;
	//static const int kaisinn = 2;
	bool CreatedChara = false;
	//基礎ステータス
	int Hp;				//体力
	float Mhp[CHp];				//最大体力
	float Mmp;				//最大魔力
	float sAtk[Atkp];				//近距離攻撃力

	int doroppu;
	float lAtk;				//遠距離攻撃力
	float mAtk;				//魔法攻撃力

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

	float Lv;		//レベル　

	float exp;		//経験値

	float EXP;

	int drop;					//アイテムドロップ

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