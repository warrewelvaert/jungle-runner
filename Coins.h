#pragma once
#include "pch.h"
#include "Texture.h"
#include "utils.h"

class Coins
{
public:
	enum Type
	{
		coin = 1,
		ring = 5,
		gem = 10
	};

	Coins(Type coinType, Point2f botLeftPos);
	~Coins();
	Coins(const Coins& other);
	void Draw() const;
	Rectf GetShape() const;
	int GetValue();

private:
	int m_Value;
	Rectf m_Shape;
	Rectf m_SrcRect{ 0.0f, 0.0f, 16.0f, 16.0f };
	Texture m_CoinsTexture;
	Type m_Type;

	void SetSrcRect();
};

