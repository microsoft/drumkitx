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
#include "Playable3D.h"

Playable3D::Playable3D(std::unique_ptr<GeometricPrimitive> shape, size_t sampleIdx)
	: m_shape(std::move(shape)), m_sampleIdx(sampleIdx)
{}
