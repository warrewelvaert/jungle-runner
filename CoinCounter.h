#pragma once
#include"pch.h"
#include <iostream>
#include "Texture.h"
#include <vector>

class CoinCounter
{
public:
	CoinCounter();
	~CoinCounter();
	void Draw(const Rectf cameraWindow) const;
	void AddValue(int value);

private:
	int m_CounterValue;
	std::vector<Texture*> m_pCounterTex;
	std::string m_ValueString;
};

