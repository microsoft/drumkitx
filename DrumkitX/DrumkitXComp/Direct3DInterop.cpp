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
#include "Direct3DInterop.h"

#include "Direct3DContentProvider.h"

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;

/**
 * @class Direct3DInterop
 * @brief Acts as a bridge between the managed and native worlds, relaying user
 *        input and device events as needed to the native parts. It has methods
 *        for starting and stopping the audio engine and a handler for pointer
 *        pressed event related to recording and playback of drum taps.
 */

namespace DrumkitXComp
{

Direct3DInterop::Direct3DInterop() :
	m_timer(ref new BasicTimer())
{
	m_renderer = ref new DrumkitRenderer();
	m_renderer->Initialize();
	m_recorder = ref new Recorder(m_renderer);
}

Direct3DInterop::~Direct3DInterop()
{
}

IDrawingSurfaceContentProvider^ Direct3DInterop::CreateContentProvider()
{
	ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
	return reinterpret_cast<IDrawingSurfaceContentProvider^>(provider.Detach());
}

// IDrawingSurfaceManipulationHandler
void Direct3DInterop::SetManipulationHost(DrawingSurfaceManipulationHost^ manipulationHost)
{
	manipulationHost->PointerPressed +=
		ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerPressed);
}

void Direct3DInterop::RenderResolution::set(Windows::Foundation::Size renderResolution)
{
	if (renderResolution.Width  != m_renderResolution.Width ||
		renderResolution.Height != m_renderResolution.Height)
	{
		m_renderResolution = renderResolution;

		if (m_renderer)
		{
			m_renderer->UpdateForRenderResolutionChange(m_renderResolution.Width, m_renderResolution.Height);
			RecreateSynchronizedTexture();
		}
	}
}

// Event Handler
void Direct3DInterop::OnPointerPressed(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
	float x = args->CurrentPoint->Position.X * (m_renderResolution.Width / WindowBounds.Width);
	float y = args->CurrentPoint->Position.Y * (m_renderResolution.Height / WindowBounds.Height);
	m_renderer->Tap(x, y);
	m_recorder->Tap(x, y, m_timer->Total);
}

// Interface With Direct3DContentProvider
HRESULT Direct3DInterop::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host)
{
	m_renderer->UpdateForWindowSizeChange(WindowBounds.Width, WindowBounds.Height);
	m_renderer->UpdateForRenderResolutionChange(m_renderResolution.Width, m_renderResolution.Height);

	// Restart timer after renderer has finished initializing.
	m_timer->Reset();

	return S_OK;
}

void Direct3DInterop::Disconnect()
{
}

HRESULT Direct3DInterop::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty)
{
	*contentDirty = true;

	return S_OK;
}

HRESULT Direct3DInterop::GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle)
{
	m_timer->Update();
	m_renderer->Update(m_timer->Total, m_timer->Delta);
	m_renderer->Render();

	// is recorder playing?
	if (m_recorder->IsPlaying())
	{
		m_recorder->AdvancePlayback(m_timer->Total, m_timer->Delta);
	}

	RequestAdditionalFrame();

	return S_OK;
}

ID3D11Texture2D* Direct3DInterop::GetTexture()
{
	return m_renderer->GetTexture();
}

void Direct3DInterop::StartAudioEngine()
{
	m_renderer->Resume();
}

void Direct3DInterop::StopAudioEngine()
{
	m_renderer->Suspend();
}

void Direct3DInterop::StartRecording()
{
	m_recorder->Record(m_timer->Total);
}

void Direct3DInterop::StopRecordingOrPlayback()
{
	m_recorder->Stop();
}

void Direct3DInterop::StartPlayback()
{
	m_recorder->Play();
}

}
