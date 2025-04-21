#pragma once

class C_Title
{
public:
	C_Title(){}
	~C_Title(){}

	void Init();
	void Update();
	void Draw();

private:
	KdTexture BackTex;
	Math::Matrix BackMat;
};