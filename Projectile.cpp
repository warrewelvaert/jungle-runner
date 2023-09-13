#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(Point2f botLeft)
	:m_StartPos{botLeft.x, botLeft.y}
	, m_ProjTexture{ "./Resources/Images/ProjectileSprite.png" }
	, m_Shape{ botLeft.x, botLeft.y, 15.f , 15.f } 
{
}

Projectile::~Projectile()
{
}

Projectile::Projectile(const Projectile& other)
	:m_Shape{other.m_Shape}
	, m_ProjTexture{ "./Resources/Images/ProjectileSprite.png" }
	, m_StartPos{other.m_StartPos}
{

}

void Projectile::Draw() const
{
	m_ProjTexture.Draw(m_Shape);
}

Rectf Projectile::GetShape() const
{
	return m_Shape;
}

void Projectile::MoveRight(float elapsedSec)
{
	m_Velocity.x = m_Speed * elapsedSec;
	m_Shape.left += m_Velocity.x;
}

void Projectile::MoveLeft(float elapsedSec)
{
	m_Velocity.x = m_Speed * elapsedSec;
	m_Shape.left -= m_Velocity.x;
}