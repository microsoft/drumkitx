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

#pragma once

#include "I2DEffect.h"

class Shake : public I2DEffect
{
public:
	Shake(float amplitude, float frequency, float cutoff);
	virtual void Start(float timestamp);
	virtual void Update(RECT source, FRECT original, float timestamp);
	virtual FRECT DestinationRect();
	virtual float Rotation();
	virtual DirectX::XMFLOAT2 Origin();

private:
	FRECT m_rect;
	bool m_running;
	float m_start;
	float m_amplitude;
	float m_frequency;
	float m_cutoff;
};
