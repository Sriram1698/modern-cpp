#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    uint64_t hrs = seconds / 3600;
    uint8_t mins= (seconds % 3600) / 60;
    uint8_t secs = seconds % 60;
    
    string h = (hrs < 10) ? ("0" + std::to_string(hrs)) : std::to_string(hrs);
    string m = (mins < 10) ? ("0" + std::to_string(mins)) : std::to_string(mins);
    string s = (secs < 10) ? ("0" + std::to_string(secs)) : std::to_string(secs);

    return h + ":" + m + ":" + s;
}