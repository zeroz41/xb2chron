#ifndef CLASSES_ML_SCNCAMMAN_H
#define CLASSES_ML_SCNCAMMAN_H

#include "classes/ml/IWorkEvent.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/WinView.h"
#include "ml/WorkRootState.h"
#include "mm/mtl/FixedVector.h"


namespace ml {
// table 0x7100B77B58
class ScnCamMan : public ::ml::IWorkEvent {
public:
    // the ten view slots start empty (-1) and the scene gets one camera per slot
    ScnCamMan(Scn* scn);
    // detaches the scene from every view it is attached to
    virtual ~ScnCamMan();  // slot 0
    // attaches the scene to the view as slot index, detaching it from the slot's previous view
    void setView(WinView* view, int index);
    // the view of slot index; a negative index the current slot's (1.0.0 keeps it out of line; 3.0.1's
    // Scn::getView inlines it)
    WinView* getView(short index) {
        if (index < 0) {
            index = m_curCam;
        }
        if (m_views[index] != -1) {
            return static_cast<WinView*>(WorkRootState::getWork(m_views[index]));
        }
        return nullptr;
    }
    // the camera numbered index from the scene's pool; a negative index the current slot's (1.0.0 keeps it out of
    // line; 3.0.1's Scn::getCam inlines it)
    ScnObjCam* getCam(int index) {
        if (index < 0) {
            index = m_curCam;
        }
        return m_scn->m_pool->getCam(index);
    }

    Scn* m_scn;  // 0x8 the constructor's (the name is not the original's)
    // 0x10 each slot's view work id (WorkObj::m_wid), -1 for none (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 10> m_views;
    int m_curCam;  // 0x40 the slot getView(-1) takes; the constructor clears it (the name is not the original's)
};
}  // namespace ml

#endif
