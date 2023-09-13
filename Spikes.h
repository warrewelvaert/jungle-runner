#pragma once
#include "pch.h"
#include "Texture.h"
#include "utils.h"

class Spikes
{
public:
	Spikes(Point2f botLeftPos);
	~Spikes();
	Spikes(const Spikes& other);
	Rectf GetShape() const;
	void Draw() const;

private:
	Texture m_SpikesTexture;
	const Rectf m_Shape;
};

