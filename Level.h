#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2f.h"
#include "Platform.h"
#include "utils.h"
#include "SVGParser.h"

class Level
{
public:
	Level();
	~Level();
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape);

private:
	std::vector<std::vector<Point2f>> m_SVGVertices;
	Texture m_BackgroundTexture;
	std::vector<Platform> m_Platforms;

	bool HandlePlatformGround(const Rectf& actorShape);
	void InitPlatforms();
};

