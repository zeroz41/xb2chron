#ifndef GF_GFEXECSCHEDULE_H
#define GF_GFEXECSCHEDULE_H

namespace fw { class ComponentObject; }

namespace gf {
// ends the schedule the component's object runs (defined in gf_game_stuck_meter's unit; the mob's idle state calls
// it on leaving, its move state on entering)
void execEndSchedule(fw::ComponentObject& com);
}  // namespace gf

#endif
