#pragma once

//===========================================
//
// �Z�k��
//
//===========================================

// ComPtr�Z�k��
using Microsoft::WRL::ComPtr;

// �Z�p�n�Z�k��
namespace Math = DirectX::SimpleMath;

// �p�x�ϊ�
inline constexpr float ToRadians(float fDegrees) { return fDegrees * (3.141592654f / 180.0f); }
inline constexpr float ToDegrees(float fRadians) { return fRadians * (180.0f / 3.141592654f); }

// ���S��Release���邽�߂̊֐�
template<class T>
void KdSafeRelease(T*& p)
{
	if (p)
	{
		ULONG c = p->Release();
		p = nullptr;
	}
}

// ���S��Delete���邽�߂̊֐�
template<class T>
void KdSafeDelete(T*& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

// �t�@�C���p�X����A�e�f�B���N�g���܂ł̃p�X���擾
inline std::string KdGetDirFromPath(const std::string &path)
{
	const std::string::size_type pos = std::max<signed>(path.find_last_of('/'), path.find_last_of('\\'));
	return (pos == std::string::npos) ? std::string() : path.substr(0, pos + 1);
}

// RECT�\���̂̒ǉ��@�\�o�[�W����
struct KdRect : public RECT
{
	KdRect() {
		left = top = right = bottom = 0;
	}

	KdRect(const RECT& rc)
	{
		*this = rc;
	}

	KdRect(LONG left, LONG top, LONG right, LONG bottom)
	{
		SetRect(this, left, top, right, bottom);
	}

};


