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
#include "Swing.h"

/**
 * @class Swing
 * @brief Swing effect for cymbals.
 */

Swing::Swing(float amplitude, float frequency, float cutoff)
	: m_rotation(0), m_running(false), m_start(0), m_amplitude(amplitude), m_frequency(frequency), m_cutoff(cutoff)
{}

void Swing::Start(float timestamp)
{
	m_rotation = 0;
	m_start = timestamp;
	m_running = true;
}

void Swing::Update(RECT source, FRECT original, float timestamp)
{
	m_source = source;
	m_origRect = original;
	m_rect = m_origRect;
	m_rect.left   += (0.5f * (m_origRect.right - m_origRect.left));
	m_rect.right  += (0.5f * (m_origRect.right - m_origRect.left));
	m_rect.top    += (0.5f * (m_origRect.bottom - m_origRect.top));
	m_rect.bottom += (0.5f * (m_origRect.bottom - m_origRect.top));

	if (!m_running)
	{
		return;
	}
	float animDuration = timestamp - m_start;

	m_rotation =
		// basic rotation
		m_amplitude * sin(m_frequency * animDuration)
		// attenuation
		* max((1.0f / (animDuration + 1.0f)) * (1.0f - animDuration / m_cutoff), 0.0f);
 
	if (animDuration > m_cutoff)
	{
		m_running = false;
		m_rotation = 0;
	}
}

FRECT Swing::DestinationRect()
{
	return m_rect;
}

float Swing::Rotation()
{
	return m_rotation;
}

DirectX::XMFLOAT2 Swing::Origin()
{
	return DirectX::XMFLOAT2(0.5f * (m_source.right - m_source.left),
		                     0.5f * (m_source.bottom - m_source.top));
}
