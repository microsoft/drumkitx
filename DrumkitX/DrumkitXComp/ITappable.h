/**
 * Copyright (c) 2013 Nokia Corporation.
 */

#pragma once

/**
 * @class ITappable
 * @brief Interface for tappable object.
 */
namespace DrumkitXComp
{
    public interface class ITappable
    {
    public:
	    void Tap(float x, float y);
    };
}
