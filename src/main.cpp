#if defined(RACER_ACU)
#include "acu.h"
#elif defined(RACER_SCU)
#include "scu.h"
#else
#error Invalid controller type, define either RACER_ACU or RACER_SCU
#endif