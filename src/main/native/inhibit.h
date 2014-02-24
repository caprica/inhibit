/*
 * This file is part of Inhibit.
 *
 * Inhibit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Inhibit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Inhibit.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 Caprica Software Limited.
 */

#ifndef _INHIBIT_H
#define _INHIBIT_H

/**
 * DBus service and object names for the "freedesktop" screensaver.
 */
static const char *FREEDESKTOP_SERVICE_NAME = "org.freedesktop.ScreenSaver";
static const char *FREEDESKTOP_OBJECT_PATH  = "/org/freedesktop/ScreenSaver";
static const char *FREEDESKTOP_INTERFACE    = "org.freedesktop.ScreenSaver";

/**
 * Private inhibit structure.
 */
typedef struct inhibit_t {
    DBusGConnection *connection;
    DBusGProxy      *proxy;
} inhibit_t;

/**
 * Create a private inhibit structure.
 *
 * @param service_name DBus service name
 * @param object_path DBus object path
 * @param interface DBus interface name
 * @return private inhibit structure, or NULL on error
 */
inhibit_t *create(const char *service_name, const char *object_path, const char *interface);

/**
 * Destroy the private inhibit structure.
 *
 * @param inhibit
 */
void destroy(inhibit_t *inhibit);

/**
 * Inhibit the screensaver.
 *
 * @param application_name
 * @param inhibit_reason
 * @return cookie (to use subsequently for uninhibit), or zero on error
 */
extern unsigned int inhibit(const char *application_name, const char *inhibit_reason);

/**
 * Uninhibit the screensaver.
 *
 * @param cookie cookie obtained in a prior call to inhibit
 * @return true on success, false on error
 */
extern bool uninhibit(unsigned int cookie);

#endif // _INHIBIT_H
