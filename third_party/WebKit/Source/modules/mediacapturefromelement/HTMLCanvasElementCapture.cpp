// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"
#include "modules/mediacapturefromelement/HTMLCanvasElementCapture.h"

#include "core/dom/ExceptionCode.h"
#include "core/html/HTMLCanvasElement.h"
#include "modules/mediacapturefromelement/CanvasCaptureMediaStreamTrack.h"
#include "modules/mediastream/MediaStream.h"
#include "public/platform/Platform.h"
#include "public/platform/WebCanvasCaptureHandler.h"
#include "public/platform/WebMediaStream.h"
#include "public/platform/WebMediaStreamTrack.h"

namespace {
const double kDefaultFrameRate = 60.0;
} // anonymous namespace

namespace blink {

MediaStream* HTMLCanvasElementCapture::captureStream(HTMLCanvasElement& element, ExceptionState& exceptionState)
{
    if (!element.originClean()) {
        exceptionState.throwDOMException(SecurityError, "Canvas is not origin-clean.");
        return MediaStream::create(element.executionContext());
    }

    WebMediaStreamTrack track;
    WebSize size(element.width(), element.height());
    OwnPtr<WebCanvasCaptureHandler> handler = adoptPtr(Platform::current()->createCanvasCaptureHandler(size, kDefaultFrameRate, &track));
    ASSERT(handler);
    if (!handler) {
        exceptionState.throwDOMException(NotSupportedError, "No CanvasCapture handler can be created.");
        return MediaStream::create(element.executionContext());
    }

    MediaStreamTrackVector tracks;
    tracks.append(CanvasCaptureMediaStreamTrack::create(track, &element, handler.release()));
    return MediaStream::create(element.executionContext(), tracks);
}

} // namespace blink