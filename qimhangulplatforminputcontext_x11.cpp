/* qimhangul-qt5 - Qt input context plugin for Hangul
 * Based on qimhangul
 * Copyright (C) 2004 Choe Hwanjin
 * Copyright (C) 2015 Shinjo Park
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <ctype.h>

#include <QWidget>
#include <QX11Info>

#include "hangul.h"
#include "qimhangulplatforminputcontext.h"

#include <X11/Xlib.h>

void QHangulPlatformInputContext::setModeInfo(int mode)
{
    Display* display = NULL;
    int screen = 0;

    display = QX11Info::display();
    screen = QX11Info::appScreen();

    if (display != NULL) {
	long data = mode;
	Window window = RootWindow(display, screen);
	Atom status = XInternAtom(display, "_HANGUL_INPUT_MODE", False);
	Atom type = XInternAtom(display, "INTEGER", False);

	if (window != None && status != None && type != None) {
	    XChangeProperty(display, window, status, type,
		    32, PropModeReplace, (const unsigned char *)&data, 1);
	}
    }
}
