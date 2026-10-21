#ifndef CLASSES_GF_GFPLAYCOMMENUCHAPTERSAVE_H
#define CLASSES_GF_GFPLAYCOMMENUCHAPTERSAVE_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58698
class GfPlayComMenuChapterSave {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuChapterSave();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
