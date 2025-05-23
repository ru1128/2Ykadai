#pragma once

#include "SpriteFont.h"

//===================================================
//
// 2D描画シェーダ
//
//===================================================
class KdSpriteShader {
public:

	struct Vertex
	{
		Math::Vector3 Pos;
		Math::Vector2 UV;
	};

	//===========================================
	// 初期化・解放
	//===========================================

	// 初期化
	bool Init();

	// 解放
	void Release();

	// 
	~KdSpriteShader() {
		Release();
	}

	//===========================================
	//
	// 描画系
	//
	//===========================================

	// 描画開始
	// ステートの記憶・変更や、2D描画用の行列の設定、シェーダ切り替えなどを行う
	// ・linear			… 線形補間モードにする
	// ・disableZBuffer	… Zバッファを使用しない
	void Begin(bool linear = false, bool disableZBuffer = true);

	// 描画終了
	//  Begin()で記憶していたステートを復元 
	void End();

	// 変換行列セット
	void SetMatrix(const Math::Matrix& m)
	{
		m_cb0.Work().mTransform = m;
	}

	// 2D画像描画(Begin〜End間で実行すると、処理効率が上がる)
	// ・tex			… 描画するテクスチャ(Texture)
	// ・x				… x座標(ピクセル)
	// ・y				… y座標(ピクセル)
	// ・w				… w座標(ピクセル)
	// ・h				… h座標(ピクセル)
	// ・srcRect		… 元画像のRECT nullptrで全体
	// ・color			… 色(RGBA) nullptrで色はセットしない(前回の描画時の色が使用される)
	// ・pivot			… 基準点 0.0〜1.0の範囲で指定する
	void DrawTex(const KdTexture* tex, int x, int y, int w, int h, const Math::Rectangle* srcRect = nullptr, const Math::Color* color = &Math::Color(1, 1, 1, 1), const Math::Vector2& pivot = { 0.5, 0.5f });

	// 2D画像描画(Begin〜End間で実行すると、処理効率が上がる)
	// 幅と高さはtexの情報が使用される
	// ・tex			… 描画するテクスチャ(Texture)
	// ・x				… x座標(ピクセル)
	// ・y				… y座標(ピクセル)
	// ・srcRect		… 元画像のRECT
	// ・color			… 色(RGBA)
	// ・pivot			… 基準点 0.0〜1.0の範囲で指定する
	void DrawTex(const KdTexture* tex, int x, int y, const Math::Rectangle* srcRect = nullptr, const Math::Color* color = &Math::Color(1, 1, 1, 1), const Math::Vector2& pivot = { 0.5, 0.5f })
	{
		if (tex == nullptr)return;
		DrawTex(tex, x, y, srcRect->width, srcRect->height, srcRect, color, pivot);
	}

	//４・５月の授業用シンプル版
	void DrawTex(const KdTexture* tex, const Math::Rectangle& srcRect = { 0,0,0,0 }, const float alpha = 1.0f, const Math::Vector2& pivot = { 0.5, 0.5f })
	{
		if (tex == nullptr)return;
		DrawTex(tex, 0, 0, srcRect.width, srcRect.height, &srcRect, &Math::Color(1, 1, 1, alpha), pivot);
	}

	//色変更用
	void DrawTex_Color(const KdTexture* tex, const Math::Rectangle& srcRect = { 0,0,0,0 }, const Math::Color& color = { 1,1,1,1 }, const Math::Vector2& pivot = { 0.5, 0.5f })
	{
		if (tex == nullptr)return;
		DrawTex(tex, 0, 0, srcRect.width, srcRect.height, &srcRect, &color, pivot);
	}

	//４・５月の授業用文字表示
	void DrawString(float _x, float _y, const char _text[], const Math::Vector4& _color)
	{
		//ワイド文字列に変換する必要がある
		WCHAR *_wtext = new WCHAR[strlen(_text) + 1];
		mbstowcs_s(nullptr, _wtext, strlen(_text) + 1, _text, _TRUNCATE);

		//Begin前のBlendStateを取得
		ID3D11BlendState *oldBlendState = 0;
		float oldFactor[4];
		UINT oldMask = 0;
		D3D.GetDevContext()->OMGetBlendState(&oldBlendState, oldFactor, &oldMask);

		//BlendStateを引き継いでBegin
		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, oldBlendState);
		spriteFont->DrawString(spriteBatch, _wtext, Math::Vector2(_x + 640, -_y + 360), _color);
		spriteBatch->End();

		//Begin前のBlendStateを復元
		D3D.GetDevContext()->OMSetBlendState(oldBlendState, oldFactor, oldMask);

		//一時取得したBlendStateを解放 (解放しないと参照カウントが減らない)
		KdSafeRelease(oldBlendState);
		
		delete[] _wtext;
	}


	// 点を描画
	// ・x				… 点のX座標
	// ・y				… 点のY座標
	// ・color			… 色(RGBA)
	void DrawPoint(int x, int y, const Math::Color* color = &Math::Color(1, 1, 1, 1));

	// 2D線を描画
	// ・x1				… 点１のX座標
	// ・y1				… 点１のY座標
	// ・x2				… 点２のX座標
	// ・y2				… 点２のY座標
	// ・color			… 色(RGBA)
	void DrawLine(int x1, int y1, int x2, int y2, const Math::Color* color = &Math::Color(1, 1, 1, 1));

	// 三角形を描画
	// ・x1				… 座標１のX座標
	// ・y1				… 座標１のY座標
	// ・x2				… 座標２のX座標
	// ・y2				… 座標２のY座標
	// ・x3				… 座標３のX座標
	// ・y3				… 座標３のY座標
	// ・fill			… 塗りつぶし
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Math::Color* color = &Math::Color(1, 1, 1, 1), bool fill = true);

	// 2D円を描画
	// ・x				… 円の中心座標のX座標
	// ・y				… 円の中心座標のY座標
	// ・radius			… 円の半径
	// ・color			… 色(RGBA)
	// ・fill			… 塗りつぶし
	void DrawCircle(int x, int y, int radius, const Math::Color* color = &Math::Color(1, 1, 1, 1), bool fill = true);

	// 2D箱を描画
	// ・x				… 箱の中心座標のX座標
	// ・y				… 箱の中心座標のY座標
	// ・extentX		… 箱のX方向のハーフサイズ
	// ・extentY		… 箱のY方向のハーフサイズ
	// ・color			… 色(RGBA)
	// ・fill			… 塗りつぶし
	void DrawBox(int x, int y, int extentX, int extentY, const Math::Color* color = &Math::Color(1, 1, 1, 1), bool fill = true);

	// 切り抜き範囲を設定する
	// ・rect			… 範囲
	void SetScissorRect(const Math::Rectangle& rect)
	{
		D3D.SetRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, true, true);
		D3D11_RECT rc;
		rc.left = rect.x;
		rc.top = rect.y;
		rc.right = rect.x + rect.width;
		rc.bottom = rect.y + rect.height;
		D3D.GetDevContext()->RSSetScissorRects(1, &rc);
	}

private:

	ID3D11VertexShader*		m_VS = nullptr;				// 頂点シェーダー
	ID3D11InputLayout*		m_VLayout = nullptr;		// 頂点レイアウト

	ID3D11PixelShader*		m_PS = nullptr;				// ピクセルシェーダー

	// 定数バッファ
	struct cbSprite {
		Math::Matrix		mTransform;
		Math::Vector4		Color = { 1, 1, 1, 1 };
	};
	KdConstantBuffer<cbSprite>	m_cb0;

	// 定数バッファ
	struct cbProjection {
		Math::Matrix		mProj;
	};
	KdConstantBuffer<cbProjection>	m_cb1;

	// Flag
	bool					m_isBegin = false;

	// 2D用正射影行列
	Math::Matrix			m_mProj2D;

	// 使用するステート
	ID3D11DepthStencilState*	m_ds = nullptr;
	ID3D11RasterizerState*		m_rs = nullptr;
	ID3D11SamplerState*			m_smp0_Point = nullptr;
	ID3D11SamplerState*			m_smp0_Linear = nullptr;

	// ステート記憶/復元用
	struct SaveState {
		ID3D11DepthStencilState*	DS = nullptr;
		ID3D11RasterizerState*		RS = nullptr;
		UINT						StencilRef = 0;
		ID3D11SamplerState*			Smp0 = nullptr;
	};
	SaveState					m_saveState;

	DirectX::SpriteBatch* spriteBatch;	//フォント表示用
	DirectX::SpriteFont* spriteFont;//フォントデータ
};
