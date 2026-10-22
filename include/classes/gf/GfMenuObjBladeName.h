#ifndef CLASSES_GF_GFMENUOBJBLADENAME_H
#define CLASSES_GF_GFMENUOBJBLADENAME_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B601E0
class GfMenuObjBladeName : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjBladeName(unsigned int handle);
    virtual ~GfMenuObjBladeName();  // slot 0
    // the blade name's call context (attached under 0x81): start it and open the name, close it
    static void open(GfMenuCallContext* context);
    static void close();
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqStart();
    bool seqApperRare();
    bool seqApperWait();
    bool seqApperNormal();
    // fades the name in: 1.0.0's, inline here as 3.0.1 keeps no copy (seqApperRare inlines it)
    inline bool seqApperName();
    bool seqLeave();
    GfMenuSequence<GfMenuObjBladeName, 8> m_seq;
    // seqLeave: LAY_main's fade-out has started (the name is not the original's)
    bool m_leaving;
};
}  // namespace gf

#endif
