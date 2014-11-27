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
