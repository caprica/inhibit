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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <dbus/dbus.h>
#include <dbus/dbus-glib.h> 

#include "inhibit.h"

inhibit_t *create(const char *service_name, const char *object_path, const char *interface) {
    GError *error = NULL;
    DBusGConnection *connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!connection) {
        g_printerr("Failed to get dbus connection: %s\n", error->message);
        g_error_free(error);
        return NULL;
    }
    DBusGProxy *proxy = dbus_g_proxy_new_for_name(connection, service_name, object_path, interface);
    if (!proxy) {
        g_printerr("Failed to create proxy\n");
        return NULL;
    }
    inhibit_t *inhibit = malloc(sizeof(inhibit_t));
    if (!inhibit) {
        g_object_unref(proxy);
        return NULL;
    }
    inhibit->connection = connection;
    inhibit->proxy = proxy;
    return inhibit;
}

void destroy(inhibit_t *inhibit) {
    if (!inhibit) {
        return;
    }
    if (inhibit->proxy) {
        g_object_unref(inhibit->proxy);
    }
    free(inhibit);
}

unsigned int inhibit(const char *application_name, const char *inhibit_reason) {
    inhibit_t *inhibit = create(FREEDESKTOP_SERVICE_NAME, FREEDESKTOP_OBJECT_PATH, FREEDESKTOP_INTERFACE);
    if (!inhibit) {
        return 0;
    }
    unsigned int cookie = 0;
    GError *error = NULL;
    gboolean result = dbus_g_proxy_call(inhibit->proxy, "Inhibit", &error,
        G_TYPE_STRING, application_name,
        G_TYPE_STRING, inhibit_reason,
        G_TYPE_INVALID,
        G_TYPE_UINT, &cookie,
        G_TYPE_INVALID);
    if (!result) {
        g_printerr("Failed to invoke proxy for inhibit: %s\n", error->message);
        g_error_free(error);
    }
    destroy(inhibit);
    return cookie;
}

bool uninhibit(unsigned int cookie) {
    inhibit_t *inhibit = create(FREEDESKTOP_SERVICE_NAME, FREEDESKTOP_OBJECT_PATH, FREEDESKTOP_INTERFACE);
    if (!inhibit) {
        return false;
    }
    GError *error = NULL;
    gboolean result = dbus_g_proxy_call(inhibit->proxy, "UnInhibit", &error,
        G_TYPE_UINT, cookie,
        G_TYPE_INVALID,
        G_TYPE_INVALID);
    if (!result) {
        g_printerr("Failed to invoke proxy for uninhibit: %s\n", error->message);
        g_error_free(error);
        destroy(inhibit);
        return false;
    }
    destroy(inhibit);
    return true;
}
