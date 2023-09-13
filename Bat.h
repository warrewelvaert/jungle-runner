#pragma once
#include "pch.h"
#include "Texture.h"
#include "utils.h"

class Bat
{
public:
	Bat(Point2f startPos);
	~Bat();
	Bat(const Bat& other);
	void Draw() const;
	Rectf GetShape() const;
	void Update(float elapsedSec, const Rectf& avatarRect);

private:
	const float m_Width{ 64.0f };
	const float m_Height{ 44.0f };
	Rectf m_Shape{ 0.0f, 0.0f, m_Width, m_Height };
	Rectf m_SrcRect;
	Texture m_BatTexture;
	float m_Range{ 300.0f };
	float m_Speed{ 100.0f };
	Point2f m_Velocity;
	Point2f m_StartPos;
	Point2f m_CenterPos{ m_StartPos.x + m_Width / 2, m_StartPos.y + m_Height / 2 };

	const int m_NrOfFrames{ 5 };
	const int m_NrOfFramesPerSec{ 10 };
	float m_AnimTime{ 0.0f };
	int m_AnimFrame{ 0 };

	void MoveToAvatar(float elapsedSec, Rectf avatarRect);
	void MoveToStart(float elapsedSec, Rectf avatarRect);
	void SetTextureRect();
	void ChangeAnimFrame();
};
