#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// table 0x7100B61CD0
class GfMenuObjEnemyStatus : public ::gf::GfMenuObject {
public:
    struct OpenParam {
        GF_OBJ_HANDLE* m_obj;  // the enemy whose status it shows (GfMenuManager::gevChangeTarget's target)
    };
    static void open(const OpenParam& param);  // 1.0.0 symbol
    static void close();  // 1.0.0 symbol
    static void disp(bool disp);  // 1.0.0 symbol
    class ElemListener;
    class MainListener;
    virtual ~GfMenuObjEnemyStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
