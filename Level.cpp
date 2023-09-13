#include "pch.h"
#include "Level.h"

Level::Level()
	:m_BackgroundTexture{ "./Resources/Images/Background.png" }
{
	SVGParser::GetVerticesFromSvgFile("./Resources/Level.svg", m_SVGVertices);
	InitPlatforms();
}	

Level::~Level()
{
}

void Level::Draw() const
{
	m_BackgroundTexture.Draw(Point2f(0, 0));
	for (Platform i : m_Platforms)
	{
		i.Draw();
	}
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo;
	float offset{ 10.f };

	Point2f rayRightBot{ actorShape.left + actorShape.width - offset, actorShape.bottom };
	Point2f	rayRightTop{ actorShape.left + actorShape.width - offset, actorShape.bottom + 20.f };

	Point2f rayLeftBot{ actorShape.left + offset + 2.f, actorShape.bottom  };
	Point2f	rayLeftTop{ actorShape.left + offset + 2.f, actorShape.bottom + 20.f };
	
	Point2f rayLeft{ actorShape.left + offset, actorShape.bottom + offset - 9};
	Point2f rayRight{ actorShape.left + actorShape.width - offset, actorShape.bottom + offset - 9};

	if (utils::Raycast(m_SVGVertices[0], rayRight, rayLeft, hitInfo))
	{
		if (actorVelocity.x > 0.0f)
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width + 10.f;
		}
		else
		{
			actorShape.left = hitInfo.intersectPoint.x - 10.f;
		}
	}
	if (utils::Raycast(m_SVGVertices[0], rayRightBot, rayRightTop, hitInfo) || utils::Raycast(m_SVGVertices[0], rayLeftBot, rayLeftTop, hitInfo))
	{
		if (actorVelocity.y > 0.0f)
		{
		}
		else
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0.0f;
		}
	}

	for (Platform i : m_Platforms)
	{
		i.HandleCollision(actorShape, actorVelocity);
	}
}

bool Level::IsOnGround(const Rectf& actorShape)
{
	utils::HitInfo hitInfo;
	float offset{ 10.f };

	Point2f rayRightBot{ actorShape.left + actorShape.width - offset, actorShape.bottom - 1};
	Point2f	rayRightTop{ actorShape.left + actorShape.width - offset, actorShape.bottom + actorShape.height };

	Point2f rayLeftBot{ actorShape.left + offset + 2.f, actorShape.bottom - 1};
	Point2f	rayLeftTop{ actorShape.left + offset + 2.f, actorShape.bottom + actorShape.height };

	if (utils::Raycast(m_SVGVertices[0], rayRightBot, rayRightTop, hitInfo) || utils::Raycast(m_SVGVertices[0], rayLeftBot, rayLeftTop, hitInfo) 
		|| HandlePlatformGround(actorShape) )
	{
		return true;
	}
	return false;
}

bool Level::HandlePlatformGround(const Rectf& actorShape)
{
	for (Platform i : m_Platforms)
	{
		if (i.IsOnGround(actorShape))
		{
			return true;
		}
	}
	return false;
}

void Level::InitPlatforms()
{
	const float platHeigt{ 240.f };
	const float platFromGround{ 160.f };
	const float platWidth{ 258.f };

	const int nrOfPlat{ 11 };
	Platform platArray[nrOfPlat]{ Point2f(900.f, platHeigt), Point2f(900.f + platWidth, platHeigt + platFromGround), Point2f(1945.f , platHeigt + platFromGround / 2),
	Point2f(1945 + 2 * platWidth, platHeigt + platFromGround / 2), Point2f(7750.f, platHeigt), Point2f(7750.f + platWidth, platHeigt + platFromGround),
	Point2f(7750.f, platHeigt + platFromGround * 2), Point2f(12000.f, platHeigt), Point2f(12000.f + platWidth, platHeigt + platFromGround), Point2f(12000.f, platHeigt + platFromGround * 2),
	Point2f(12000.f + platWidth * 2, platHeigt + platFromGround * 2) };
	
	for (int i = 0; i < nrOfPlat; i++)
	{
		m_Platforms.push_back(platArray[i]);
	}
}
