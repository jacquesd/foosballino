//
// Created by Kodiko Dytis on 28/05/16.
//

#ifndef FOOSBALLINO_TIME_H
#define FOOSBALLINO_TIME_H

#define MSECS_PER_SEC  (1000)
#define MSECS_PER_MIN  (60UL * 1000)
#define MSECS_PER_HOUR (3600UL * 1000)
#define MSECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define seconds(_time_) (_time_ % MSECS_PER_MIN)
#define minutes(_time_) ((_time_ / MSECS_PER_MIN) % MSECS_PER_MIN)
#define hours(_time_) (( _time_% MSECS_PER_DAY) / MSECS_PER_HOUR)

#endif //FOOSBALLINO_TIME_H
