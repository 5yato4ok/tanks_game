#ifndef TRACK_H
#define TRACK_H
#include "action.h"
#include "stdint.h"

namespace tank {
class Track_mngr {
 public:
    Track_mngr();
    tank_status ManageAction(Action& action);
 private:
    int32_t change_velocity();
    int32_t change_direction();
    int32_t velocity;
    bool moving_forward;
};
}//namespace tank

#endif // TRACK_H
