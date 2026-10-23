#ifndef CLASSES_GF_GFPLAYCOMCALLBACKEVENTSEQUENCE_H
#define CLASSES_GF_GFPLAYCOMCALLBACKEVENTSEQUENCE_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B58510
class GfPlayComCallbackEventSequence : public GfPlayCom {
public:
    GfPlayComCallbackEventSequence(int id, bool begin) : GfPlayCom(10, false), m_id(id), m_begin(begin) {}
    static GfPlayComCallbackEventSequence* create(int id, bool begin);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComCallbackEventSequence";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    int m_id;
    bool m_begin;  // GfSequentialPlay::addCallbackEventSequence's names
};
}  // namespace gf

#endif
