#ifndef CLASSES_AI_AIDATA_H
#define CLASSES_AI_AIDATA_H

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace ai {
// table 0x7100B3A340; an object's AI, which ai::AiManager creates (new of 0x60 bytes) and keeps in its list
class AiData {
public:
    AiData();
    virtual ~AiData();  // slot 0
    void init();
    void update(const fw::UpdateInfo& info);
    gf::GF_OBJ_HANDLE* getHandle() const;
    void setHandle(gf::GF_OBJ_HANDLE* handle);
    int getId() const;
    void setId(int id);

    gf::GF_OBJ_HANDLE* m_handle;  // getHandle/setHandle (the name is not the original's)
    int m_id;  // getId/setId: its row in the BDAT table AiScriptDataManager reads (the name is not the original's)
    unsigned char pad_14[0x4C];
};
}  // namespace ai

#endif
