#pragma once
#pragma once
#include "Coins.h"
#include "CoinCounter.h"
#include "Avatar.h"
#include "SoundEffect.h"
#include <vector>

template<typename T>
class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	void AddSprite(T& sprite);
	void Draw() const;
	void Update(float elapsedSec);
	void Update(float elapsedSec, const Rectf& avatarRect);

	void HitEnemy(const Rectf& avatarRect, Avatar* &avatar);
	void HitSpike(const Rectf& avatarRect, Avatar* &avatar);
	void HitWizzard(const Rectf& avatarRect, Avatar* &avatar);
	void HitCoin(const Rectf& avatarRect, CoinCounter* &counter);
	void HitPowerUp(const Rectf& avatarRect, Avatar* &avatar);

private:
	std::vector<T*> m_pSprites;
	const SoundEffect m_Potion;
	const SoundEffect m_Enemy;
	const SoundEffect m_Coin;
	const SoundEffect m_Player;
};

template<typename T>
SpriteManager<T>::SpriteManager()
	:m_Potion{ "./Resources/Audio/potion.ogg" }
	, m_Enemy{ "./Resources/Audio/enemy.ogg" }
	, m_Coin{ "./Resources/Audio/coin.wav" }
	, m_Player{ "./Resources/Audio/player.ogg" }
{
}

template<typename T>
SpriteManager<T>::~SpriteManager()
{
	for (T* i : m_pSprites)
	{
		delete i;
		i = nullptr;
	}
}

template<typename T>
void SpriteManager<T>::Draw() const
{
	for (T* i : m_pSprites)
	{
		i->Draw();
	}
}

template<typename T>
void SpriteManager<T>::Update(float elapsedSec)
{
	for (T* i : m_pSprites)
	{
		i->Update(elapsedSec);
	}
}

template<typename T>
void SpriteManager<T>::Update(float elapsedSec, const Rectf& avatarRect)
{
	for (T* i : m_pSprites)
	{
		i->Update(elapsedSec, avatarRect);
	}
}

template<typename T>
void SpriteManager<T>::AddSprite(T& sprite)
{
	m_pSprites.push_back(new T{ sprite });
}

template<typename T>
void SpriteManager<T>::HitWizzard(const Rectf& avatarRect, Avatar* &avatar)
{
	for (size_t i = 0; i < m_pSprites.size(); i++)
	{
		if ( utils::IsOverlapping(avatarRect, m_pSprites[i]->GetShape()) || utils::IsOverlapping(avatarRect, m_pSprites[i]->GetProjShape() ) ) 
		{
			if (avatar->GetPowerStatus() == false)
			{
				m_Player.Play(0);
				avatar->Kill();
			}
			else if ( utils::IsOverlapping( avatarRect, m_pSprites[i]->GetProjShape() ) )
			{
				m_pSprites[i]->KillProjectile();
			}
			else
			{
				m_Enemy.Play(0);
				delete  m_pSprites[i];
				m_pSprites[i] = nullptr;
				m_pSprites[i] = m_pSprites.back();
				m_pSprites.pop_back();
			}
		}
	}
}

template<typename T>
void SpriteManager<T>::HitEnemy(const Rectf& avatarRect, Avatar* &avatar)
{
	for (size_t i = 0; i < m_pSprites.size(); i++)
	{
		if (utils::IsOverlapping(avatarRect, m_pSprites[i]->GetShape()))
		{
			if (avatar->GetPowerStatus() == true)
			{
				m_Enemy.Play(0);
				delete  m_pSprites[i];
				m_pSprites[i] = nullptr;
				m_pSprites[i] = m_pSprites.back();
				m_pSprites.pop_back();
			}
			else
			{
				m_Player.Play(0);
				avatar->Kill();
			}
		}
	}
}

template<typename T>
void SpriteManager<T>::HitSpike(const Rectf& avatarRect, Avatar* &avatar)
{
	for (T* i : m_pSprites)
	{
		if (utils::IsOverlapping(avatarRect, i->GetShape()))
		{
			m_Player.Play(0);
			avatar->Kill();
		}
	}
}

template<typename T>
void SpriteManager<T>::HitCoin(const Rectf& avatarRect, CoinCounter* &counter)
{
	for (size_t i = 0; i < m_pSprites.size(); i++)
	{
		if (utils::IsOverlapping(avatarRect, m_pSprites[i]->GetShape()))
		{
			counter->AddValue(m_pSprites[i]->GetValue());
			m_Coin.Play(0);
			delete  m_pSprites[i];
			m_pSprites[i] = nullptr;
			m_pSprites[i] = m_pSprites.back();
			m_pSprites.pop_back();
		}
	}
}

template<typename T>
void SpriteManager<T>::HitPowerUp(const Rectf& avatarRect, Avatar* &avatar)
{
	for (size_t i = 0; i < m_pSprites.size(); i++)
	{
		if (utils::IsOverlapping(avatarRect, m_pSprites[i]->GetShape()))
		{
			avatar->Empower();
			m_Potion.Play(0);
			delete  m_pSprites[i];
			m_pSprites[i] = nullptr;
			m_pSprites[i] = m_pSprites.back();
			m_pSprites.pop_back();
		}
	}
}