#pragma once
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "Projectile.h"
#include <vector>
#include <iostream>

class Wizzard
{
public:
	Wizzard(Point2f botLeft);
	~Wizzard();
	Wizzard(const Wizzard& other);
	void Update(float elapsedSec, Rectf avatarRect);
	void Draw() const;
	void KillProjectile();

	Rectf GetShape() const;
	Rectf GetProjShape() const;

private:
	Texture m_WizzardTex;
	const Rectf m_Shape;
	const float m_Width{ 42.5f };
	const float m_Height{ 55.0f };
	Rectf m_SrcRect;

	float m_AnimTime;
	const int m_NrOfFrames{ 8 };
	const int m_NrOfFramesPerSec{ 8 };
	int m_AnimFrame{ 0 };

	std::vector<Projectile> m_Projectile;
	bool m_IsProjAlive{ true };
	float m_FireTime;
	float m_CoolDown{ 3.0f };
	bool m_FireRight{ false };

	void Shoot(Rectf avatarRect);
	void SetTextureRect(Rectf avatarRect);
	void ChangeAnimFrame();
};

