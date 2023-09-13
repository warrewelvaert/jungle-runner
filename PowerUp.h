#pragma once
#include "pch.h"
#include "Texture.h"

class PowerUp
{
public:
	PowerUp(Point2f botLeftPos);
	~PowerUp();
	PowerUp(const PowerUp& other);
	Rectf GetShape() const;
	void Draw() const;

private:
	const Rectf m_Shape;
	Texture m_Texture;
	const Rectf m_SrcRect{ 0, 0, 16, 16 };
};

