#include "pch.h"
#include "Bat.h"

Bat::Bat(Point2f startPos)
	: m_BatTexture{ "./Resources/Images/BatSprite.png" }
	, m_StartPos{ startPos }
{
	m_Shape.left = startPos.x;
	m_Shape.bottom = startPos.y;
}

Bat::~Bat()
{
}

Bat::Bat(const Bat& other)
	: m_BatTexture{ "./Resources/Images/BatSprite.png" }
	, m_StartPos{ other.m_StartPos }
	, m_Shape{ other.m_Shape }
{
}

void Bat::Update(float elapsedSec, const Rectf& avatarRect)
{
	m_AnimTime += elapsedSec;
	ChangeAnimFrame();
	SetTextureRect();

	Point2f avatarCenter{ avatarRect.left + avatarRect.width / 2, avatarRect.bottom + avatarRect.height / 2 };
	float avatarDistance{ float(sqrt(pow(avatarCenter.x - m_CenterPos.x, 2) + pow(avatarCenter.y - m_CenterPos.y, 2))) };
	Point2f batPos{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2 };

	if (avatarDistance <= m_Range)
	{
		MoveToAvatar(elapsedSec, avatarRect);
	}
	else if (batPos.x != m_CenterPos.x)
	{
		MoveToStart(elapsedSec, avatarRect);
	}
}

void Bat::Draw() const
{
	m_BatTexture.Draw(m_Shape, m_SrcRect);
}

void Bat::MoveToAvatar(float elapsedSec, Rectf avatarPos)
{
	Point2f avatarCenter{ avatarPos.left + avatarPos.width / 2, avatarPos.bottom + avatarPos.height / 2 };
	Point2f batPos{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2 };

	if (batPos.x < avatarCenter.x)
	{
		m_Velocity.x = m_Speed * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
	else
	{
		m_Velocity.x = -m_Speed * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
}

void Bat::MoveToStart(float elapsedSec, Rectf avatarPos)
{
	Point2f batCurrentPos{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2 };
	Rectf startShape{ m_StartPos.x - m_Width / 4, m_StartPos.y - m_Height / 4, m_Width / 2, m_Height / 2 };
	Rectf currentShape{ batCurrentPos.x - m_Width / 4, batCurrentPos.y - m_Height / 4, m_Width / 2, m_Height / 2 };

	if (batCurrentPos.x < m_StartPos.x)
	{
		m_Velocity.x = m_Speed/2 * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
	else
	{
		m_Velocity.x = -m_Speed/2 * elapsedSec;
		m_Shape.left += m_Velocity.x;
	}
}

void Bat::SetTextureRect()
{
	m_SrcRect.left = m_BatTexture.GetWidth() / 5 * m_AnimFrame;
	m_SrcRect.height = m_BatTexture.GetHeight();
	m_SrcRect.width = m_BatTexture.GetWidth() / 5;
}

void Bat::ChangeAnimFrame()
{
	if (m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
	{
		m_AnimTime = 0.0f;
		m_AnimFrame = ++m_AnimFrame % m_NrOfFrames;
	}
}

Rectf Bat::GetShape() const
{
	return m_Shape;
}

