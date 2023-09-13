#include "pch.h"
#include "Wizzard.h"

Wizzard::Wizzard(Point2f botLeft)
	:m_WizzardTex{ "./Resources/Images/TotemSprite.png" }
	, m_Shape{ botLeft.x, botLeft.y, 42.5f, 55.f }
{
	m_Projectile.push_back(Projectile{ Point2f(m_Shape.left, m_Shape.bottom + m_Shape.height / 2) });
}

Wizzard::~Wizzard()
{
}

Wizzard::Wizzard(const Wizzard& other)
	:m_WizzardTex{ "./Resources/Images/TotemSprite.png" }
	,m_Shape{other.m_Shape}
{
	m_Projectile.push_back(Projectile{ Point2f(m_Shape.left, m_Shape.bottom + m_Shape.height / 2) });
}

void Wizzard::Update(float elapsedSec, Rectf avatarRect)
{

	m_AnimTime += elapsedSec;
	m_FireTime += elapsedSec;

	ChangeAnimFrame();
	SetTextureRect(avatarRect);

	if (m_FireTime > m_CoolDown)
	{
		Shoot(avatarRect);
	}

	if (m_IsProjAlive)
	{
		if (m_FireRight)
		{
			m_Projectile[0].MoveRight(elapsedSec);
		}
		else
		{
			m_Projectile[0].MoveLeft(elapsedSec);
		}
	}
}

void Wizzard::Draw() const
{
	m_WizzardTex.Draw(m_Shape, m_SrcRect);
	if (m_IsProjAlive)
	{
		m_Projectile[0].Draw();
	}
}

void Wizzard::KillProjectile()
{
	m_IsProjAlive = false;
}

Rectf Wizzard::GetShape() const
{
	return m_Shape;
}

Rectf Wizzard::GetProjShape() const 
{
	return m_Projectile[0].GetShape();
}

void Wizzard::Shoot(Rectf avatarRect)
{
	m_IsProjAlive = true;
	m_FireTime = 0.0f;
	m_Projectile.pop_back();
	if (avatarRect.left > m_Shape.left + m_Shape.width / 2)
	{
		m_Projectile.push_back(Projectile{ Point2f(m_Shape.left + m_Width, m_Shape.bottom + m_Shape.height / 2) });
		m_FireRight = true;
	}
	else
	{
		m_Projectile.push_back(Projectile{ Point2f(m_Shape.left - m_Width / 2, m_Shape.bottom + m_Shape.height / 2) });
		m_FireRight = false;
	}
}

void Wizzard::SetTextureRect(Rectf avatarRect)
{
	Rectf tempRect{ 0.0f, m_WizzardTex.GetHeight() / 2, m_WizzardTex.GetWidth() / 8, m_WizzardTex.GetHeight() / 2 };
	if (avatarRect.left + avatarRect.width > m_Shape.left)
	{
		m_SrcRect = tempRect;
	}
	else
	{
		m_SrcRect = tempRect;
		m_SrcRect.bottom = 0.0f;
	}
	m_SrcRect.left = m_WizzardTex.GetWidth() / 8 * m_AnimFrame;
}

void Wizzard::ChangeAnimFrame()
{
	if (m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
	{
		m_AnimTime = 0.0f;
		m_AnimFrame = ++m_AnimFrame % m_NrOfFrames;
	}
}