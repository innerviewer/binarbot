//
// Created by innerviewer on 2024-06-27.
//

#ifndef CANDLEINTERVAL_H
#define CANDLEINTERVAL_H

namespace Binarbot {
    enum CandleInterval : uint8_t {
        ONE_MINUTE,
        THREE_MINUTES,
        FIVE_MINUTES,
        FIFTEEN_MINUTES,
        THIRTY_MINUTES,
        ONE_HOUR,
        TWO_HOURS,
        FOUR_HOURS,
        SIX_HOURS,
        EIGHT_HOURS,
        TWELVE_HOURS,
        ONE_DAY,
        THREE_DAYS,
        ONE_WEEK,
        ONE_MONTH
    };

    const inline std::map<CandleInterval, std::string> CandleIntervalValue =  {
        { ONE_MINUTE,  "1m" } ,
        { THREE_MINUTES , "3m" },
        { FIVE_MINUTES , "5m" },
        { FIFTEEN_MINUTES , "15m" },
        { THIRTY_MINUTES , "30m" },
        { ONE_HOUR , "1h" },
        { TWO_HOURS , "2h" },
        { FOUR_HOURS , "4h" },
        { SIX_HOURS , "6h" },
        { EIGHT_HOURS , "8h" },
        { TWELVE_HOURS , "12h" },
        { ONE_DAY , "1d" },
        { THREE_DAYS , "3d" },
        { ONE_WEEK , "1w" },
        { ONE_MONTH , "1M" }
    };
}

#endif //CANDLEINTERVAL_H
