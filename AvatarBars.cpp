#include "pch.h"
#include "AvatarBars.h"

AvatarBars::AvatarBars()
	: m_EmptyBars{ "./Resources/Images/EmptyBars.png" }
	, m_HealthManaBars{ "./Resources/Images/HealthManaBars.png" }
	, m_HealthSrcRect{ 0.f, m_HealthManaBars.GetHeight() / 2, m_HealthManaBars.GetWidth(), m_HealthManaBars.GetHeight() / 2 }
	, m_ManaSrcRect{ 0.f, 0.f, m_HealthManaBars.GetWidth(), m_HealthManaBars.GetHeight() / 2 }
	, m_HealthDestRect{ 31.f, 572.f, m_HealthManaBars.GetWidth(), m_HealthManaBars.GetHeight() / 2 }
	, m_ManaDestRect{ 31.f, 534.f, m_HealthManaBars.GetWidth(), m_HealthManaBars.GetHeight() / 2 }
{
}

AvatarBars::~AvatarBars()
{
}

void AvatarBars::Update(Rectf cameraRect, Avatar* avatarObj)
{
	Rectf tempRect{ cameraRect.left + 31.0f, cameraRect.bottom + cameraRect.height - 28.f, m_HealthManaBars.GetWidth(), m_HealthManaBars.GetHeight() / 2 };
	m_HealthDestRect = tempRect;
	m_ManaDestRect = tempRect;
	m_ManaDestRect.bottom = cameraRect.bottom + cameraRect.height - 64.f;

	if (avatarObj->GetPowerStatus() == false)
	{
		m_ManaDestRect.width = 0.1f;	
	}
	else
	{
		m_ManaDestRect.width *= 1 - avatarObj->GetPowerTime();
	}
	m_HealthDestRect.width *= avatarObj->GetHealth();
}

void AvatarBars::Draw(Rectf cameraRect) const
{
	m_EmptyBars.Draw( Point2f{ cameraRect.left + 7.f, cameraRect.bottom + cameraRect.height - 70.f } );
	m_HealthManaBars.Draw(m_HealthDestRect, m_HealthSrcRect);
	m_HealthManaBars.Draw(m_ManaDestRect, m_ManaSrcRect);
}