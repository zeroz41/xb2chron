#ifndef CLASSES_EVENT_DATAMANAGER_H
#define CLASSES_EVENT_DATAMANAGER_H

#include "mm/Vec3.h"
#include "mm/Mat44.h"

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3E2B0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::DataManager>
class DataManager : public IManager, public mm::mtl::Singleton<DataManager> {
public:
    virtual ~DataManager();  // slot 0
    DataManager();  // out of line (Singleton<DataManager>::getPtr calls it)
    // named by 1.0.0's symbols (_ZN5event11DataManager12setOffsetSrcERKN2mm4Vec3Efb / setOffsetDes, the evt_setup
    // plugin's offsetSrc/offsetDes call them at the same sites)
    void setOffsetSrc(const mm::Vec3& offset, float angle, bool flag);
    void setOffsetDes(const mm::Vec3& offset, float angle, bool flag);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // whether the target id's values are angles (evt_chara's setTar then converts degrees to radians)
    bool checkRadianTar(unsigned int id);
    // the position or rotation an axis (PosAxis/RotAxis type and value) gives (ObjectChara::setPosAxis/setRotAxis);
    // axis2rot's vector is the character's current position
    mm::Vec3 axis2pos(unsigned int type, float x, float y, float z);
    mm::Vec3 axis2rot(unsigned int type, float x, float y, float z, const mm::Vec3& pos);
    // the target a TarAxis gives (CamHands::setTar); the vector is the camera's current position
    mm::Vec3 axis2tar(unsigned int type, float x, float y, float z, const mm::Vec3& pos);
    // the frame of target axis type (0..5 but the angle ones, then one per character of the current scene)
    mm::Mat44 getTarAxis(unsigned int type);
    // the frame of axis type (0..3, then one per character of the current scene)
    mm::Mat44 getPosAxis(unsigned int type);
    float getRotOfsY(unsigned int type, const mm::Vec3& pos);
    // the name of target axis id: the fixed ones (0..5), then the current scene's characters (ObjectChara::render)
    const char* getTarName(unsigned int id);

    // the 0x170-byte scene offsets createScene news (1.0.0's OfsInfo::OfsInfo(const char*), inlined in 3.0.1's
    // createScene); the field names are not the original's
    struct OfsInfo {
        // the matrices and vectors are assigned in the body (an init list computes each field's address at its
        // copy; the original computes them all before the first)
        explicit OfsInfo(const char* name) : m_name(name) {
            pad_50 = mm::Mat44::identity;
            pad_90 = mm::Mat44::identity;
            m_srcMat = mm::Mat44::identity;
            m_srcRot = mm::Vec3::zero;
            m_desMat = mm::Mat44::identity;
            m_desRot = mm::Vec3::zero;
        }
        mm::mtl::FixStr<64> m_name;  // 0x0: the scene's name
        mm::Mat44 pad_50;  // 0x50
        mm::Mat44 pad_90;  // 0x90
        // 0xd0/0x110 and 0x120/0x160: updateCurrent copies the login offset (m_ofsMat, m_ofsRot.y) into both pairs
        // (setOffsetSrc/setOffsetDes are inferred to set them)
        mm::Mat44 m_srcMat;  // 0xd0
        mm::Vec3 m_srcRot;  // 0x110
        mm::Mat44 m_desMat;  // 0x120
        mm::Vec3 m_desRot;  // 0x160
    };
    // the scene named name, else null (1.0.0's searchScene; 3.0.1 inlines it into updateCurrent)
    OfsInfo* searchScene(const char* name) const {
        for (unsigned long i = 0; i < m_scenes.size(); i++) {
            if (strcmp(m_scenes[i]->m_name.m_str, name) == 0) {
                return m_scenes[i];
            }
        }
        return nullptr;
    }
    // makes the scene named m_sceneName current, creating it when missing (1.0.0's name)
    void updateCurrent();
    OfsInfo* createScene(const char* name);
    // the offset login takes from Manager when GfGameManager::isGameTypeIra (msg 1)
    void login();
    // 1.0.0's clear, setupScene, startScene (out of line there; 3.0.1 inlines them into OnEventProc and the
    // destructor; defined inline in CharaObj.cpp)
    inline void clear();
    inline void setupScene();
    inline void startScene();
    // the login offset reset (login's start, msg 2); the name is not the original's
    inline void resetOffset();

    unsigned int m_flags;  // 0x10; bit 0: the login offset is set; the name is not the original's
    unsigned int pad_14;
    // the scenes 1.0.0's createScene adds; the name is not the original's
    mm::mtl::FixedVector<OfsInfo*, 16> m_scenes;  // 0x18 (size 0x98)
    // the scene updateCurrent makes current ("default" at first, as ObjectManager's); the name is not the original's
    mm::mtl::FixStr<64> m_sceneName;  // 0xa0
    mm::mtl::FixStr<64> m_currentName;  // 0xe4; the name is not the original's
    OfsInfo* m_current;  // 0x128; the name is not the original's
    // the offset login builds from Manager's play position and angle (rotation about y, then the position);
    // the names are not the original's
    mm::Mat44 m_ofsMat;  // 0x130
    mm::Vec3 m_ofsRot;  // 0x170
};
}  // namespace event

#endif
