#pragma once
#include"Application/Parameter/Parameter.h"
struct eBullet
{
	Math::Vector2 m_pos, m_move;
	float m_size, m_speed;
	Math::Rectangle m_srcRect;
	Math::Color m_color;
	int m_count;
	bool m_alive;
	Math::Matrix m_scale, m_rotate, m_trans, m_mat;
};

class C_Boss
{
public:
	C_Boss(){}
	~C_Boss(){}

	void Init();
	void Update();
	void Action();
	void Draw();
	void SetTex(KdTexture* a_eTex) { eTex = a_eTex; }
	void SetAtkTex(KdTexture* a_bTex) { bTex = a_bTex; }

	void InitAtk();
	void DrawAtk();
	void UpdateAtk();

	Math::Vector2 GetAtk(int b) { return { bullet[b].m_pos.x,bullet[b].m_pos.y }; }
	float Rnd();
	float GetAngleDeg(float srcX, float srcY, float destX, float destY);//“G‚ª”ò‚Î‚·’e‚ÌŠp“x
	void SetOwner(Scene* hOwner) { m_pOwner = hOwner; }
	static const int GetBulletNum() { return bulletNum; }//“G‚Ì’e‚Ì”‚ğŒ©‚Ä‚¢‚é

	Math::Vector2 GetBulletPos(int b) { return { bullet[b].m_pos.x,bullet[b].m_pos.y }; }
	float GetBulletRadius() { return 32.0f; }	//player‚Ì‹Ê‚Ì‘å‚«‚³‚É‰‚¶‚ÄŒã‚Å•ÏX‚·‚é‚±‚Æ!

	bool GetAtkAliveFlg(int b) { return bullet[b].m_alive; }
	void SetBullet(int b, bool Flg) { bullet[b].m_alive = Flg; }


	void Create(C_Para* para);

private:
	const float moveSpeed = 30;
	Math::Vector2 pos, move;
	Math::Matrix trans, rotation, scale, mat;
	Math::Rectangle rect;
	float rectNum;
	bool aliveFlg;

	KdTexture* eTex;
	KdTexture* bTex;

	static const int bulletNum = 2;
	struct eBullet bullet[bulletNum];
	static const int CTMax = 300;

	float a, b, c, deg;
	int Flg = 0;

	static const int Left = -640;
	static const int Right = 640;
	static const int Top = 360;
	static const int Bottom = -360;

	static const int shotInterval = 5;
	int keyCount = 0;
	Scene* m_pOwner;

	float TargetRange = 300.0f;


	C_Para* m_para;

};