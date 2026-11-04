#ifndef ML_SCNRENDERDRSYSPARMACC_H
#define ML_SCNRENDERDRSYSPARMACC_H

namespace ml { class DrMan; }
namespace ml { class DrPixlPostParm; }
namespace mm { class Vec3; }
namespace ml { class ScnRenderDrSys; }
namespace ml { class ScnRenderDrViewCtrl; }
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
    ScnRenderDrSysParmAcc();  // DrMan::get()'s, view 0
    ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view);
    void setDOFOverride(bool enable);
    void setToneMap(bool enable);
    void setOverrideToneMap(float value);
    void setMotBlurOverride(bool enable);
    void setMotBlur(bool enable);
    void setMotBlurDefault(bool enable);
    void setDOF(bool enable);
    bool isDOF() const;
    void setDoFPixlRatio(float ratio);
    void setDoFDistance(float distance);
    void setDoFRange(float range);
    void setDoFStrength(float strength);
    void setDoFLens(float lens);
    void setDoFBlend(float blend);
    void setDofHLvMode(bool enable);
    void setDofPixlLv(int level);  // 0..2, else 0
    void setDOFAutoFocus(bool enable);
    void setDOFFocusNum(int num);  // 0..11, else 0
    void setDOFFocusMin(float min);
    float getDoFPixlRatio() const;
    float getDoFDistance() const;
    float getDoFRange() const;
    float getDoFStrength() const;
    float getDoFLens() const;
    float getDoFBlend() const;
    bool isDofHLvMode() const;
    int getDofPixlLv() const;
    bool isDOFAutoFocus() const;
    int getDOFFocusNum() const;
    float getDOFFocusMin() const;
    void setPlaneCloudNum(unsigned int num);
    void setGlobalWind(const mm::Vec3& power);
    void setAutoReduction(bool enable);
    void setColorFilterOverride(bool enable);
    void setColorFilterNum(int num);
    void setColorFilterFarNum(int num);
    void setColorFilterFrm(float frame);
    void setRainDrop(bool enable);
    void setTimeVal(float time);  // the time of day, 0..1 of 24 hours
    void setWeather(int weather);
    void setWeatherFrame(float frame);
    // 3.0.1's code under this name sets a DrMan flag (DrMan::weatherFrmEnd); 1.0.0's forwarded to
    // DrPixlPostParm::getWeatherFrame.
    void getWeatherFrame() const;
    void setSeamMapAddPosMode(bool enable);
    void setSeamMapReadPos(const mm::Vec3& pos);
    void setSelectIdDisp(int index, bool off);  // off: DrMan::offGblIdx, else setGblIdx
    bool isMdlAllMiddleTexStm() const;
    bool isSeamMapRead() const;
    void setToonDirLightScale(bool enable);
    void setToonAmbient(bool enable);
    void setPlayerPos(const mm::Vec3& pos);
    void setCameraLight(bool enable);
    void createAddRenderView(ScnRenderDrViewCtrl* view);
    void deleteAddRenderView(ScnRenderDrViewCtrl* view);
    void setModelTexture(const ScnRenderDrMdlTexture& texture);
    void resetModelTexture(unsigned int slot);
    void setGlassBr(bool enable, unsigned int arg);
    bool isGlassBr();
    void setViewRenderSkip(unsigned int view, bool skip);
    void resetScene();
    void setAutoResetScene(bool enable);
    void setGamma(float gamma);
    void setCaptureMode(bool enable);
    // 2.0.0's symbols name it. What it does: stores the flag as a word at 0x1D50 of DrMan::get()'s DrMan (not through
    // the accessor's own m_drMan).
    void setRenderTexMode(bool flag);
    // 2.0.0's symbols name it. A member: its code is in this unit and reads the accessor's m_drMan. What it does:
    // returns DrMan::isSeamMapOn's answer on m_drMan; GfMapManager::isExistObj asks it (on a just-constructed
    // accessor) when no map object exists.
    bool isSeamMapOn() const;

    DrMan* m_drMan;                  // the renderer's (its 0x10)
    DrPixlPostParm* m_postParm;      // the DrMan's for the view (the name is not the original's)
    int m_view;                      // the constructor's
};
}  // namespace ml

#endif
