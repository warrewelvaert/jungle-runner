#pragma once
#include "pch.h"
#include "Texture.h"
#include "Vector2f.h"
#include "utils.h"

class Spider
{
public:
	Spider(Point2f startPoint);
	~Spider();
	Spider(const Spider& other);

	void Draw() const;
	void Update(float elapsedSec);
	void WalkPattern(float elapsedSec);
	Rectf GetShape() const;

private:
	Texture m_SpiderTexture;
	Point2f m_StartPoint;
	float m_RightPoint;
	Rectf m_Shape;
	Rectf m_SrcRect;
	bool m_MoveRight{ true };

	const float m_Speed{ 150.0f };
	Vector2f m_Velocity;

	const int m_NrOfFrames{ 6 };
	const int m_NrOfFramesPerSec{ 10 };
	float m_AnimTime{ 0.0f };
	int m_AnimFrame{ 0 };

	void SetTextureRect();
	void ChangeAnimFrame();
};

