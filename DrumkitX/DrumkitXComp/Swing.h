/**
 * Copyright (c) 2013 Nokia Corporation.
 */

#pragma once

#include "I2DEffect.h"

class Swing : public I2DEffect
{
public:
	Swing(float amplitude, float frequency, float cutoff);
	virtual void Start(float timestamp);
	virtual void Update(RECT source, FRECT original, float timestamp);
	virtual FRECT DestinationRect();
	virtual float Rotation();
	virtual DirectX::XMFLOAT2 Origin();

private:
	RECT m_source;
	FRECT m_origRect;
	FRECT m_rect;
	float m_rotation;
	bool m_running;
	float m_start;
	float m_amplitude;
	float m_frequency;
	float m_cutoff;
};