#pragma once
#include "Font.h"
#include "GameObject.h"

class FontRender : public GameObject
{
public:
	FontRender();
	~FontRender();

	/// <summary>
	/// フォントを設定する。
	/// </summary>
	/// <param name="font">フォント</param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_font.SetFont(font);
	}

	/// <summary>
	/// テキストを設定。
	/// </summary>
	/// <param name="text">文字列</param>
	/// <remarks>
	/// 枚フレーム呼ぶとめちゃんこおもい。
	/// </remarks>
	void SetText(const wchar_t* text)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//文字列が変わった。
			m_text = text;
		}
	}

	//void SetTexts(const char* text, int minuit, int second)
	//{
	//	if (wcscmp(m_text.c_str(), (wchar_t*)text) != 0) {
	//		m_text = (wchar_t*)std::printf(text, minuit, second);
	//		/*m_text = (wchar_t*)swprintf_s(text, minuit, second);*/
	//	}
	//}

	/// <summary>
	/// フォントの座標を指定する。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector2 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// フォントのスケールを指定する。
	/// </summary>
	/// <param name="scale">フォントのスケール</param>
	void SetScale(float  scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// フォントの回転を指定する
	/// </summary>
	/// <param name="rot">フォントの回転</param>
	/// <remarks>
	/// 単位はラジアン。
	/// </remarks>
	void SetRotation(float rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// フォントの色を指定する。
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(CVector4 color)
	{
		m_color = color;
	}

	/// <summary>
	/// フォントの描画処理の流れを作成
	/// </summary>
	void PostRender();

private:

	float m_rotation = 0.f;							//フォントの回転。(単位はラジアン)。
	float m_scale = 1.f;							//フォントの拡大率。

	CVector2 m_position = CVector2::Zero();			//フォントの座標。
	CVector2 m_pivot = { 0.5f,0.5f };				//フォントの基点。

	CVector4 m_color = CVector4::White();			//フォントの色。

	std::wstring m_text;							//テキスト。

	Font m_font;									//フォント。

};

