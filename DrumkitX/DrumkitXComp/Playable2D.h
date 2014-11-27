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
#include "Types.h"

using DrumkitXComp::FRECT;

class Playable2D
{
public:
	// Create new playable with given texture and the given sample index and
	// position + size on screen.
	Playable2D(ID3D11ShaderResourceView* texture, D3D11_TEXTURE2D_DESC texdesc, size_t sampleIdx, FRECT rect);

	virtual ~Playable2D();

	// Get pointer to texture
	ID3D11ShaderResourceView* Texture();

	// Get sample index for playback
	size_t SampleIndex();
	
	// Update time-dependent attributes
	void Update(float timestamp);

	// Set effect for playing
	void SetEffect(std::unique_ptr<I2DEffect> effect);

	// Play starting at timestamp
	void Play(float timestamp);
	
	// Sprite position
	FRECT Position();

	// Render destination position and size relative to origin
	FRECT DestinationRect();

	// Render source rect
	const RECT *SourceRect();

	// TODO
	DirectX::FXMVECTOR Color();

	// Sprite rotation
	float Rotation();

	// TODO
	DirectX::XMFLOAT2 Origin();

	// TODO
	DirectX::SpriteEffects Effects();

	// TODO
	float LayerDepth();
	
private:
	static const DirectX::XMFLOAT2 Float2Zero;

	std::unique_ptr<ID3D11ShaderResourceView> m_texture;
	size_t m_sampleIdx;
	FRECT m_destinationRect;
	RECT m_sourceRect;
	std::unique_ptr<I2DEffect> m_effect;
};