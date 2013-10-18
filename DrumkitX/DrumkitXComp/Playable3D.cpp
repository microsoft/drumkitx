#include "pch.h"
#include "Playable3D.h"

Playable3D::Playable3D(std::unique_ptr<GeometricPrimitive> shape, size_t sampleIdx)
	: m_shape(std::move(shape)), m_sampleIdx(sampleIdx)
{}
