/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm.h"
#include "SkCanvas.h"
#include "SkShader.h"
#include "SkStippleMaskFilter.h"

namespace skiagm {

/**
 * Stress test the samplers by rendering a textured glyph with a mask and
 * an AA clip
 */
class SamplerStressGM : public GM {
public:
    SamplerStressGM()
    : fTextureCreated(false)
    , fShader(NULL)
    , fMaskFilter(NULL) {
    }

    virtual ~SamplerStressGM() {
    }

protected:
    virtual SkString onShortName() {
        return SkString("samplerstress--104");
    }

    virtual SkISize onISize() {
        return make_isize(640, 480);
    }

    /**
     * Create a red & green stripes on black texture
     */
    void createTexture() {
        if (fTextureCreated) {
            return;
        }

        static const int xSize = 16;
        static const int ySize = 16;

        fTexture.setConfig(SkBitmap::kARGB_8888_Config,
                           xSize,
                           ySize,
                           xSize*sizeof(SkColor));

        fTexture.allocPixels();
        fTexture.lockPixels();
        SkPMColor* addr = fTexture.getAddr32(0, 0);

        for (int y = 0; y < ySize; ++y) {
            for (int x = 0; x < xSize; ++x) {
                addr[y*xSize+x] = SkPreMultiplyColor(SK_ColorBLACK);

                if ((y % 5) == 0) {
                    addr[y*xSize+x] = SkPreMultiplyColor(SK_ColorRED);
                }
                if ((x % 7) == 0) {
                    addr[y*xSize+x] = SkPreMultiplyColor(SK_ColorGREEN);
                }
            }
        }

        fTexture.unlockPixels();

        fTextureCreated = true;
    }

    void createShader() {
        if (NULL != fShader.get()) {
            return;
        }

        createTexture();

        fShader.reset(SkShader::CreateBitmapShader(fTexture,
                                                   SkShader::kRepeat_TileMode,
                                                   SkShader::kRepeat_TileMode));
    }

    void createMaskFilter() {
        if (NULL != fMaskFilter.get()) {
            return;
        }

        fMaskFilter.reset(SkNEW(SkStippleMaskFilter));
    }

    virtual void onDraw(SkCanvas* canvas) {

        createShader();
        createMaskFilter();

        canvas->save();

        // draw a letter "M" with a green & red striped texture and a
        // stipple mask with a round rect soft clip
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setTextSize(72);
        paint.setShader(fShader.get());
        paint.setMaskFilter(fMaskFilter.get());

        SkRect temp;
        temp.set(SkIntToScalar(115),
                 SkIntToScalar(75),
                 SkIntToScalar(144),
                 SkIntToScalar(110));

        SkPath path;
        path.addRoundRect(temp, SkIntToScalar(5), SkIntToScalar(5));

        canvas->clipPath(path, SkRegion::kReplace_Op, true); // AA is on

        canvas->drawText("M", 1,
                         SkIntToScalar(100), SkIntToScalar(100),
                         paint);

        canvas->restore();

        // Now draw stroked versions of the "M" and the round rect so we can
        // see what is going on
        SkPaint paint2;
        paint2.setColor(SK_ColorBLACK);
        paint2.setAntiAlias(true);
        paint2.setTextSize(72);
        paint2.setStyle(SkPaint::kStroke_Style);
        paint2.setStrokeWidth(1);
        canvas->drawText("M", 1,
                         SkIntToScalar(100), SkIntToScalar(100),
                         paint2);

        paint2.setColor(SK_ColorGRAY);

        canvas->drawPath(path, paint2);
    }

private:
    SkBitmap      fTexture;
    bool          fTextureCreated;
    SkAutoTUnref<SkShader>     fShader;
    SkAutoTUnref<SkMaskFilter> fMaskFilter;

    typedef GM INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

static GM* MyFactory(void*) { return new SamplerStressGM; }
static GMRegistry reg(MyFactory);

}
