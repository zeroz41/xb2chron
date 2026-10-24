#ifndef CLASSES_GF_GFPLAYCOMMENUOBJCOMMONTEXT_H
#define CLASSES_GF_GFPLAYCOMMENUOBJCOMMONTEXT_H

#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfMenuCallContext.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58288
class GfPlayComMenuObjCommonText : public GfPlayCom {
public:
    // the field names are not the original's
    GfPlayComMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param)
        : GfPlayCom(23, false), m_context(nullptr) {
        m_param = param;
        s_activate++;
    }
    static GfPlayComMenuObjCommonText* create(GfMenuObjCommonText::OpenKizunaParam& param);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuObjCommonText();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuObjCommonText";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the symbol's own name
    GfMenuObjCommonText::OpenKizunaParam m_param;  // create's
    GfMenuCallContext* m_context;                  // start() creates it; end() releases it
};
}  // namespace gf

#endif
