#pragma once

#include <functional>

#include "../core/Core.h"

enum EventCategory {
    KeyEvent = BIT(0),
    MouseEvent = BIT(1),
};

// New Events are added here

#define EVENT_TYPE_TABLE \
    X(None)              \
    X(KeyPress)          \
    X(KeyRelease) X(MouseMove) X(MouseOffset) X(MouseClick) X(MouseScroll)

#define X(a) a,
enum EventType { EVENT_TYPE_TABLE };
#undef X

class Event {
   public:
    bool isHandled;

    // Dispatches func on event e only if it is the correct type
    template <typename T>
    static bool dispatch(Event& e, EventType type,
                         std::function<void(T&)> func) {
        static_assert(std::is_base_of_v<Event, T> == true);
        if (e.isType(type)) {
            func(static_cast<T&>(e));
            e.isHandled = true;
            return true;
        }
        return false;
    }

    bool isInCategory(EventCategory category) const {
        return category & m_category;
    }
    std::string toString() const;
    inline bool isType(EventType type) { return m_type == type; }

   protected:
    Event(EventType type, EventCategory category)
        : m_type{type}, m_category{category}, isHandled{false} {}
    EventCategory m_category;
    EventType m_type;

   private:
    static const char* EVENT_NAME[];
};

class KeyPressEvent : public Event {
   public:
    KeyPressEvent(int keycode, int mods)
        : Event(EventType::KeyPress, EventCategory::KeyEvent),
          keycode{keycode},
          mods{mods} {}
    const int keycode, mods;
};

class KeyReleaseEvent : public Event {
   public:
    KeyReleaseEvent(int keycode, int mods)
        : Event(EventType::KeyRelease, EventCategory::KeyEvent),
          keycode{keycode},
          mods{mods} {}
    const int keycode, mods;
};

class MouseScrollEvent : public Event {
   public:
    MouseScrollEvent(double xOffset, double yOffset)
        : Event(EventType::MouseScroll, EventCategory::MouseEvent),
          xOffset{xOffset},
          yOffset{yOffset} {}
    const double xOffset, yOffset;
};

class MouseMoveEvent : public Event {
   public:
    MouseMoveEvent(double xPos, double yPos)
        : Event(EventType::MouseMove, EventCategory::MouseEvent),
          yPos{yPos},
          xPos{xPos} {}
    const double yPos, xPos;
};

class MouseOffsetEvent : public Event {
   public:
    MouseOffsetEvent(double xOffset, double yOffset)
        : Event(EventType::MouseOffset, EventCategory::MouseEvent),
          yOffset{yOffset},
          xOffset{xOffset} {}
    const double yOffset, xOffset;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.toString();
}
