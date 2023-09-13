#include "pch.h"
#include "Camera.h"

Camera::Camera(float width, float height)
	:m_Width{ width }
	, m_Height{ height }
	, m_Boundries{ 0.0f, 0.0f, width, height }
{
}

Camera::~Camera()
{
}

void Camera::SetLevelBoundries(const Rectf& levelBoundries)
{
	m_LevelBoundries = levelBoundries;
}

Point2f Camera::Track(const Rectf& target) const
{
	Point2f targetCenter{ target.left + target.width / 2.0f, target.bottom + target.height / 2.0f };
	return Point2f(targetCenter.x - m_Width / 2.0f, targetCenter.y - m_Height / 2.0f);
}

Point2f Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundries.left)
	{
		bottomLeftPos.x = m_LevelBoundries.left;
	}
	else if (bottomLeftPos.x + m_Width > m_LevelBoundries.width)
	{
		bottomLeftPos.x = m_LevelBoundries.width - m_Width;
	}
	if (bottomLeftPos.y < m_LevelBoundries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundries.bottom;
	}
	else if (bottomLeftPos.y + m_Height > m_LevelBoundries.height)
	{
		bottomLeftPos.y = m_LevelBoundries.height - m_Height;
	}
	return bottomLeftPos;
}

Rectf Camera::GetBoundries(const Rectf& target) 
{
	Point2f CameraPos{ Track(target) };
	CameraPos = Clamp(CameraPos);

	m_Boundries.left = CameraPos.x;
	m_Boundries.bottom = CameraPos.y;

	return m_Boundries;
}

void Camera::Transform(const Rectf& target) const
{
	Point2f CameraPos{ Track(target) };
	CameraPos = Clamp(CameraPos);

	glPushMatrix();
	glTranslatef(-CameraPos.x, -CameraPos.y, 0);
}