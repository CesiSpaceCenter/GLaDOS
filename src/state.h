#ifndef _RACER_STATE_H_
#define _RACER_STATE_H_

namespace racer::state {
    enum State {
        BOOTING = 0,
        STANDBY = 3,
        ARMED = 6,
        ASCENT = 9,
        DESCENT = 12,
        LANDED
    };
    inline State current_state = BOOTING;
    inline State remote_state = BOOTING;
};

#endif