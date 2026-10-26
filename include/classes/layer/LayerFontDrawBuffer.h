#ifndef CLASSES_LAYER_LAYERFONTDRAWBUFFER_H
#define CLASSES_LAYER_LAYERFONTDRAWBUFFER_H

#include "classes/layer/LayerFontTag.h"

namespace layer { class LayerObjFont; }

namespace layer {
// table 0x7100B805C8
class LayerFontDrawBuffer : public ::layer::LayerFontTag {
public:
    LayerFontDrawBuffer(const LayerFontResObj* res, const LayerFontStyleObj* style, const LyrFontStyleData* styleData,
                        const LayerFontIconObj* icon, LayerFontSetting setting, LayerObjFont* obj);
    // its D1 is LayerTag's (the table's slot 0); the D0 alone is emitted
    virtual ~LayerFontDrawBuffer() {}  // slot 0
    virtual void createFontCode(unsigned short code);  // slot 9
    virtual void createRubyFontCode(unsigned short code);  // slot 10
    virtual void createFontIcon(unsigned short code);  // slot 11
    virtual void createLineBreak();  // slot 12

    void* createChar(const unsigned char* text);
    void createWorkBuffer(const LayerTagWork& work, const unsigned char* text);
    void endWorkSetup();

    // The field names are not the original's.
    unsigned char pad_4A8[0x8];
    void* m_buffer;  // 0x4B0: what createChar returns
    LayerObjFont* m_obj;  // 0x4B8: the constructor's
    unsigned char pad_4C0[0x10];
};
}  // namespace layer

#endif
