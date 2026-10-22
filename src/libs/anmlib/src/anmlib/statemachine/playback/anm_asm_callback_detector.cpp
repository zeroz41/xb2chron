#include "anm/AsmListener.h"

#include "algorithm"
#include "anm/AsmListener.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"

namespace anm {

void CallBackDetector::execute(AsmListener& listener, AsmListener::CallBackType type,
                               const mm::mtl::Vector<AsmAnnotetion>& annotations) {
#line 22
    MM_ASSERT(annotations.size() != 0);
    const AsmAnnotetion* it = annotations.begin();
    const AsmAnnotetion* end = annotations.end();
    for (; it != end; ++it) {
        listener.callback(type, *it);
    }
}

void CallBackDetector::executeStartFrame(AsmListener& listener, float frame,
                                         const mm::mtl::Vector<AsmKeyframeAnnotation>& annotations) {
    const AsmKeyframeAnnotation* it =
        std::lower_bound(annotations.begin(), annotations.end(), frame, CompKeyframeAnnotation());
    const AsmKeyframeAnnotation* end = annotations.end();
    for (; it != end && it->m_frame == frame; ++it) {
        listener.callback(AsmListener::CALLBACK_FRAME, it->m_annotation);
    }
}

void CallBackDetector::executeFrame(AsmListener& listener, float from, float to, bool reverse, bool looped,
                                    const mm::mtl::Vector<AsmKeyframeAnnotation>& annotations) {
#line 96
    MM_ASSERT(annotations.size() != 0);
    const AsmKeyframeAnnotation* it =
        std::lower_bound(annotations.begin(), annotations.end(), from, CompKeyframeAnnotationUpTo());
    if (reverse) {
        int index = it - annotations.begin();
        if (looped) {
            // (every one up to the start: the original passes the one past `from` each time)
            for (int i = index; i >= 0; i--) {
                listener.callback(AsmListener::CALLBACK_FRAME, it->m_annotation);
            }
            for (int i = annotations.size() - 1; i >= 0; i--) {
                const AsmKeyframeAnnotation& annotation = annotations[i];
                if (from != to && annotation.m_frame >= to) {
                    listener.callback(AsmListener::CALLBACK_FRAME, annotation.m_annotation);
                } else {
                    return;
                }
            }
        } else {
            for (int i = index; i >= 0; i--) {
                const AsmKeyframeAnnotation& annotation = annotations[i];
                if (annotation.m_frame <= from) {
                    if (annotation.m_frame >= to && from != to) {
                        listener.callback(AsmListener::CALLBACK_FRAME, it->m_annotation);
                    } else {
                        return;
                    }
                }
            }
        }
    } else {
        const AsmKeyframeAnnotation* end = annotations.end();
        if (looped) {
            for (; it != end; ++it) {
                listener.callback(AsmListener::CALLBACK_FRAME, it->m_annotation);
            }
            const AsmKeyframeAnnotation* first = annotations.begin();
            const AsmKeyframeAnnotation* last = annotations.end();
            for (; first != last && first->m_frame <= to; ++first) {
                listener.callback(AsmListener::CALLBACK_FRAME, first->m_annotation);
            }
        } else {
            for (; it != end; ++it) {
                if (it->m_frame <= to && from != to) {
                    listener.callback(AsmListener::CALLBACK_FRAME, it->m_annotation);
                } else {
                    return;
                }
            }
        }
    }
}

}  // namespace anm
