#ifndef GF_GFEXECSCHEDULE_H
#define GF_GFEXECSCHEDULE_H

namespace fw { class ComponentObject; }

namespace gf {
// ends the schedule the component's object runs (defined in gf_game_stuck_meter's unit; the mob's idle state calls
// it on leaving, its move state on entering): an asm state "S_schedule_..." gets the command "C_schedule_...2"
// (first letter C, last character 2); returns execCmd's result, false when no such state runs
bool execEndSchedule(fw::ComponentObject& com);
}  // namespace gf

#endif
