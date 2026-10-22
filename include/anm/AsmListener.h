#ifndef ANM_ASMLISTENER_H
#define ANM_ASMLISTENER_H

#include "anm/AsmAnnotetion.h"
#include "mm/mtl/Vector.h"

namespace anm {
// what an animation state machine tells its annotations to (gf::GfComAsm::AsmLisener derives from it)
class AsmListener {
public:
    // when an annotation fires (the names are not the original's)
    enum CallBackType {
        CALLBACK_ENTER = 0,  // a state is entered
        CALLBACK_LEAVE = 1,  // a state is left
        CALLBACK_FRAME = 2,  // a clip passes the annotation's frame
    };

    virtual void callback(CallBackType type, const AsmAnnotetion& annotation) = 0;  // slot 0
};

// an annotation at a frame of a clip, 0x20 bytes (the field names are not the original's)
struct AsmKeyframeAnnotation {
    float m_frame;
    AsmAnnotetion m_annotation;
};

// the keyframe annotations before a frame (std::lower_bound's comparator in CallBackDetector::executeStartFrame; the
// name is not the original's)
struct CompKeyframeAnnotation {
    bool operator()(const AsmKeyframeAnnotation& annotation, float frame) const { return annotation.m_frame < frame; }
};
// the keyframe annotations up to a frame, the frame included (std::lower_bound's comparator in
// CallBackDetector::executeFrame; the name is not the original's)
struct CompKeyframeAnnotationUpTo {
    bool operator()(const AsmKeyframeAnnotation& annotation, float frame) const { return annotation.m_frame <= frame; }
};

// tells a listener the annotations due (anm_asm_callback_detector.cpp)
class CallBackDetector {
public:
    // every annotation, of the given type
    static void execute(AsmListener& listener, AsmListener::CallBackType type,
                        const mm::mtl::Vector<AsmAnnotetion>& annotations);
    // the annotations at the start frame
    static void executeStartFrame(AsmListener& listener, float frame, const mm::mtl::Vector<AsmKeyframeAnnotation>& annotations);
    // the annotations passed going from one frame to the next, backwards when reverse, across the end when looped
    static void executeFrame(AsmListener& listener, float from, float to, bool reverse, bool looped,
                             const mm::mtl::Vector<AsmKeyframeAnnotation>& annotations);
};
}  // namespace anm

#endif
