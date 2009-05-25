/*
 * swindow.h - simple window handling functions header
 *
 * Copyright © 2008 Julien Danjou <julien@danjou.info>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef AWESOME_SWINDOW_H
#define AWESOME_SWINDOW_H

#include "draw.h"
#include "window.h"

/** A simple window. */
typedef struct simple_window_t
{
    /** The window object. */
    xcb_window_t window;
    /** The pixmap copied to the window object. */
    xcb_pixmap_t pixmap;
    /** The graphic context. */
    xcb_gcontext_t gc;
    /** The window geometry. */
    area_t geometry;
    struct
    {
        /** Internal geometry (matching X11 protocol) */
        area_t internal;
    } geometries;
    /** The window border */
    struct
    {
        /** The window border width */
        uint16_t width;
        /** The window border color */
        xcolor_t color;
    } border;
    /** Draw context */
    draw_context_t ctx;
    /** Orientation */
    orientation_t orientation;
    /** Opacity */
    double opacity;
} simple_window_t;

void simplewindow_init(simple_window_t *s,
                       int, area_t, uint16_t, const xcolor_t *,
                       orientation_t, const xcolor_t *, const xcolor_t *);

void simplewindow_wipe(simple_window_t *);

void simplewindow_move(simple_window_t *, int, int);
void simplewindow_resize(simple_window_t *, int, int);
void simplewindow_moveresize(simple_window_t *, area_t);
void simplewindow_refresh_pixmap_partial(simple_window_t *, int16_t, int16_t, uint16_t, uint16_t);
void simplewindow_border_width_set(simple_window_t *, uint32_t);
void simplewindow_border_color_set(simple_window_t *, const xcolor_t *);
void simplewindow_orientation_set(simple_window_t *, orientation_t);
void simplewindow_cursor_set(simple_window_t *, xcb_cursor_t);

/** Refresh the window content by copying its pixmap data to its window.
 * \param sw The simple window to refresh.
 */
static inline void
simplewindow_refresh_pixmap(simple_window_t *sw)
{
    simplewindow_refresh_pixmap_partial(sw, 0, 0, sw->geometry.width, sw->geometry.height);
}

/** Set a simplewindow's opacity.
 * \param opacity A value between 0 and 1 which describes the opacity.
 */
static inline void
simplewindow_opacity_set(simple_window_t *sw, double opacity)
{
    sw->opacity = opacity;
    if(sw->window != XCB_NONE)
        window_opacity_set(sw->window, opacity);
}

/** Get a simplewindow's opacity.
 * \return The opacity as a value between 0 and 1, or -1 if unset.
 */
static inline double
simplewindow_opacity_get(simple_window_t *sw)
{
    return sw->opacity;
}

#endif
// vim: filetype=c:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=80
