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
#include "DrumkitRenderer.h"

#include "Shake.h"
#include "SoundFileReader.h"
#include "Swing.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

namespace {
	const float PAD_SHAKE_AMPLITUDE = 0.008f;
	const float PAD_SHAKE_FREQUENCY = XM_2PI * 7.0f;
	const float PAD_SHAKE_CUTOFF = 1.0f;
	const float SWING_AMPLITUDE = XM_PIDIV4 / 8.0f;
	const float SWING_FREQUENCY = XM_2PI * 8.0f;
	const float SWING_CUTOFF = 2.0f;
}

/**
 * @class DrumkitRenderer
 * @brief This class is responsible of rendering the drumkit.
 */

DrumkitRenderer::DrumkitRenderer() :
	m_loadingComplete(false),
	m_player(48000),
	m_timeTotal(0),
	m_bgtex(nullptr),
	m_locktex(nullptr)
{
}

DrumkitRenderer::~DrumkitRenderer()
{
	if (m_bgtex)
	{
		m_bgtex->Release();
	}

	if (m_locktex)
	{
		m_locktex->Release();
	}
}

void DrumkitRenderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	m_spriteBatch = std::unique_ptr<DirectX::SpriteBatch>(new DirectX::SpriteBatch(m_d3dContext.Get()));

	auto drumkit2DTask = Concurrency::task<void>([this] () {
		const wchar_t* texturefilenames[] = {
			L"images\\kick.dds",
			L"images\\tom1.dds",
			L"images\\tom2.dds",
			L"images\\tom3.dds",
			L"images\\snare.dds",
			L"images\\cowbell.dds",
			L"images\\crash.dds",
			L"images\\hihat_open_lower.dds",
			L"images\\hihat_open_upper.dds",
			L"images\\hihat_closed.dds",
			L"images\\china.dds",
			L"images\\ride1.dds",
			L"images\\ride2.dds",
			L"images\\splash.dds",
			nullptr
		};

		const wchar_t* samplefilenames[] = {
			L"sounds\\kick.wav",
			L"sounds\\tom1.wav",
			L"sounds\\tom2.wav",
			L"sounds\\tom3.wav",
			L"sounds\\snare.wav",
			L"sounds\\cowbell.wav",
			L"sounds\\crash.wav",
			L"sounds\\hihat2.wav",
			L"sounds\\hihat2.wav",
			L"sounds\\hihat1.wav",
			L"sounds\\china.wav",
			L"sounds\\ride1.wav",
			L"sounds\\ride2.wav",
			L"sounds\\splash.wav",
			nullptr
		};

		FRECT positions[] = {
			{-0.0125f, 0.49583f, 0.3f,     0.98542f},   // kick
			{0.27125f, 0.32292f, 0.44f,    0.67292f},   // tom1
			{0.445f,   0.31042f, 0.6325f,  0.69583f},   // tom2
			{0.58875f, 0.5f,     0.8125f,  0.96042f},   // tom3
			{0.265f,   0.6f,     0.51125f, 0.97083f},   // snare
			{0.5025f,  0.73542f, 0.635f,   0.95833f},   // cowbell
			{-0.025f,  0.19167f, 0.285f,   0.49375f},   // crash
			{0.7925f,  0.55417f, 1.05125f, 0.72708f},   // hihat open bottom
			{0.7925f,  0.48333f, 1.0625f,  0.675f  },   // hihat open top
			{0.73875f, 0.71667f, 1.025f,   0.92917f},   // hihat
			{0.1425f,  0.07292f, 0.40875f, 0.33542f},   // china
			{0.58f,    0.09375f, 0.92875f, 0.30417f},   // ride1
			{0.6775f,  0.225f,   1.015f,   0.48542f},   // ride2
			{0.38625f, 0.11875f, 0.59625f, 0.26667f}    // splash
		};

		I2DEffect* effects[] = {
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // kick
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // tom1
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // tom2
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // tom3
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // snare
			new Shake(PAD_SHAKE_AMPLITUDE, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // cowbell
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // crash
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // hihat open bottom
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // hihat open top
			new Shake(PAD_SHAKE_AMPLITUDE / 2.0f, PAD_SHAKE_FREQUENCY, PAD_SHAKE_CUTOFF), // hihat
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // china
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // ride1
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF), // ride2
			new Swing(SWING_AMPLITUDE, SWING_FREQUENCY, SWING_CUTOFF) // splash
		};

		size_t idx = 0;
		const wchar_t *tex = texturefilenames[idx];
        const wchar_t *sample = samplefilenames[idx];

		while (tex != nullptr && sample != nullptr)
		{
			// load texture
			ID3D11ShaderResourceView* texture = 0;
			DrumkitXComp::ThrowIfFailed(
				CreateDDSTextureFromFile(m_d3dDevice.Get(), tex, nullptr, &texture)
			);

			// load sample
			SoundFileReader reader(ref new Platform::String(sample));
			size_t sampleIdx = m_player.AddSound(reader.GetSoundFormat(), reader.GetSoundData());
			
			// Get dimensions of texture
			ID3D11Resource* res = 0;
			texture->GetResource(&res);
			ID3D11Texture2D* tex2d = 0;
			res->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&tex2d);
			D3D11_TEXTURE2D_DESC texdesc;
			tex2d->GetDesc(&texdesc);
			
			// make and store pad
			Playable2D* pad = new Playable2D(texture, texdesc, sampleIdx, positions[idx]);
			pad->SetEffect(std::unique_ptr<I2DEffect>(effects[idx]));
			m_2dpads.push_back(std::move(std::unique_ptr<Playable2D>(pad)));
			
			// next round
			++idx;
			tex = texturefilenames[idx];
			sample = samplefilenames[idx];
		}
		
		DrumkitXComp::ThrowIfFailed(
			CreateDDSTextureFromFile(m_d3dDevice.Get(), L"images\\background.dds", nullptr, &m_bgtex)
		);

		DrumkitXComp::ThrowIfFailed(
			CreateDDSTextureFromFile(m_d3dDevice.Get(), L"images\\locks.dds", nullptr, &m_locktex)
		);
	});

	auto deviceStateTask = Concurrency::task<void>([this] () {
		std::unique_ptr<DirectX::CommonStates> states(new DirectX::CommonStates(m_d3dDevice.Get()));
		m_padBlendState = std::unique_ptr<ID3D11BlendState>(states->AlphaBlend());
	});

	(drumkit2DTask && deviceStateTask).then([this] () {
		m_loadingComplete = true;
	});
}

void DrumkitRenderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();
}

void DrumkitRenderer::Update(float timeTotal, float timeDelta)
{
	m_timeTotal = timeTotal;
	(void) timeDelta; // Unused parameter.

	// Update pad positions
	std::vector<std::unique_ptr<Playable2D> >::iterator iter = m_2dpads.begin();

	while (iter != m_2dpads.end())
	{
		Playable2D* pad = (*iter).get();
		pad->Update(timeTotal);
		++iter;
	}
}

void DrumkitRenderer::Render()
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		midnightBlue
		);

	m_d3dContext->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	// Only continue after everything has loaded (loading is asynchronous).
	if (!m_loadingComplete)
	{
		return;
	}

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	RECT bgrect = {
		0, 0,
		static_cast<long>(m_renderTargetSize.Width),
		static_cast<long>(m_renderTargetSize.Height)
	};

	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_padBlendState.get());
	m_spriteBatch->Draw(m_bgtex, bgrect);
	std::vector<std::unique_ptr<Playable2D> >::iterator iter = m_2dpads.begin();

	while (iter != m_2dpads.end())
	{
		Playable2D* pad = (*iter).get();
		FRECT rel = pad->DestinationRect();
		RECT abs = {
			(long)(rel.left * m_renderTargetSize.Width),
			(long)(rel.top * m_renderTargetSize.Height),
			(long)(rel.right * m_renderTargetSize.Width),
			(long)(rel.bottom * m_renderTargetSize.Height)
		};
		m_spriteBatch->Draw(pad->Texture(), abs, nullptr, pad->Color(), pad->Rotation(), pad->Origin(), pad->Effects(), pad->LayerDepth());
		++iter;
	}

	m_spriteBatch->Draw(m_locktex, bgrect);
	m_spriteBatch->End();
}

void DrumkitRenderer::Tap(float x, float y)
{
	// check pads
	POINT pt = { (long)x, (long)y };
	std::vector<std::unique_ptr<Playable2D> >::reverse_iterator iter = m_2dpads.rbegin();

	while (iter != m_2dpads.rend())
	{
		FRECT pos = (*iter)->Position();
		RECT abs = {
			(long)(pos.left * m_renderTargetSize.Width),
			(long)(pos.top * m_renderTargetSize.Height),
			(long)(pos.right * m_renderTargetSize.Width),
			(long)(pos.bottom * m_renderTargetSize.Height)
		};
		if (pt.x > abs.left && pt.x < abs.right && pt.y > abs.top && pt.y < abs.bottom) {
			(*iter)->Play(m_timeTotal);
			m_player.PlaySound((*iter)->SampleIndex());
			break;
		}
		++iter;
	}
}

void DrumkitRenderer::Suspend()
{
	m_player.Suspend();
}

void DrumkitRenderer::Resume()
{
	m_player.Resume();
}
