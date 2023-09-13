#pragma once
#include "pch.h"
#include "Texture.h"
#include "utils.h"

class Projectile
{
public:
	Projectile(Point2f botLeft);
	~Projectile();
	Projectile(const Projectile& other);
	void Draw() const;
	Rectf GetShape() const;
	void MoveRight(float elapsedSec);
	void MoveLeft(float elapsedSec);

private:
	Texture m_ProjTexture;
	Point2f m_StartPos;
	const float m_Speed{ 100.0f };
	Point2f m_Velocity;
	Rectf m_Shape;
};

