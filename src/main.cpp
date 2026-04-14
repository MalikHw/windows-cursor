#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenuItem.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#include <windows.h>

// cache the cursors once so we don't reload them every frame
static HCURSOR s_handCursor = nullptr;
static HCURSOR s_arrowCursor = nullptr;

static void ensureCursors() {
    if (!s_handCursor)
        s_handCursor = LoadCursor(nullptr, IDC_HAND);
    if (!s_arrowCursor)
        s_arrowCursor = LoadCursor(nullptr, IDC_ARROW);
}

// hook CCMenuItem::selected(), started when the cursor hovers a button
class $modify(CCMenuItem) {
    virtual void selected() {
        CCMenuItem::selected();
        ensureCursors();
        SetCursor(s_handCursor);
    }

    virtual void unselected() {
        CCMenuItem::unselected();
        ensureCursors();
        SetCursor(s_arrowCursor);
    }
};

#endif // GEODE_IS_WINDOWS
