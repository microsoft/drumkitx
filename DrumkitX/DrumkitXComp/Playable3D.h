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

#include <GeometricPrimitive.h>

using DirectX::GeometricPrimitive;

class Playable3D
{
public:
	Playable3D(std::unique_ptr<GeometricPrimitive> shape, size_t sampleIdx);

private:
	std::unique_ptr<GeometricPrimitive> m_shape;
	size_t m_sampleIdx;
};
