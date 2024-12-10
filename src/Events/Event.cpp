#include "Event.h"

#define X(a) #a,
const char* Event::EVENT_NAME[] = {EVENT_TYPE_TABLE};
#undef X

std::string Event::toString() const { return Event::EVENT_NAME[m_type]; }
