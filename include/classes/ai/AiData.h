#ifndef CLASSES_AI_AIDATA_H
#define CLASSES_AI_AIDATA_H

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

#include "mm/Vec3.h"

namespace ai {
// table 0x7100B3A340; an object's AI, which ai::AiManager creates (new of 0x60 bytes) and keeps in its list
class AiData {
public:
    AiData();
    virtual ~AiData();  // slot 0
    void init();
    // counts the frame count down while it is above 0 and the object is not in AI state 1
    void update(const fw::UpdateInfo& info);
    gf::GF_OBJ_HANDLE* getHandle() const;
    void setHandle(gf::GF_OBJ_HANDLE* handle);
    // the handle of the character the object's AI targets, -1 for none
    gf::GF_OBJ_HANDLE* getHandleTarget() const;
    int getId() const;
    void setId(int id);
    bool isValid() const;
    int getParam(int index) const;
    void setParam(int index, int value);
    void setFrameCount(float count);
    bool isFrameCountEnd() const;
    float getRadius() const;
    // the radius of an enemy (its EnEnRadius at its setup's scale), 0.5 for a driver, 0 for anything else
    float getRadius(gf::GF_OBJ_HANDLE* handle) const;
    float getRadiusTarget() const;
    mm::Vec3 getPosition() const;
    mm::Vec3 getPosition(gf::GF_OBJ_HANDLE* handle) const;
    mm::Vec3 getPositionTarget() const;
    unsigned int getScoutStartHp() const;

    gf::GF_OBJ_HANDLE* m_handle;  // getHandle/setHandle (the name is not the original's)
    int m_id;  // getId/setId: its row in the BDAT table AiScriptDataManager reads (the name is not the original's)
    // set: isValid is false (the name is not the original's)
    bool m_invalid;
    float m_frameCount;  // setFrameCount; update counts it down (the name is not the original's)
    int m_params[16];  // getParam/setParam (the name is not the original's)
};
}  // namespace ai

#endif
