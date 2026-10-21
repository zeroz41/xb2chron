#ifndef GF_GFMENUOBJDUMMYTUTORIAL_H
#define GF_GFMENUOBJDUMMYTUTORIAL_H

namespace gf { class GfMenuCallContext; }

namespace gf {
// a tutorial menu object (attached object 0x79); its functions take no object
class GfMenuObjDummyTutorial {
public:
    struct OpenParam {
        unsigned int m_id;  // what GfMenuManager::openDummyTutorial is given; sent with the open event (0x21)
    };
    static void open(GfMenuCallContext* context, const OpenParam& param);
};
}  // namespace gf

#endif
