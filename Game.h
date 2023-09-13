#pragma once
#include "Avatar.h"
#include "Spider.h"
#include "PowerUp.h"
#include "Level.h"
#include "Bat.h"
#include "Wizzard.h"
#include "Spikes.h"
#include "Camera.h"
#include <vector>
#include "SpriteManager.h"
#include "AvatarBars.h"
#include "Door.h"
#include "SoundEffect.h"
#include "SoundStream.h"
#include <stdlib.h>  

class Game
{
	enum GameState
	{
		start, play, win, defeat
	};
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	GameState m_GameState{ start };
	
	Avatar* m_pAvatar;
	CoinCounter* m_pCounter;
	Level m_Level;
	Camera m_Camera;
	AvatarBars m_StatusBars;
	Door m_Door;
	SpriteManager<Coins> m_CoinManager;
	SpriteManager<PowerUp> m_PowerUpManager;
	SpriteManager<Spider> m_SpiderManager;
	SpriteManager<Spikes> m_SpikesManager;
	SpriteManager<Bat> m_BatManager;
	SpriteManager<Wizzard> m_WizzardManager;

	Texture m_StartTexture;
	Texture m_WinTexture;
	Texture m_DefeatTexture;

	Rectf m_CameraRect;
	Rectf m_AvatarShape;
	Rectf m_ResetShape;

	bool m_StartState{ true };
	const float m_GroundLevel{ 125.f };
	float m_RespawnTime{ 0.0f };
	bool m_HasPlayedStart{ false };
	bool m_HasPlayedMusic{ false };
	bool m_IsMuted{ false };
	int m_MusicVolume{ 80 };

	const SoundStream m_StartMusic;
	const SoundStream m_PlayMusic;
	const SoundEffect m_PressEnter;
	const SoundEffect m_GameOver;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void InitCamera();
	void InitSprites();

	void PrintExpl();
	void ResetGame();
	void PlayMusic();
};