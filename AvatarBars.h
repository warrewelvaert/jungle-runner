#pragma once
#include "pch.h"
#include "Texture.h" 
#include "Avatar.h"

class AvatarBars
{
public:
	AvatarBars();
	~AvatarBars();
	void Update(Rectf cameraRect, Avatar* avatarObj);
	void Draw(Rectf cameraRect) const;

private:
	Texture m_EmptyBars;
	Texture m_HealthManaBars;

	const Rectf m_HealthSrcRect;
	const Rectf m_ManaSrcRect;
	Rectf m_HealthDestRect;
	Rectf m_ManaDestRect;
};

