#include "pch.h"
#include "Coins.h"

Coins::Coins(Type coinType, Point2f botLeftPos)
	:m_CoinsTexture{ "./Resources/Images/Coins.png" }
	, m_Type{ coinType }
	, m_Shape{ botLeftPos.x, botLeftPos.y, 60.f, 60.f }
 {
	SetSrcRect();
	m_Value = GetValue();
}

Coins::~Coins()
{
}

Coins::Coins(const Coins& other)
	:m_CoinsTexture{ "./Resources/Images/Coins.png" }
	, m_Type{ other.m_Type }
	, m_Shape{ other.m_Shape }
	, m_Value{ other.m_Value }
{
	SetSrcRect();
}

void Coins::Draw() const
{
	m_CoinsTexture.Draw(m_Shape, m_SrcRect);
}

int Coins::GetValue()
{
	switch (m_Type)
	{
	case Coins::coin:
		m_Value = 1;
		break;
	case Coins::ring:
		m_Value = 5;
		break;
	case Coins::gem:
		m_Value = 10;
		break;
	}
	return m_Value;
}

void Coins::SetSrcRect()
{
	switch (m_Type)
	{
	case Coins::coin:
		m_SrcRect = m_SrcRect;
		break;
	case Coins::ring:
		m_SrcRect.left = 16.0f;
		break;
	case Coins::gem:
		m_SrcRect.left = 32.0f;
		break;
	}
}

Rectf Coins::GetShape() const
{
	return m_Shape;
}
