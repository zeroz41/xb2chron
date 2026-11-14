#ifndef ML_DRENVCOLIPARAMETER_H
#define ML_DRENVCOLIPARAMETER_H

namespace ml {
class DrMan;
class DrEnvColiMan;
class DrEnvColiObj;
class DrEnvColiResult;
struct EnvColiPostData;

// an envcoli file's post-effect parameter set, by format version (the field names are not the original's)
template <int Ver>
struct EnvColiPostParameterVer {
    float m_toneMapParam[11];  // 0x0, DrEnvColiParameter::resetToneMapParams blends them into DrPixlPostParm's
};

// DrEnvColiMan::update builds one on its stack and has it apply the hit object's parameters to the view's
// DrPixlPostParm (the field names are not the original's)
class DrEnvColiParameter {
public:
    void calcParams(unsigned int, int, bool);
    void updateCloudParams(float, bool, const EnvColiPostData*, const EnvColiPostData*);
    // blends the two sets' tone map parameters (rate of the first) into the view's DrPixlPostParm
    void resetToneMapParams(const EnvColiPostParameterVer<10006>* first, const EnvColiPostParameterVer<10006>* second,
                            float rate);
    // static: its callers leave x0 unset; copies DrIniSys's bloom parameters into the view's DrPixlPostParm
    static void updateBloomParams();

    DrMan* m_drMan;          // 0x0
    DrEnvColiMan* m_man;     // 0x8
    DrEnvColiResult* m_result;  // 0x10
    DrEnvColiObj* m_hitObj;  // 0x18
    const void* m_postData;  // 0x20, the hit object's data + its header's 0x18 offset
    int pad_28;              // 0x28, the hit object's header 0x4 word
};
}  // namespace ml

#endif
