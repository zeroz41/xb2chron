#ifndef ML_DRPIXLPOSTOBJDEPTHOFFIELD_H
#define ML_DRPIXLPOSTOBJDEPTHOFFIELD_H

#include "ml/DrPixlPostObj.h"

namespace ml {
// the depth-of-field post object DrPixlPostMan::setDepthField creates (0xC0 bytes); its fields are not declared yet
class DrPixlPostObjDepthofField : public DrPixlPostObj {
public:
    DrPixlPostObjDepthofField(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjDepthofField();

    unsigned char pad_18[0xA8];
};
}  // namespace ml

#endif
