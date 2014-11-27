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

#include "Direct3DBase.h"
#include "ITappable.h"
#include "Playable2D.h"
#include "XAudio2SoundPlayer.h"

using DrumkitXComp::ITappable;

struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

ref class DrumkitRenderer sealed : public Direct3DBase, public ITappable
{
public:
	DrumkitRenderer();
	virtual ~DrumkitRenderer();

	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	
	// Method for updating time-dependent objects.
	void Update(float timeTotal, float timeDelta);

	// Method for handling touch events
	virtual void Tap(float x, float y);

	// Methods for controlling the audio engine
	void Suspend();
	void Resume();

private:
	bool m_loadingComplete;

	std::unique_ptr<ID3D11BlendState> m_padBlendState;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	wchar_t m_debugBuffer[256];

	XAudio2SoundPlayer m_player;

	std::vector<std::unique_ptr<Playable2D> > m_2dpads;

	ID3D11ShaderResourceView* m_bgtex;
	ID3D11ShaderResourceView* m_locktex;

	float m_timeTotal;
};
