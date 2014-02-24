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

import com.sun.jna.NativeLibrary;

/**
 * Simple test to inhibit the screen-saver.
 */
public class InhibitTest {

    private static final String NATIVE_LIBRARY_PATH = null;

    public static void main(String[] args) throws Exception {
        if (NATIVE_LIBRARY_PATH != null) {
            NativeLibrary.addSearchPath("inhibit", NATIVE_LIBRARY_PATH);
        }

        Inhibit inhibit = new Inhibit();

        inhibit.inhibit("my test app", "because");
        System.out.println("INHIBITED, WAITING");

        // Assume a 60 second idle period for the screensaver
        Thread.sleep(70000);

        inhibit.uninhibit();
        System.out.println("UNINHIBITED, WAITING");
        Thread.sleep(90000);

        System.out.println("ALL DONE");
    }
}
