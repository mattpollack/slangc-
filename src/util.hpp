#ifndef _UTIL_H
#define _UTIL_H

namespace slang {
    enum class option_type { SET, NIL };
    
    template <class T>
    struct option {
	option_type type;
	T           data;
    };
};

#endif
