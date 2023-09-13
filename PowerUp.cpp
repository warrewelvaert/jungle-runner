#include "pch.h"
#include "PowerUp.h"

PowerUp::PowerUp(Point2f botLeftPos)
	:m_Shape{botLeftPos.x, botLeftPos.y, 50.0f, 50.0f}
	, m_Texture{ "./Resources/Images/Potion.png" }
{
}

PowerUp::~PowerUp()
{
}

PowerUp::PowerUp(const PowerUp& other)
	: m_Shape{ other.m_Shape }
	, m_Texture{ "./Resources/Images/Potion.png" }
{
}

Rectf PowerUp::GetShape() const
{
	return m_Shape;
}

void PowerUp::Draw() const
{
	m_Texture.Draw(m_Shape, m_SrcRect);
}