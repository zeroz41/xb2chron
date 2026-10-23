#ifndef ML_SCNRENDERDRSYSPARMACC_H
#define ML_SCNRENDERDRSYSPARMACC_H

namespace ml { class DrMan; }
namespace mm { class Vec3; }
namespace ml { class ScnRenderDrSys; }
namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// a texture a scene's models are drawn with: setModelTexture passes the texture and the flag to DrMan as a
// DR_MODEL_TEXTURE, in the slot it names (the field names are not the original's)
struct ScnRenderDrMdlTexture {
    grlib::CGLibTextureBuffer* m_texture;
    unsigned int m_slot;
    bool m_enable;  // UIScreenObject::createOnMemory sets it
};

// access to a scene renderer's parameters, through its DrMan
class ScnRenderDrSysParmAcc {
public:
    ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view);
    void setModelTexture(const ScnRenderDrMdlTexture& texture);
    void resetModelTexture(unsigned int slot);
    // the scene's settings fw::RenderParam hands on (the parameter names are not the original's)
    bool isSeamMapRead() const;
    void setPlayerPos(const mm::Vec3& pos);
    void setMotBlurDefault(bool enable);
    void setTimeVal(float time);  // the time of day, 0..1 of 24 hours
    void setWeather(int weather);
    void setWeatherFrame(float frame);
    void setGlobalWind(const mm::Vec3& power);
    void setColorFilterOverride(bool enable);
    void setColorFilterNum(int num);
    void setColorFilterFarNum(int num);
    void setColorFilterFrm(float frame);
    void setPlaneCloudNum(unsigned int num);
    void resetScene();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its one caller
    // (fw::fn_71001996F0) hands it a ScnRenderDrSysParmAcc it just constructed. What it does: stores the flag as a
    // word at 0x1D50 of DrMan::get()'s DrMan (not through the accessor's own m_drMan).
    void fn_710070A2F4(bool flag);

    DrMan* m_drMan;                  // the renderer's (its 0x10)
    unsigned char pad_08[0x8];       // what the renderer holds for the view
    int m_view;                      // the constructor's
};
}  // namespace ml

#endif
