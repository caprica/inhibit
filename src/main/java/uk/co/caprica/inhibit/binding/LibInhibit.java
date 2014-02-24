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

package uk.co.caprica.inhibit.binding;

import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 * Native library interface.
 */
public interface LibInhibit extends Library {

    /**
     * Native library instance.
     */
    LibInhibit INSTANCE = (LibInhibit) Native.loadLibrary("inhibit", LibInhibit.class);

    /**
     * Inhibit the screen-saver.
     *
     * @param applicationName name of the application
     * @param inhibitReason why the screensaver is being inhibited
     * @return inhibit cookie on success, zero on error
     */
    int inhibit(String applicationName, String inhibitReason);

    /**
     * Uninhibit the screen-saver.
     *
     * @param cookie inhibit cookie
     * @return <code>true</code> on success; <code>false</code> otherwise
     */
    boolean uninhibit(int cookie);
}
