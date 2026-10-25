#ifndef CLASSES_GF_GFAPPENDWIRE_H
#define CLASSES_GF_GFAPPENDWIRE_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// an object's wire (GfAppendWire.cpp; only the members GfGameUtil's wire helpers call are declared)
class GfAppendWire {
public:
    void startWire(GF_OBJ_HANDLE* target, float time);
    void startWireWithClose(GF_OBJ_HANDLE* target, float time, float, float);
    void endWire(float time);
};

}  // namespace gf

#endif
