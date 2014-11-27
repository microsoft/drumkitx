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

#include <vector>

#include "ITappable.h"

namespace DrumkitXComp
{
    public ref class Recorder sealed
    {
    public:
	    Recorder(ITappable^ tappable);

	    void Play();
	    void Record(float starttime);
	    void Stop();

	    bool IsRecording();
	    bool IsPlaying();

	    void Tap(float x, float y, float time);

	    void AdvancePlayback(float total, float delta);

    private:
	    struct TapEvent {
		    TapEvent(float time, float x, float y) : Time(time), X(x), Y(y) {}
		    float Time;
		    float X;
		    float Y;
	    };

	    std::vector<TapEvent> m_events;

	    bool m_recording;
	    bool m_playing;
	    float m_recordingStartTime;
	    float m_playbackPosition;
	    ITappable^ m_tappable;
	    std::vector<TapEvent>::iterator m_nextEvent;
    };
}
