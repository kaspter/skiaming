/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm.h"
#include "SkCanvas.h"
#include "SkColorPriv.h"
#include "SkShader.h"

#include "SkArithmeticMode.h"
#include "SkGradientShader.h"
#define WW  100
#define HH  32

static SkBitmap make_bm() {
    SkBitmap bm;
    bm.setConfig(SkBitmap::kARGB_8888_Config, WW, HH);
    bm.allocPixels();
    bm.eraseColor(0);
    return bm;
}

static SkBitmap make_src() {
    SkBitmap bm = make_bm();
    SkCanvas canvas(bm);
    SkPaint paint;
    SkPoint pts[] = { {0, 0}, {SkIntToScalar(WW), SkIntToScalar(HH)} };
    SkColor colors[] = {
        SK_ColorBLACK, SK_ColorGREEN, SK_ColorCYAN,
        SK_ColorRED, SK_ColorMAGENTA, SK_ColorWHITE
    };
    SkShader* s = SkGradientShader::CreateLinear(pts, colors, NULL, SK_ARRAY_COUNT(colors),
                                                 SkShader::kClamp_TileMode);
    paint.setShader(s)->unref();
    canvas.drawPaint(paint);
    return bm;
}

static SkBitmap make_dst() {
    SkBitmap bm = make_bm();
    SkCanvas canvas(bm);
    SkPaint paint;
    SkPoint pts[] = { {0, SkIntToScalar(HH)}, {SkIntToScalar(WW), 0} };
    SkColor colors[] = {
        SK_ColorBLUE, SK_ColorYELLOW, SK_ColorBLACK, SK_ColorGREEN, SK_ColorGRAY
    };
    SkShader* s = SkGradientShader::CreateLinear(pts, colors, NULL, SK_ARRAY_COUNT(colors),
                                                 SkShader::kClamp_TileMode);
    paint.setShader(s)->unref();
    canvas.drawPaint(paint);
    return bm;
}

static SkBitmap make_arith(const SkBitmap& src, const SkBitmap& dst,
                           const SkScalar k[]) {
    SkBitmap bm = make_bm();
    SkCanvas canvas(bm);
    SkPaint paint;
    canvas.drawBitmap(dst, 0, 0, NULL);
    SkXfermode* xfer = SkArithmeticMode::Create(k[0], k[1], k[2], k[3]);
    paint.setXfermode(xfer)->unref();
    canvas.drawBitmap(src, 0, 0, &paint);
    return bm;
}

static void show_k_text(SkCanvas* canvas, SkScalar x, SkScalar y, const SkScalar k[]) {
    SkPaint paint;
    paint.setTextSize(SkIntToScalar(24));
    paint.setAntiAlias(true);
    for (int i = 0; i < 4; ++i) {
        SkString str;
        str.appendScalar(k[i]);
        SkScalar width = paint.measureText(str.c_str(), str.size());
        canvas->drawText(str.c_str(), str.size(), x, y + paint.getTextSize(), paint);
        x += width + SkIntToScalar(10);
    }
}

class ArithmodeGM : public skiagm::GM {
public:
    ArithmodeGM () {}

protected:

    virtual SkString onShortName() {
        return SkString("arithmode--3.SkArithmeticMode��ʹ��,canvas��drawBitmap");
    }

    virtual SkISize onISize() { return SkISize::Make(640, 480); }

    virtual void onDraw(SkCanvas* canvas) {
        SkBitmap src = make_src();
        SkBitmap dst = make_dst();

        const SkScalar one = SK_Scalar1;
        static const SkScalar K[] = {
            0, 0, 0, 0,
            0, 0, 0, one,
            0, one, 0, 0,
            0, 0, one, 0,
            0, one, one, 0,
            0, one, -one, 0,
            0, one/2, one/2, 0,
            0, one/2, one/2, one/4,
            0, one/2, one/2, -one/4,
            one/4, one/2, one/2, 0,
            -one/4, one/2, one/2, 0,
        };

        const SkScalar* k = K;
        const SkScalar* stop = k + SK_ARRAY_COUNT(K);
        SkScalar y = 0;
        SkScalar gap = SkIntToScalar(src.width() + 20);
        while (k < stop) {
            SkScalar x = 0;
            SkBitmap res = make_arith(src, dst, k);
            canvas->drawBitmap(src, x, y, NULL);
            x += gap;
            canvas->drawBitmap(dst, x, y, NULL);
            x += gap;
            canvas->drawBitmap(res, x, y, NULL);
            x += gap;
            show_k_text(canvas, x, y, k);
            k += 4;
            y += SkIntToScalar(src.height() + 12);
        }
    }

private:
    typedef GM INHERITED;
};

///////////////////////////////////////////////////////////////////////////////

static skiagm::GM* MyFactory(void*) { return new ArithmodeGM; }
static skiagm::GMRegistry reg(MyFactory);
