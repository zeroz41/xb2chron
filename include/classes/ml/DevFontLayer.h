#ifndef CLASSES_ML_DEVFONTLAYER_H
#define CLASSES_ML_DEVFONTLAYER_H

#include "classes/ml/WorkObj.h"
#include "classes/ml/FontLayer.h"
#include "mm/Col4.h"

namespace ml { class RenderContext; }

namespace ml {
// table 0x7100B75BA8
class DevFontLayer : public ::ml::WorkObj {
public:
    // a queued font command; m_type: 0 text, 1 colour, 2 shadow colour, 3 scale, 4 (0x1F4's value), 5 style,
    // 6 shadow, 7 the end (the derived commands' and members' names are not the original's)
    struct LAYER_QUE {
        int m_type;
    };
    // the text (copied in just above it) at x, y
    struct QUE_FONT : LAYER_QUE {
        short m_x;
        short m_y;
    };
    struct QUE_COL : LAYER_QUE {
        mm::Col4 m_col;
    };
    struct QUE_SCALE : LAYER_QUE {
        float m_x;
        float m_y;
    };
    struct QUE_STYLE : LAYER_QUE {
        FONT_STYLE m_style;
    };
    struct QUE_SHADOW : LAYER_QUE {
        int m_on;
    };

    // its queue (0x2000 bytes of the frame's scratch memory when DevGraph exists)
    DevFontLayer(const char* name, WorkObj* parent);
    // inline: its copies are weak, in the module's tail (wkUpdate is the key function)
    virtual ~DevFontLayer() {}  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogout();  // slot 15

    // draws or drops the queued commands (DevFont::fontLayerFlush)
    void flush(bool on);
    // runs the queue up to its end command
    void renderQue(const RenderContext* ctx, const LAYER_QUE** que);
    // a command of type T from the frame's scratch memory, none without a queue (inline; the names are not the
    // original's)
    template <typename T>
    T* newQue();
    void pushQue(const LAYER_QUE* que);
    // the colours back to their defaults and a fresh queue of m_queMax commands (inline: the constructor and
    // wkTail; the name is not the original's)
    void resetQue();
    void queColor(const mm::Col4& col);
    void queShadowColor(const mm::Col4& col);
    void queShadow(bool on);
    void queScale(float x, float y);
    void queStyle(FONT_STYLE style);

    // the names below are not the original's
    const LAYER_QUE** m_que;   // 0x1A8
    unsigned int m_queNum;     // 0x1B0
    float m_scaleX;            // 0x1B4
    float m_scaleY;            // 0x1B8
    FONT_STYLE m_style;        // 0x1BC
    const FontLayer* m_layer;  // 0x1C0 the FontLayer it serves (FontLayer's constructor sets it)
    bool m_shadow;             // 0x1C8
    mm::Col4 m_shadowCol;      // 0x1CC
    mm::Col4 m_col;            // 0x1DC
    bool m_done;               // 0x1EC set: wkUpdate sends event 0 and logout may go on
    int m_queMax;              // 0x1F0 0x400 (the queue's 0x2000 bytes)
    int m_cmd4Value;           // 0x1F4 command 4 sets it
};
}  // namespace ml

#endif
