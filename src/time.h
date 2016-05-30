//
// Created by Kodiko Dytis on 28/05/16.
//

#ifndef FOOSBALLINO_TIME_H
#define FOOSBALLINO_TIME_H

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define seconds(_time_) (_time_ % SECS_PER_MIN)
#define minutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define hours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)

#endif //FOOSBALLINO_TIME_H
