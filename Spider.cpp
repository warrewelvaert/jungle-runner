#include "pch.h"
#include "Spider.h"


Spider::Spider(Point2f startPoint)
	: m_SpiderTexture{ "./Resources/Images/SpiderSprite.png" }
	, m_StartPoint{ startPoint }
	, m_RightPoint{ startPoint.x + 500.0f }
	, m_Shape{m_StartPoint.x, m_StartPoint.y, 120.f, 50.f }
{
}

Spider::~Spider()
{
}

Spider::Spider(const Spider& other)
	: m_SpiderTexture{ "./Resources/Images/SpiderSprite.png" }
	, m_StartPoint{ other.m_StartPoint }
	, m_RightPoint{ other.m_RightPoint }
	, m_Shape{ other.m_Shape }
{
}

void Spider::Draw() const
{
	m_SpiderTexture.Draw(m_Shape, m_SrcRect);
}

void Spider::Update(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	ChangeAnimFrame();
	SetTextureRect();
	WalkPattern(elapsedSec);
}

void Spider::SetTextureRect()
{
	Rectf tempRect{0.0f, m_SpiderTexture.GetHeight() / 2, m_SpiderTexture.GetWidth() / 6, m_SpiderTexture.GetHeight() / 2 };
	if (m_Velocity.x >= 0)
	{
		m_SrcRect = tempRect;
	}
	else
	{
		m_SrcRect = tempRect;
		m_SrcRect.bottom = 0.0f;
	}
	m_SrcRect.left = m_SpiderTexture.GetWidth() / 6 * m_AnimFrame;
}

void Spider::ChangeAnimFrame()
{
	if (m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
	{
		m_AnimTime = 0.0f;
		m_AnimFrame = ++m_AnimFrame % m_NrOfFrames;
	}
}

void Spider::WalkPattern(float elapsedSec)
{
	if (m_MoveRight == true && m_Shape.left + m_Shape.width < m_RightPoint)
	{
		m_Velocity.x = m_Speed * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
	else if (m_MoveRight)
	{
		m_MoveRight = false;
	}
	else if (m_Shape.left < m_StartPoint.x)
	{
		m_MoveRight = true;
	}
	else
	{
		m_Velocity.x = -m_Speed * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
}

Rectf Spider::GetShape() const
{
	return m_Shape;
}

