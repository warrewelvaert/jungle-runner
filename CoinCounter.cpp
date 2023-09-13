#include "pch.h"
#include "CoinCounter.h"

CoinCounter::CoinCounter()
	:m_ValueString{ "0" }
{
	m_pCounterTex.push_back(new Texture{ m_ValueString, "./Resources/PixelFont.otf", 30, Color4f(1, 1, 0, 1) });
}

CoinCounter::~CoinCounter()
{
	delete m_pCounterTex[0];
	m_pCounterTex[0] = nullptr;
}

void CoinCounter::Draw(const Rectf cameraWindow) const
{
	Point2f destPoint{ cameraWindow.left + cameraWindow.width / 2, cameraWindow.bottom + cameraWindow.height - 70.0f };
	m_pCounterTex[0]->Draw(destPoint);
}

void CoinCounter::AddValue(int value)
{
	m_CounterValue += value;
	m_ValueString = std::to_string(m_CounterValue);

	delete m_pCounterTex[0];
	m_pCounterTex[0] = nullptr;

	m_pCounterTex.pop_back();
	m_pCounterTex.push_back(new Texture{ m_ValueString, "./Resources/PixelFont.otf", 30, Color4f(1, 1, 0, 1) });
}
