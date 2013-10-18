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
