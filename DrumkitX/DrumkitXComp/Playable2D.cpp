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
#include "Playable2D.h"


const DirectX::XMFLOAT2 Playable2D::Float2Zero(0, 0);

/**
 * @class Playable2D
 * @brief Represents a playable object.
 */

Playable2D::Playable2D(ID3D11ShaderResourceView* texture, D3D11_TEXTURE2D_DESC texdesc, size_t sampleIdx, FRECT rect)
	: m_texture(texture), m_sampleIdx(sampleIdx), m_destinationRect(rect)
{
	m_sourceRect.top = 0;
	m_sourceRect.left = 0;
	m_sourceRect.bottom = texdesc.Height;
	m_sourceRect.right = texdesc.Width;
}

Playable2D::~Playable2D()
{
	ID3D11ShaderResourceView* tex = m_texture.release();
	tex->Release();
}

ID3D11ShaderResourceView* Playable2D::Texture()
{
	return m_texture.get();
}

size_t Playable2D::SampleIndex()
{
	return m_sampleIdx;
}

FRECT Playable2D::Position()
{
	return m_destinationRect;
}

FRECT Playable2D::DestinationRect()
{
	if (m_effect != nullptr)
	{
		return m_effect->DestinationRect();
	}
	return m_destinationRect;
}

void Playable2D::Update(float timestamp)
{
	if (m_effect != nullptr)
	{
		m_effect->Update(m_sourceRect, m_destinationRect, timestamp);
	}
}

void Playable2D::SetEffect(std::unique_ptr<I2DEffect> effect)
{
	m_effect = std::move(effect);
}

void Playable2D::Play(float timestamp)
{
	if (m_effect != nullptr)
	{
		m_effect->Start(timestamp);
	}
}

DirectX::FXMVECTOR Playable2D::Color()
{
	return DirectX::Colors::White;
}

float Playable2D::Rotation()
{
	if (m_effect != nullptr) {
		return m_effect->Rotation();
	}
	return 0;
}

DirectX::XMFLOAT2 Playable2D::Origin()
{
	if (m_effect != nullptr)
	{
		return m_effect->Origin();
	}
	return Float2Zero;
}

DirectX::SpriteEffects Playable2D::Effects()
{
	return DirectX::SpriteEffects_None;
}

float Playable2D::LayerDepth()
{
	return 0;
}