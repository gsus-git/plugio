#ifndef SIGNAL_TYPES_HPP
#define SIGNAL_TYPES_HPP

namespace plugio::framework::core {

using Boolean = bool;
using Number  = double;

enum class SignalType
{
    BOOL,
    NUMBER
};

}

#endif // SIGNAL_TYPES_HPP
