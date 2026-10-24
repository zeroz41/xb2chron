#ifndef CLASSES_GF_GFPLAYCOMMENUCHAPTERSAVE_H
#define CLASSES_GF_GFPLAYCOMMENUCHAPTERSAVE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58698
class GfPlayComMenuChapterSave : public GfPlayCom {
public:
    explicit GfPlayComMenuChapterSave(unsigned int id) : GfPlayCom(13, false), m_id(id) { s_bExist = true; }
    static GfPlayComMenuChapterSave* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuChapterSave";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static bool isDisp();
    static bool s_bExist;

    unsigned int m_id;  // the chapter (setChapterSave, createOneEvent); the name is not the original's
    bool m_open;  // update has opened the save menu; the name is not the original's
};
}  // namespace gf

#endif
