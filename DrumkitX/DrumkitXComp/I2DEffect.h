/**
 * Copyright (c) 2013 Nokia Corporation.
 */

#pragma once

#include "Types.h"

using DrumkitXComp::FRECT;

/**
 * @class I2DEffect
 * @brief Interface for 2D effects.
 */
class I2DEffect
{
public:
	virtual void Start(float timestamp) = 0;
	virtual void Update(RECT source, FRECT original, float timestamp) = 0;
	virtual FRECT DestinationRect() = 0;
	virtual float Rotation() = 0;
	virtual DirectX::XMFLOAT2 Origin() = 0;
};
