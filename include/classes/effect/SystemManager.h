#ifndef CLASSES_EFFECT_SYSTEMMANAGER_H
#define CLASSES_EFFECT_SYSTEMMANAGER_H

namespace ptlib { class DrDrawWorkInfoEF; }

namespace effect {
class SendParam;

// table 0x7100B80770
class SystemManager {
public:
    virtual ~SystemManager();  // slot 0
    static SystemManager*& getPtr();  // the system's manager, null while there is none
    // registers effect resource `data` (`size` bytes); null when it cannot
    void* es_regist(void* data, unsigned int size);
    void es_free(void* handle);
    // the instance handle's effect fades out over `frames` (fw::EffectManager::kill passes 1, remove -1, dead 0)
    void es_pause(bool pause);
    void es_fade_core(void* instance, unsigned int handle, int frames);
    void es_set_disp(unsigned int handle, int disp);
    void es_set_alpha(unsigned int handle, float alpha);
    void es_set_speed(unsigned int handle, float speed);
    void es_set_category(unsigned int handle, unsigned int category);
    void es_set_viewnum(unsigned int handle, int viewnum);
    void es_set_param_pos_only(unsigned int handle, const SendParam* param);
    void es_set_param_pos_only2(unsigned int handle, const SendParam* param);
    void es_set_param(unsigned int handle, const SendParam* param);
    int es_isalive(unsigned int handle);  // above 0 while the handle's effect lives
    int es_getDeadFlag(unsigned int handle);  // -1 for an unknown handle
    bool es_is_loop(void* data) const;
    bool es_contais_cam_axis(void* data);
    void begin();
    void end();
    void opacityRender(const ptlib::DrDrawWorkInfoEF* info);
    void alphaRender(const ptlib::DrDrawWorkInfoEF* info);
    void lastRender(const ptlib::DrDrawWorkInfoEF* info);
    void blurRender(const ptlib::DrDrawWorkInfoEF* info);
    void finalRender(const ptlib::DrDrawWorkInfoEF* info);

    unsigned char pad_8[0x87245];
    // the stream renderers lock and unlock the second half of their double buffer while set (the name is not the
    // original's)
    bool m_secondBuffer;
};
}  // namespace effect

#endif
