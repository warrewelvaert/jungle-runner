#pragma once
#include "pch.h"
#include "Texture.h"
#include "Vector2f.h"
#include "Level.h"
#include "SoundEffect.h"
#include "utils.h"

class Avatar
{
public:
	enum ActionState
	{
		waiting,
		moving,
		dead
	};

	Avatar();
	~Avatar();
	Avatar(const Avatar& other);

	void Draw() const;
	void Update(Level& level, float elapsedSec);
	bool GetPowerStatus() const;
	Rectf GetShape() const;
	float GetPowerTime() const;
	float GetHealth() const;
	void Empower();
	void Kill();
	void Respawn();


private:
	// Variables
	Texture m_AvatarTexture;
	Texture m_AvatarPoweredTexture;
	Rectf m_Shape{ 300.f, 200.0f, 46.0f, 68.0f};
	Rectf m_SrcRect;
	const float m_ClipWidth{ m_AvatarTexture.GetWidth() / 12 };
	const float m_ClipHeight{ m_AvatarTexture.GetHeight() / 5 };

	ActionState m_ActionState{ ActionState::waiting };
	bool m_IsPowered{ false };
	float m_PowerUpTime{ 0.0f };
	float m_PowerUpDuration{ 5.0f };
	bool m_IsJumping{ false };
	float m_Health{ 1.0f };
	const float m_HorSpeed{ 300.0f };
	const float m_JumpVel{ 9.f };
	Vector2f m_Velocity{ 0.0f, 0.0f };

	const int m_NrOfIdleFrames{ 12 };
	const int m_NrOfIMovingFrames{ 8 };
	const int m_NrOfFramesPerSec{ 10 };
	float m_AnimTime{0.0f};
	int m_AnimFrame;

	const SoundEffect m_JumpSound;

	// Functions
	void HandleMovement(float elapsedSec);
	void SetTextureRect();
	void ChangeAnimFrame();
	void CoundownPower(float elapsedTime);
};

