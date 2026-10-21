#ifndef CLASSES_GF_GFMENUCALLCONTEXT_H
#define CLASSES_GF_GFMENUCALLCONTEXT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B5E3F0; GfMenuCallManager releases it through reference_object.h
class GfMenuCallContext : public ::mm::mtl::ReferenceObject {
public:
    // what a menu reports back: GfMenuCallManager copies it from a UI event's parameters
    struct GfMenuResult {
        unsigned char pad_0[8];
    };
    GfMenuCallContext() : m_objectId(0), m_handle(0), m_terminated(false) {}
    virtual ~GfMenuCallContext();  // slot 0
    static GfMenuCallContext* create();
    int getState();
    bool isTerm() const;
    bool isActive() const;
    void reset();
    void terminate();
    void abort();
    bool popResult(GfMenuResult& result);
    void addResult(const GfMenuResult& result);
    void setup(unsigned int handle, unsigned int objectId);
    void callNext(unsigned int objectId);
    unsigned int m_id;        // numbered by create; GfMenuCallManager finds a context by it
    unsigned int m_objectId;  // the menu object it calls (setup, callNext); GfMenuObject::startCallContext passes
                              // the number it gives getAttachedObject
    unsigned int m_handle;    // its UI object's (setup), 0 once terminated
    mm::mtl::FixedVector<GfMenuResult, 4> m_results;  // addResult, popResult
    bool m_terminated;        // terminate sets it, setup and reset clear it
};
}  // namespace gf

#endif
