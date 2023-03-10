#include "FPSCounter.h"
#include <iosfwd>

#include "GameObject.h"
#include "Time.h"
#include "TextComponent.h"

void dae::FPSCounter::Update()
{
	//Update frame counter
	++m_AmountOfPassedFrames;

	// Every updateInterval, update the text to the average FPS of the interval
	m_AccuSec += Time::GetInstance().GetDelta();
	if (m_AccuSec >= m_UpdateInterval)
	{
		m_AccuSec -= m_UpdateInterval;

		m_FPS = static_cast<int>(m_AmountOfPassedFrames / m_UpdateInterval);

		m_AmountOfPassedFrames = 0;


		// TEXT PART

		// Get text component if its not there
		if (m_pText.expired())
		{
			m_pText = GetOwner()->GetComponent<dae::TextComponent>();//GetComponent<TextComponent>();

			if (m_pText.expired()) return;
		}

		// Update text component
		std::stringstream fpsText{};

		fpsText << m_FPS;
		fpsText << " FPS";

		m_pText.lock()->SetText(fpsText.str());
	}
}
