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

package uk.co.caprica.inhibit;

import uk.co.caprica.inhibit.binding.LibInhibit;

/**
 * Inhibit wrapper component.
 */
public final class Inhibit {

    /**
     * Current inhibit cookie.
     */
    private Integer cookie;

    /**
     * Inhibit the screen-saver.
     *
     * @param applicationName name of the application
     * @param inhibitReason why the screensaver is being inhibited
     * @return <code>true</code> on success; <code>false</code> otherwise
     */
    public boolean inhibit(String applicationName, String inhibitReason) {
        if (cookie == null) {
            cookie = LibInhibit.INSTANCE.inhibit(applicationName, inhibitReason);
            return cookie != 0;
        }
        else {
            throw new IllegalStateException("Already inhibited");
        }
    }

    /**
     * Uninhibit the screen-saver.
     *
     * @return <code>true</code> on success; <code>false</code> otherwise
     */
    public boolean uninhibit() {
        if (cookie != null) {
            return LibInhibit.INSTANCE.uninhibit(cookie);
        }
        else {
            throw new IllegalStateException("Not currently inhibited");
        }
    }
}
