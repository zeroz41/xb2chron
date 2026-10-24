#ifndef CLASSES_LAYER_LAYERSHDMANAGER_H
#define CLASSES_LAYER_LAYERSHDMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace layer {
// table 0x7100B80360
class LayerShdManager : public ::ml::IWorkEvent {
public:
    virtual ~LayerShdManager();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    // The field names follow LayerManager's and LayerAccManager's accessors that read and write them (not the
    // original's). LayerManager's constructor allocates 0x580 bytes for it.
    unsigned char pad_08[0x528];
    float m_screenWidth;  // LayerAccManager::getScreenWidth
    float m_screenHeight;  // LayerAccManager::getScreenHeight
    float m_screenDivWidth;  // LayerManager::getScreenDivWidth
    unsigned char pad_53C[0x4];
    float m_screenCalcPosWidth;  // LayerManager::getScreenCalcPosWidth
    float m_screenCalcPosHeight;  // LayerManager::getScreenCalcPosHeight
    float m_screenCalcSclWidth;  // LayerManager::getScreenCalcSclWidth
    float m_screenCalcSclHeight;  // LayerManager::getScreenCalcSclHeight
    unsigned char pad_550[0x28];
    float m_gamma;  // LayerAccManager::setGamma
    unsigned char pad_57C[0x4];
};
}  // namespace layer

#endif
