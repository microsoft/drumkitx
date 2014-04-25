/**
 * Copyright (c) 2013-2014 Microsoft Mobile. All rights reserved.
 *
 * Nokia, Nokia Connecting People, Nokia Developer, and HERE are trademarks
 * and/or registered trademarks of Nokia Corporation. Other product and company
 * names mentioned herein may be trademarks or trade names of their respective
 * owners.
 *
 * See the license text file delivered with this project for more information.
 */

#include "pch.h"
#include "Shake.h"

/**
 * @class Shake
 * @brief Shake effect for drums.
 */

Shake::Shake(float amplitude, float frequency, float cutoff)
	: m_running(false), m_start(0), m_amplitude(amplitude), m_frequency(frequency), m_cutoff(cutoff)
{}

void Shake::Start(float timestamp)
{
	m_start = timestamp;
	m_running = true;
}

void Shake::Update(RECT source, FRECT original, float timestamp)
{
	(void)source;
	m_rect = original;

	if (!m_running)
	{
		return;
	}

	float animDuration = timestamp - m_start;
	float xoff =
		// basic shake
		m_amplitude * sin(m_frequency * animDuration)
		// attenuation
		* max((1.0f / (animDuration + 1.0f)) * (1.0f - animDuration / m_cutoff), 0.0f);
	m_rect.left += xoff;
	m_rect.right += xoff;

	if (animDuration > m_cutoff)
	{
		m_running = false;
	}
}

FRECT Shake::DestinationRect()
{
	return m_rect;
}

float Shake::Rotation()
{
	return 0;
}

DirectX::XMFLOAT2 Shake::Origin()
{
	return DirectX::XMFLOAT2(0, 0);
}
