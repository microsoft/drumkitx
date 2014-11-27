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
