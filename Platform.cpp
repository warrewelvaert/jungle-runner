#include "pch.h"
#include "Platform.h"

Platform::Platform(const Point2f& botLeft)
	:m_Texture{ "./Resources/Images/Platform.png" }
	, m_Shape{ botLeft.x, botLeft.y, 258.f, 48.f }
	, m_Vertices{ Point2f(m_Shape.left, m_Shape.bottom + m_Shape.height - 6.f), Point2f(m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height - 6.f) }
{
}

Platform::~Platform()
{
}

Platform::Platform(const Platform& other)
	:m_Texture{ "./Resources/Images/Platform.png" }
	, m_Shape{ other.m_Shape }
	, m_Vertices{ other.m_Vertices }
{
}

void Platform::Draw() const
{
	m_Texture.Draw(m_Shape);
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo;

	Point2f rayBot{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f	rayTop{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	if ( utils::Raycast(m_Vertices, rayTop,rayBot, hitInfo) )
	{
		if (actorVelocity.y > 0.0f)
		{
		}
		else if (actorShape.bottom + 20.f > m_Shape.bottom + m_Shape.height)
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0.0f;
		}
	}
}

bool Platform::IsOnGround(const Rectf& actorShape)
{
	utils::HitInfo hitInfo;

	Point2f rayBot{ actorShape.left + actorShape.width / 2, actorShape.bottom };
	Point2f	rayTop{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };

	if (utils::Raycast(m_Vertices, rayTop, rayBot, hitInfo))
	{
		return true;
	}
	return false;
}

Rectf Platform::GetShape() const
{
	return m_Shape;
}