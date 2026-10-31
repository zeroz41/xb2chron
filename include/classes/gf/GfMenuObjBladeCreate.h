#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfBladeCreateInfo.h"  // classes/gf/GfBladeCreateInfo.h (new; same folder)

namespace mm { namespace mtl { class ReferenceObject; } }

namespace gf {
class GfMenuCallContext;
class GfMenuModelView;
class GfMenuReferenceNumber;
class GfMenuBladeCreateCamera;

// table 0x7100B5FF10
class GfMenuObjBladeCreate : public ::gf::GfMenuObject {
public:
    class BoosterNumListener;
    class BoosterSelectListener;
    class ConfirmListener;
    class CreationListener;
    class CrystalSelectListener;
    class DriverSelectListener;
    class IdeagramListener;
    class MainListener;
    class ResultListener;
    // what registOpenParam keeps for the next open (ScriptPlayText's ui openBladeCreate passes its script
    // argument); the name is not the original's
    struct OpenParam {
        unsigned int m_value;
    };
    GfMenuObjBladeCreate(unsigned int handle);
    static void registOpenParam(const OpenParam& param);
    static void openCreatedBladeName(GfMenuCallContext* context);
    virtual ~GfMenuObjBladeCreate();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // m_seq's jobs
    bool seqStart();
    bool seqWaitLoading();
    bool seqEnd();
    bool seqSave();
    bool seqSaveWait();
    bool seqResultStart();
    bool seqResultConfirm();
    bool seqCreateStartSE();
    bool seqCreateWaitFade();
    bool seqCreatePlayJingle();
    bool seqCreatePlayBgmAfter();

    unsigned char pad_24[4];
    // the page updateIdea compares (> 1) and seqEnd enables the full-screen input of; the name is not the original's
    unsigned int m_page;
    unsigned char pad_2C[4];
    void* pad_30[4];  // the constructor zeroes 0x30..0x50
    unsigned char pad_50[8];
    void* pad_58[2];  // the constructor zeroes 0x58..0x68
    unsigned char pad_68[0x18];
    GfBladeCreate m_bladeCreate;  // 0x80 (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 10> pad_AB8;  // a FixedVector of 0x28 bytes (element type unknown)
    unsigned char pad_AE8[8];
    GfMenuModelView* m_modelView;  // 0xAF0: seqWaitLoading waits for its loading, update updates it
    GfMenuSequence<GfMenuObjBladeCreate, 20> m_seq;  // 0xAF8
    void* pad_1118;
    bool pad_1120;  // cleared by the constructor, seqStart and seqResultStart; nothing in 3.0.1 sets it
    mm::mtl::FixedVector<unsigned int, 4> pad_1128;  // a FixedVector of 0x10 bytes (element type unknown)
    unsigned long pad_1140;  // the constructor sets 4
    unsigned char pad_1148[8];
    // reference-counted objects the destructor releases (in the order 0x1160, 0x1168, 0x1150, 0x1158, 0x11A8)
    mm::mtl::ReferenceObject* pad_1150;
    mm::mtl::ReferenceObject* pad_1158;
    mm::mtl::ReferenceObject* pad_1160;
    mm::mtl::ReferenceObject* pad_1168;
    void* pad_1170;
    void* pad_1178;
    unsigned int pad_1180;
    unsigned char pad_1184[4];
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the constructor creates it (the name is not the original's)
    GfMenuBladeCreateCamera* m_camera;  // the constructor creates it (the name is not the original's)
    int pad_1198;  // the constructor sets -1
    unsigned char pad_119C[4];
    unsigned int pad_11A0;
    unsigned char pad_11A4[4];
    mm::mtl::ReferenceObject* pad_11A8;
    // seqSave's GfReqCommand::reqSave handle, -1 once seqSaveWait saw it end; the name is not the original's
    unsigned int m_saveReq;
    bool pad_11B4;
    unsigned int pad_11B8;
    unsigned char pad_11BC[4];
    unsigned int m_bgm;  // the handle seqCreatePlayJingle stops (GfMenuObjUtil::stopBGM); the name is not the original's
    // three sound handles MainListener's event 2 stops in a loop (the name is not the original's): [1] is the one
    // seqCreateStartSE stops first, [2] its "se_fld_allmap_715"
    unsigned int m_se[3];
};
}  // namespace gf

#endif
