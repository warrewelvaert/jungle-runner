#pragma once
#include "pch.h"
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"

class Door
{
public:
	Door(Point2f doorPos, Point2f keyPos);
	~Door();
	void Update(Rectf& avatarRect);
	void Draw() const;
	bool GetKeyStatus() const;
	void ResetKet();
	bool IsDoorOpen() const;

private:
	Texture m_DoorTex;
	Texture m_KeyTex;
	const Rectf m_DoorShape;
	const Rectf m_KeyShape;
	bool m_HasKey{ false };
	bool m_IsOpen{ false };

	const SoundEffect m_Key;
	const SoundEffect m_YouWin;
};

