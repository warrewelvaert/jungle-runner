#include "pch.h"
#include "Game.h"   

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_pAvatar{ new Avatar }
	, m_pCounter{ new CoinCounter }
	, m_Camera{1000.0f, 600.0f}
	, m_StartTexture{ "./Resources/Images/StartScreen.png" }
	, m_WinTexture{ "./Resources/Images/WinScreen.png" }
	, m_DefeatTexture{ "./Resources/Images/DeadScreen.png" }
	, m_Door{ Point2f(12650.f, 125.f), Point2f(12708.f, 610.f) }
	, m_StartMusic{ "./Resources/Audio/music2.wav" }
	, m_PlayMusic{ "./Resources/Audio/music1.wav" }
	, m_PressEnter{ "./Resources/Audio/pressenter.ogg" }
	, m_GameOver{ "./Resources/Audio/gameover.wav" }
{
	Initialize( );
}

Game::~Game()
{
	Cleanup();
	delete m_pAvatar;
	delete m_pCounter;
}

void Game::Initialize( )
{
	InitCamera();
	InitSprites();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

	if (m_Door.IsDoorOpen() == true)
	{
		m_GameState = GameState::win;
	}
	if (m_GameState == GameState::start && pStates[SDL_SCANCODE_RETURN])
	{
		m_PressEnter.Play(0);
		m_GameState = GameState::play;
	}
	else if (m_GameState == GameState::play)
	{
		m_AvatarShape = m_pAvatar->GetShape();
		m_CameraRect = m_Camera.GetBoundries(m_AvatarShape);

		if (m_pAvatar->GetHealth() <= 0.f)
		{
			m_GameOver.Play(0);
			m_GameState = GameState::defeat;
		}

		m_pAvatar->Update(m_Level, elapsedSec);
		m_SpiderManager.Update(elapsedSec);
		m_BatManager.Update(elapsedSec, m_AvatarShape);
		m_WizzardManager.Update(elapsedSec, m_AvatarShape);
		m_Door.Update(m_AvatarShape);

		m_CoinManager.HitCoin(m_AvatarShape, m_pCounter);
		m_PowerUpManager.HitPowerUp(m_AvatarShape, m_pAvatar);
		m_SpiderManager.HitEnemy(m_AvatarShape, m_pAvatar);
		m_BatManager.HitEnemy(m_AvatarShape, m_pAvatar);
		m_WizzardManager.HitWizzard(m_AvatarShape, m_pAvatar);
		m_SpikesManager.HitSpike(m_AvatarShape, m_pAvatar);

		m_StatusBars.Update(m_CameraRect, m_pAvatar);
	}
	else if (pStates[SDL_SCANCODE_R] && m_GameState == GameState::defeat)
	{
		m_PressEnter.Play(0);
		ResetGame();
		m_GameState = GameState::play;
	}
	PlayMusic();
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_Camera.Transform(m_AvatarShape);

	if (m_GameState == GameState::play)
	{
		//Draw BG
		m_Level.Draw();

		//Draw Sprites
		m_CoinManager.Draw();
		m_SpiderManager.Draw();
		m_BatManager.Draw();
		m_WizzardManager.Draw();
		m_SpikesManager.Draw();
		m_PowerUpManager.Draw();
		m_Door.Draw();
		m_pAvatar->Draw();

		//Draw HUD
		m_pCounter->Draw(m_CameraRect);
		m_StatusBars.Draw(m_CameraRect);
	}
	else if (m_GameState == GameState::start)
	{
		m_StartTexture.Draw();
	}
	else if (m_GameState == GameState::defeat)
	{
		m_DefeatTexture.Draw();
	}
	else
	{
		m_WinTexture.Draw(m_CameraRect);
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_KP_PLUS:
		m_MusicVolume += 10;
		Mix_VolumeMusic(m_MusicVolume);
		break;

	case SDLK_KP_MINUS:
		m_MusicVolume -= 10;
		Mix_VolumeMusic(m_MusicVolume);
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_SPACE:
		if (m_IsMuted == false)
		{
			Mix_PauseMusic();
			m_IsMuted = true;
		}
		else
		{
			Mix_ResumeMusic();
			m_IsMuted = false;
		}
		break;
	case SDLK_i:
		PrintExpl();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.10f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::PrintExpl()
{
	std::cout << "- Use the arrow keys to move and jump" << '\n';
	std::cout << "- Press SPACE to mute/unmute music" << '\n';
	std::cout << "- Hold + or - to adjust volume" << '\n';
	std::cout << "- Find the key to open the door at the end of the level" << '\n';
}

void Game::InitCamera()
{
	Rectf levelBoundries{ 0.0f, 0.0f, 12800.0f, 800.0f };
	m_Camera.SetLevelBoundries(levelBoundries);
}

void Game::InitSprites()
{
	const int nrOfCoins{ 43 };
	Coins::Type coinType{ Coins::Type::coin };
	Coins::Type ringType{ Coins::Type::ring };
	Coins::Type gemType{ Coins::Type::gem };
	const float coinBuffer{ 98.f };
	const float coinPlatHeight{ 275.f };
	const float coinPlatHeightTwo{ 355.f  };
	const float coinPlatHeightThree{ 435.f };

	//Coins
	Coins coinObj[nrOfCoins]{ Coins{coinType, Point2f(900.f, coinPlatHeight) }, Coins{ringType, Point2f(900.f + coinBuffer, coinPlatHeight) }, Coins{coinType, Point2f(900.f + coinBuffer * 2, coinPlatHeight) },
	Coins{coinType, Point2f(1156, coinPlatHeightThree) }, Coins{ringType, Point2f(1156 + coinBuffer, coinPlatHeightThree) }, Coins{coinType, Point2f(1156 + coinBuffer * 2, coinPlatHeightThree)}, Coins{ringType, Point2f(1555.f, m_GroundLevel)}, 
	Coins{coinType, Point2f(1945.f, coinPlatHeightTwo)}, Coins{ringType, Point2f(1945.f + coinBuffer, coinPlatHeightTwo)}, Coins{coinType, Point2f(1945.f + coinBuffer * 2, coinPlatHeightTwo)},
	Coins{coinType, Point2f(2457.f, coinPlatHeightTwo)}, Coins{coinType, Point2f(2457.f + coinBuffer * 2, coinPlatHeightTwo)},
	Coins{gemType, Point2f(2329.f, m_GroundLevel)}, Coins{coinType, Point2f(3115.f, m_GroundLevel)},  Coins{coinType, Point2f(3115.f + coinBuffer, m_GroundLevel)}, Coins{gemType, Point2f(3677.f, m_GroundLevel)}, 
	Coins{coinType, Point2f(4120.f, m_GroundLevel)},  Coins{coinType, Point2f(4120.f + coinBuffer, m_GroundLevel)}, Coins{coinType, Point2f(4570.f, m_GroundLevel)},  Coins{coinType, Point2f(4570.f + coinBuffer, m_GroundLevel)},
	Coins{ringType, Point2f(5035.f, m_GroundLevel)}, Coins{coinType, Point2f(7750.f, coinPlatHeight)},  Coins{coinType, Point2f(7750.f + coinBuffer, coinPlatHeight)}, Coins{coinType, Point2f(7750.f + coinBuffer * 2, coinPlatHeight)},
	Coins{coinType, Point2f(8006.f, coinPlatHeightThree)},  Coins{coinType, Point2f(8006.f + coinBuffer, coinPlatHeightThree)}, Coins{coinType, Point2f(8006.f + coinBuffer * 2, coinPlatHeightThree)}, 
	Coins{gemType, Point2f(7750.f, 610.f)}, Coins{coinType, Point2f(9190.f, m_GroundLevel)}, Coins{coinType, Point2f(9190.f + coinBuffer, m_GroundLevel)}, Coins{coinType, Point2f(10290.f, m_GroundLevel)}, 
	Coins{coinType, Point2f(10290.f + coinBuffer, m_GroundLevel)},
	Coins{coinType, Point2f(12000.f, coinPlatHeight) }, Coins{ringType, Point2f(12000.f + coinBuffer, coinPlatHeight) }, Coins{coinType, Point2f(12000.f + coinBuffer * 2, coinPlatHeight)},
	Coins{coinType, Point2f(12256.f, coinPlatHeightThree) }, Coins{ringType, Point2f(12256.f + coinBuffer, coinPlatHeightThree) }, Coins{coinType, Point2f(12256.f + coinBuffer * 2, coinPlatHeightThree)},
	Coins{gemType, Point2f(12000.f, coinPlatHeightThree + 175.f) }, Coins{coinType, Point2f(12000.f + coinBuffer, coinPlatHeightThree + 175.f) }, Coins{coinType, Point2f(12000.f + coinBuffer * 2, coinPlatHeightThree + 175.f)},
	Coins{coinType, Point2f(12512.f, coinPlatHeightThree + 175.f) }, Coins{coinType, Point2f(12512.f + coinBuffer, coinPlatHeightThree + 175.f)} };

	for (int i = 0; i < nrOfCoins; i++)
	{
		m_CoinManager.AddSprite( coinObj[i] );
	}

	//PowerUps
	const int nrOfPowerUps{ 2 };
	PowerUp powerUpObjs[nrOfPowerUps]{ Point2f(2457.f + coinBuffer, coinPlatHeightTwo), Point2f(6240.f, m_GroundLevel) };
	for (int i = 0; i < nrOfPowerUps; i++)
	{
		m_PowerUpManager.AddSprite( powerUpObjs[i] );
	}

	//Spikes
	const float spikeGapOne{ 5098.f };
	const float spikeGapTwo{ 6305.f };
	const float spikeGapThree{ 10743.f };
	
	const int nrOfSpikes{ 9 };
	Spikes spikeObj[nrOfSpikes]{ Point2f{spikeGapOne, 0.0f}, Point2f{spikeGapOne + 66.f, 0.0f}, Point2f{spikeGapOne + 66.f * 2, 0.0f},
	Point2f{spikeGapTwo, 0.0f}, Point2f{spikeGapTwo + 66.0f, 0.0f}, Point2f{spikeGapTwo + 66.0f * 2, 0.0f},
	Point2f{spikeGapThree, 0.0f}, Point2f{spikeGapThree + 66.0f, 0.0f}, Point2f{spikeGapThree + 66.0f * 2, 0.0f} };

	for (int i = 0; i < nrOfSpikes; i++)
	{
		m_SpikesManager.AddSprite( spikeObj[i] );
	}

	//Spiders
	const int spiderAmount{ 7 };
	Spider spiderObjs[spiderAmount]{ Point2f(1100.f, m_GroundLevel), Point2f(4575.f, m_GroundLevel), Point2f(5400.f, m_GroundLevel), Point2f(7920.f, m_GroundLevel), Point2f(8420.f, m_GroundLevel),
	Point2f(9220.f, m_GroundLevel), Point2f(11250.f, m_GroundLevel) };

	for (int i = 0; i < spiderAmount; i++)
	{
		m_SpiderManager.AddSprite(spiderObjs[i]);
	}

	//Bats
	const int batAmount{ 7 };
	float newGroundlvl = m_GroundLevel + 15.f;
	Bat batObjs[batAmount]{ Point2f(2179.f, newGroundlvl), Point2f(2543.f, newGroundlvl), Point2f(6800.f, newGroundlvl), Point2f(7150.f, newGroundlvl), Point2f(7500.f, newGroundlvl),
		Point2f(9732.f, newGroundlvl), Point2f(12000.f, newGroundlvl) };

	for (int i = 0; i < batAmount; i++)
	{
		m_BatManager.AddSprite(batObjs[i]);
	}

	//Wizzards
	const int wizzzardAmount{ 4 };
	Wizzard wizzardObj[wizzzardAmount]{ Point2f(3482.f, m_GroundLevel), Point2f(3879.f, m_GroundLevel), Point2f(6160.f, m_GroundLevel), Point2f(10120.f, m_GroundLevel) };

	for (int i = 0; i < wizzzardAmount; i++)
	{
		m_WizzardManager.AddSprite(wizzardObj[i]);
	}
}

void Game::ResetGame()
{
	delete m_pAvatar;
	delete m_pCounter;

	m_CoinManager.~SpriteManager();
	m_PowerUpManager.~SpriteManager();
	m_SpiderManager.~SpriteManager();
	m_BatManager.~SpriteManager();
	m_WizzardManager.~SpriteManager();
	m_SpikesManager.~SpriteManager();

	m_pAvatar = new Avatar;
	m_pCounter = new CoinCounter;
	InitSprites();
	m_Door.ResetKet();
}

void Game::PlayMusic()
{
	if (m_GameState != GameState::start && m_HasPlayedMusic == false)
	{
		m_PlayMusic.Play(true);
		m_HasPlayedMusic = true;
	}
	else if (m_HasPlayedStart == false)
	{
		m_StartMusic.Play(true);
		m_HasPlayedStart = true;
	}
}