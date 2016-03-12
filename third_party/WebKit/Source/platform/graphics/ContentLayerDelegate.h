/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ContentLayerDelegate_h
#define ContentLayerDelegate_h

#include "platform/PlatformExport.h"
#include "platform/geometry/IntSize.h"
#include "public/platform/WebContentLayerClient.h"
#include "wtf/Allocator.h"
#include "wtf/Noncopyable.h"
#include "wtf/PassOwnPtr.h"

class SkCanvas;

namespace gfx {
class Rect;
}

namespace blink {

class GraphicsContext;
class IntRect;
class PaintController;

class PLATFORM_EXPORT GraphicsContextPainter {
public:
    virtual IntRect interestRect() = 0;
    virtual void paint(GraphicsContext&, const IntRect* interestRect) = 0;
    virtual PaintController* paintController() = 0;

protected:
    virtual ~GraphicsContextPainter() { }
};

class PLATFORM_EXPORT ContentLayerDelegate : public WebContentLayerClient {
    WTF_MAKE_NONCOPYABLE(ContentLayerDelegate);
    USING_FAST_MALLOC(ContentLayerDelegate);
public:
    explicit ContentLayerDelegate(GraphicsContextPainter*);
    ~ContentLayerDelegate() override;

    gfx::Rect paintableRegion() override;

    // WebContentLayerClient implementation.
    void paintContents(WebDisplayItemList*, WebContentLayerClient::PaintingControlSetting = PaintDefaultBehavior) override;
    size_t approximateUnsharedMemoryUsage() const override;

private:
    GraphicsContextPainter* m_painter;
};

} // namespace blink

#endif // ContentLayerDelegate_h