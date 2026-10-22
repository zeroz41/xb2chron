#ifndef CLASSES_UI_UIIMAGEOBJECT_H
#define CLASSES_UI_UIIMAGEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace layer { class LayerBase; }
namespace ml { class ScnRenderDrCapture; }
namespace ui { class UILayoutObject; }

namespace ui {
// table 0x7100B74DD0; an image: a default layer object drawing a resource's icons (or a stream's contents), or a
// texture object drawing a capture
class UIImageObject : public ::ui::UIObject {
public:
    // 1.0.0's are out of line (0x71006DF618, 0x71006DF658); 3.0.1's creates inline the first
    UIImageObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name);
    UIImageObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name, unsigned int type);
    virtual ~UIImageObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    virtual void changeBin(void const*);  // slot 10
    // an image under the parent (or none) of the resource, a mask object when asked; it shows the stream contents
    // given (0: none)
    static UIImageObject* create(UILayoutObject* parent, const void* resource, unsigned int contents,
                                 const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator, bool mask);
    // an image under the parent (or none) drawing the capture's texture
    static UIImageObject* create(UILayoutObject* parent, ml::ScnRenderDrCapture* capture,
                                 const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator);
    void setMaskObject(UIImageObject* mask);  // masked by that mask image
    void setImageIndex(unsigned short index);
    unsigned short getImageMax();
    unsigned short getImageIndex();
    void setHFlip(bool flip);
    void setVFlip(bool flip);
    void setExtType(unsigned int type);  // 1-4: a gauge
    unsigned int getExtType();
    void setExtParam(float param);  // the gauge's value
    bool hasAnimation();
    void startAnimation(const char* name, bool loop);
    void startAnimationFromID(unsigned int id, bool loop);
    void startAnimationFromIndex(unsigned int index, bool loop);
    void stopAnimation();
    bool isPlayingAnimation();
    float getAnimationPlaybackLength();
    void setAnimationPlaybackTime(float time);
    static mm::mtl::RTTI m_rtti;
    // the stream contents it shows (the names are not the original's)
    unsigned int m_contents;  // create's; 0: it shows its resource's icons
    unsigned short m_index;   // setImageIndex's: the contents' image it shows
    ml::ScnRenderDrCapture* m_capture;  // the capture create draws (none: a default object)
    bool m_loop;  // the start functions' bool (the name is not the original's)
    unsigned char pad_119[0x7];
};
}  // namespace ui

#endif
