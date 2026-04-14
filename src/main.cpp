#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenuItem.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#include <windows.h>
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

static GLFWcursor* s_handCursor = nullptr;
static GLFWcursor* s_arrowCursor = nullptr;

static GLFWwindow* getGLFWWindow() {
    auto view = cocos2d::CCEGLView::sharedOpenGLView();
    return view->getWindow(); // returns the GLFWwindow*
}

static void ensureCursors() {
    if (!s_handCursor) {
        HCURSOR hHand = LoadCursor(nullptr, IDC_HAND);
        // create a GLFW cursor from the win32 handle isn't directly possible,
        // so use standard GLFW cursor shapes instead
        s_handCursor  = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
        s_arrowCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    }
}

class $modify(CCMenuItem) {
    virtual void selected() {
        CCMenuItem::selected();
        ensureCursors();
        glfwSetCursor(getGLFWWindow(), s_handCursor);
    }

    virtual void unselected() {
        CCMenuItem::unselected();
        ensureCursors();
        glfwSetCursor(getGLFWWindow(), s_arrowCursor);
    }
};

#endif
