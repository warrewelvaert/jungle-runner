#pragma once
#include "pch.h"
#include "Vector2f.h"
#include "Texture.h"
#include "utils.h"

class Platform
{
public:
	Platform(const Point2f& botLeft);
	~Platform();
	Platform(const Platform& other);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape);
	Rectf GetShape() const;

private:
	const Rectf m_Shape;
	Texture m_Texture;
	std::vector<Point2f> m_Vertices;
};

