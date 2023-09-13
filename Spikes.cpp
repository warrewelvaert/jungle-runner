#include "pch.h"
#include "Spikes.h"

Spikes::Spikes(Point2f botleftPos)
	:m_SpikesTexture{ "./Resources/Images/SpikesSprite.png" }
	, m_Shape{ botleftPos.x, botleftPos.y, 66.f, 34.f }
{
}

Spikes::~Spikes()
{
}

Spikes::Spikes(const Spikes& other)
	:m_SpikesTexture{ "./Resources/Images/SpikesSprite.png" }
	, m_Shape{ other.m_Shape }
{
}

void Spikes::Draw() const
{
	m_SpikesTexture.Draw(m_Shape);
}

Rectf Spikes::GetShape() const
{
	return m_Shape;
}