#ifndef CLASSES_GF_GFCOMMODEL_H
#define CLASSES_GF_GFCOMMODEL_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B667B8
class GfComModel : public ::gf::GfComponent {
public:
    class ViewerListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComModel();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x10d8];
    // each gf::VFPARTS's opacity: GfVolumeFade::applyFadeRatio stores 1 - the part's fade ratio (the name is not
    // the original's)
    float m_partsAlpha[6];
};
}  // namespace gf

#endif
