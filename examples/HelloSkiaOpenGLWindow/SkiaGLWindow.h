#pragma once
#include "QSkiaOpenGLWindow.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"
static SkPath star()
{
    const SkScalar R = 115.2f, C = 128.0f;
    SkPath path;
    path.moveTo(C + R, C);
    for (int i = 1; i < 8; ++i) {
        SkScalar a = 2.6927937f * i;
        path.lineTo(C + R * cos(a), C + R * sin(a));
    }
    return path;
}
class SkiaGLWindow : public QSkiaOpenGLWindow {
    Q_OBJECT
public:
    virtual void onInit(int w, int h) override
    {
        const SkScalar intervals[] = { 10.0f, 5.0f, 2.0f, 5.0f };
        size_t count = sizeof(intervals) / sizeof(intervals[0]);
        m_effect = SkPathEffect::MakeCompose(
            SkDashPathEffect::Make(intervals, count, 0.0f),
            SkDiscretePathEffect::Make(10.0f, 4.0f));
        m_path = star();

        m_paint.setPathEffect(m_effect);
        m_paint.setStyle(SkPaint::kStroke_Style);
        m_paint.setStrokeWidth(2.0f);
        m_paint.setAntiAlias(true);
        m_paint.setColor(0xff4285F4);
    }
    virtual void onResize(int w, int h) override
    {

    }
    virtual void draw(SkCanvas* canvas, int elapsed) override
    {
        canvas->clear(SK_ColorWHITE);

        canvas->drawPath(m_path, m_paint);

        canvas->flush();
    }

private:
    SkPaint m_paint;
    SkPath m_path;
    sk_sp<SkPathEffect> m_effect = nullptr;
};
