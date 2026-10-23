#ifndef GF_GFSETUPPFTALK_H
#define GF_GFSETUPPFTALK_H

namespace gf {
// a talk's setup, as GfPlayFactory::createTalk hands it to GfSequentialPlay::addTalk (only its first field is known;
// the name is not the original's)
class GfSetupPfTalk {
public:
    int m_eventId;  // the event createTalk opens and closes its callback event sequence with
};
}  // namespace gf

#endif
