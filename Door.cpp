#include "pch.h"
#include "Door.h"

Door::Door(Point2f doorPos, Point2f keyPos)
	: m_DoorTex{ "./Resources/Images/Door.png" }
	, m_KeyTex{ "./Resources/Images/Key.png" }
	, m_Key{ "./Resources/Audio/key.ogg" }
	, m_YouWin{ "./Resources/Audio/win.wav" }
	, m_DoorShape{ doorPos.x , doorPos.y, m_DoorTex.GetWidth() / 2, m_DoorTex.GetHeight() }
	, m_KeyShape{ keyPos.x, keyPos.y, m_KeyTex.GetWidth(), m_KeyTex.GetHeight() }
{
}

Door::~Door()
{
}

void Door::Draw() const
{
	Rectf doorSrc{ 0.0f, 0.0f, m_DoorShape.width, m_DoorShape.height };

	if (m_IsOpen == false)
	{
		doorSrc.left += doorSrc.width;
	}
	m_DoorTex.Draw(m_DoorShape, doorSrc);

	if (m_HasKey == false)
	{
		m_KeyTex.Draw(m_KeyShape);
	}
}

void Door::Update(Rectf& avatarRect)
{
	if (utils::IsOverlapping(avatarRect, m_KeyShape) && m_HasKey == false)
	{
		m_HasKey = true;
		m_Key.Play(0);
	}

	if (utils::IsOverlapping(avatarRect, m_DoorShape) && m_HasKey == true)
	{
		m_IsOpen = true;
		Mix_HaltMusic();
		m_YouWin.Play(0);
	}
}

bool Door::GetKeyStatus() const
{
	return m_HasKey;
}

void Door::ResetKet()
{
	m_HasKey = false;
}

bool Door::IsDoorOpen() const
{
	return m_IsOpen;
}