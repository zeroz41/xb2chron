#ifndef CLASSES_GF_GFASSETSETUPNPC_H
#define CLASSES_GF_GFASSETSETUPNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamNpc; }

namespace gf {
// table 0x7100B43D88
class GfAssetSetupNpc : public ::gf::GfAssetSetup {
public:
    GfAssetSetupNpc();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupNpc() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getRetargetMotFile(gf::GfAssetType type);  // slot 7
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getEfpFile(gf::GfAssetType type);  // slot 11
    virtual const char* getEabFile(gf::GfAssetType type);  // slot 12
    virtual const char* getEfbFile(gf::GfAssetType type);  // slot 13
    virtual const char* getStpFile(gf::GfAssetType type);  // slot 15
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual int getMotSlot() const;  // slot 21
    virtual int getRetargetMotSlot() const;  // slot 22
    virtual int getEvtMotSlot() const;  // slot 23
    virtual int getEfpSlot() const;  // slot 26
    virtual int getEabSlot() const;  // slot 27
    virtual int getEfbSlot() const;  // slot 28
    virtual int getStpSlot() const;  // slot 29
    virtual const char* getPath() const;  // slot 33
    virtual const char* getEvtPath() const;  // slot 34
    virtual GfAssetType getAssetType() const;  // slot 39
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamNpc const&);  // slot 40
    virtual GfAssetType getAssetTypeMot() const;  // slot 41
    virtual GfAssetType getAssetTypeArc() const;  // slot 42
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
