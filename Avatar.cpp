#include "pch.h"
#include "Avatar.h"

Avatar::Avatar()
	:m_AvatarTexture{ "./Resources/Images/AvatarSprite.png" } 
	, m_AvatarPoweredTexture{ "./Resources/Images/AvatarSpritePower.png" }
	, m_JumpSound{ "./Resources/Audio/jump.wav" }
{
}

Avatar::~Avatar()
{
}

Avatar::Avatar(const Avatar& other)
	:m_AvatarTexture{ "./Resources/Images/AvatarSprite.png" }
	, m_AvatarPoweredTexture{ "./Resources/Images/AvatarSpritePower.png" }
	, m_JumpSound{ "./Resources/Audio/jump.wav" }
	, m_IsPowered{ other.m_IsPowered }
	, m_PowerUpTime{ other.m_PowerUpTime }
	, m_Health{ other.m_Health }
{
}

void Avatar::Draw() const
{
	if (m_ActionState != ActionState::dead)
	{
		if (m_IsPowered)
		{
			m_AvatarPoweredTexture.Draw(m_Shape, m_SrcRect);
		}
		else
		{
			m_AvatarTexture.Draw(m_Shape, m_SrcRect);
		}
	}
}

void Avatar::Update(Level& level, float elapsedSec)
{
	if (m_ActionState == ActionState::dead)
	{
		m_Health -= 0.125f;
		Respawn();
	}
	else
	{
		m_AnimTime += elapsedSec;
		ChangeAnimFrame();
		SetTextureRect();

		if (m_IsPowered)
		{
			CoundownPower(elapsedSec);
		}

		const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

		if (m_ActionState == ActionState::moving)
		{
			if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_LEFT])
			{
				HandleMovement(elapsedSec);
			}
			else if (pStates[SDL_SCANCODE_UP] && level.IsOnGround(m_Shape) )
			{

				HandleMovement(elapsedSec);
			}
			else
			{
				m_ActionState = ActionState::waiting;
			}
		}
		else if (m_ActionState == ActionState::waiting)
		{
			if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_UP])
			{
				m_ActionState = ActionState::moving;
			}
		}
		m_Velocity.y += -19.41f * elapsedSec;
		m_Shape.bottom += m_Velocity.y;
		level.HandleCollision(m_Shape, m_Velocity);
	
	}
	m_IsJumping = !level.IsOnGround(m_Shape);
}

void Avatar::HandleMovement(float elapsedSec)
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Velocity.x = -m_HorSpeed * elapsedSec;
		m_Shape.left += m_Velocity.x;
		if (m_Shape.left < 0.0f)
		{
			m_Shape.left = 0.0f;
		}
	}
	else if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Velocity.x = m_HorSpeed * elapsedSec;
		m_Shape.left += m_Velocity.x;
		if (m_Shape.left + m_Shape.width > 12800.0f)
		{
			m_Shape.left = 12800.0f - m_Shape.width;
		}
	}
	if (pStates[SDL_SCANCODE_UP] && m_IsJumping == false && m_Velocity.y <= 0.f)
	{
		m_Velocity.y = m_JumpVel;
		m_Shape.bottom += m_Velocity.y;
		m_JumpSound.Play(0);
	}
}



void Avatar::SetTextureRect()
{
	Rectf tempRect{ 0.0f, m_ClipHeight, m_ClipWidth, m_ClipHeight };
	m_SrcRect = tempRect;

	if (m_IsJumping == true && m_Velocity.x >= 0.0f)
	{
		m_SrcRect.bottom = m_AvatarTexture.GetHeight() - m_ClipHeight;
		if (m_Velocity.y > 2.0f)
		{
			m_SrcRect.left = 0.0f;
		}
		else if (m_Velocity.y < -1.0f)
		{
			m_SrcRect.left = m_ClipWidth * 3;
		}
		else
		{
			m_SrcRect.left = m_ClipWidth * ((m_AnimFrame % 2) + 1);
		};
	}
	else if (m_IsJumping == true && m_Velocity.x < 0.0f)
	{
		m_SrcRect.bottom = m_AvatarTexture.GetHeight();
		if (m_Velocity.y > 2.0f)
		{
			m_SrcRect.left = 0.0f;
		}
		else if (m_Velocity.y < -1.0f)
		{
			m_SrcRect.left = m_ClipWidth * 3;
		}
		else
		{
			m_SrcRect.left = m_ClipWidth * ((m_AnimFrame % 2) + 1);
		};
	}
	else if (m_ActionState == ActionState::waiting)
	{
		m_SrcRect.left = m_ClipWidth * m_AnimFrame;
	}
	else if (m_Velocity.x > 0.0f)
	{
		m_SrcRect.bottom += m_ClipHeight;
		m_SrcRect.left = m_ClipWidth * (m_AnimFrame % 8);
	}
	else if (m_Velocity.x < 0.0f)
	{
		m_SrcRect.bottom += m_ClipHeight * 2;
		m_SrcRect.left = m_ClipWidth * (m_AnimFrame % 8);
	}
}

void Avatar::ChangeAnimFrame()
{
	if (m_ActionState == ActionState::moving)
	{
		if (m_AnimFrame > 8)
		{
			m_AnimFrame = 1;
		}
		if (m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
		{
			m_AnimTime = 0.0f;
			m_AnimFrame = ++m_AnimFrame % m_NrOfIMovingFrames;
		}
	}
	else if(m_AnimTime >= 1.0f / m_NrOfFramesPerSec)
	{
		m_AnimTime = 0.0f;
		m_AnimFrame = ++m_AnimFrame % m_NrOfIdleFrames;
	}
}

bool Avatar::GetPowerStatus() const
{
	return m_IsPowered;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::CoundownPower(float elapsedSec)
{
	if (m_PowerUpTime < m_PowerUpDuration)
	{
		m_PowerUpTime += elapsedSec;
	}
	else
	{	
		m_PowerUpTime = 0.0f;
		m_IsPowered = false;
	}
}

void Avatar::Empower()
{
	m_IsPowered = true;
}

void Avatar::Kill()
{
	m_ActionState = dead;
}

void Avatar::Respawn()
{
	Rectf startPos{ 300.0f, 130.0f, 46.0f, 68.0f };
	m_Shape.bottom = startPos.bottom;
	m_Shape.left = startPos.left;
	m_Velocity.y = 0.0f;
	m_Velocity.x = 0.0f;
	m_ActionState = waiting;
}

float Avatar::GetPowerTime() const
{
	return m_PowerUpTime / m_PowerUpDuration;
}

float Avatar::GetHealth() const
{
	return m_Health;
}