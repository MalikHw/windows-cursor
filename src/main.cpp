#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenuItem.hpp>
using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#include <windows.h>

static HCURSOR s_handCursor = nullptr;
static HCURSOR s_arrowCursor = nullptr;
static bool s_useHand = false;
static WNDPROC s_origWndProc = nullptr;

LRESULT CALLBACK hookedWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_SETCURSOR) {
        SetCursor(s_useHand ? s_handCursor : s_arrowCursor);
        return TRUE; // prevents Windows from resetting it
    }
    return CallWindowProcW(s_origWndProc, hwnd, msg, wp, lp);
}

$execute {
    s_handCursor  = LoadCursor(nullptr, IDC_HAND);
    s_arrowCursor = LoadCursor(nullptr, IDC_ARROW);

    HWND hwnd = GetActiveWindow();
    s_origWndProc = (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)hookedWndProc);
}

class $modify(CCMenuItem) {
    virtual void selected() {
        CCMenuItem::selected();
        s_useHand = true;
    }

    virtual void unselected() {
        CCMenuItem::unselected();
        s_useHand = false;
    }
};

#endif
