/*
 * Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package com.sun.prism.es2;

import com.sun.glass.ui.monocle.AcceleratedScreen;

class MonocleGLContext extends GLContext {

    private AcceleratedScreen accScreen;

    MonocleGLContext(long nativeCtxInfo) {
        this.nativeCtxInfo = nativeCtxInfo;
    }

    MonocleGLContext(GLDrawable drawable, GLPixelFormat pixelFormat,
                          boolean vSyncRequest, AcceleratedScreen accScreen,
                          long nativeCtxInfo) {
        this.accScreen = accScreen;
        this.nativeCtxInfo = nativeCtxInfo;
    }

    @Override
    long getNativeHandle() {
        return 0l;
    }

    @Override
    void makeCurrent(GLDrawable drawable) {
        if (drawable != null) {
            accScreen.enableRendering(true);
        } else {
            accScreen.enableRendering(false);
        }
    }
}
