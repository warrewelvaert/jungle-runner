#pragma once
#include "pch.h"
#include "utils.h"

class Camera
{
public:
	Camera(float width, float height);
	~Camera();
	void SetLevelBoundries(const Rectf& levelBoundries);
	void Transform(const Rectf& target) const;
	Rectf GetBoundries(const Rectf& target);

private:
	const float m_Width;
	const float m_Height;
	Rectf m_LevelBoundries;
	Rectf m_Boundries;

	Point2f Track(const Rectf& target) const;
	Point2f Clamp(Point2f& bottomLeftPos) const;
};
