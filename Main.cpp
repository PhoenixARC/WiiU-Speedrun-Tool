#include <code/code.h>
#include <minecraft/mc.h>

#include <xf/DrawHelper.h>
#include <xf/GUI.h>




xf::InfoScreen* gui = nullptr;
bool isGuiInit = false;


void displayCheck() {
    START_BUTTONCHECK((button & VPAD_BUTTON_ZL) && (button & VPAD_BUTTON_ZR) && (button & VPAD_BUTTON_L) && (button & VPAD_BUTTON_R) , 
	{
		switch(gui->TimerMode)
		{
			case(0): // Not Counting
				gui->StartTime = mc::System::processTimeInMilliSecs();
				gui->TimerMode = 1;
			break;
			case(1): // Counting
				gui->TimerMode = 0;
			break;
		}
	}, button)
    END_BUTTONCHECK()
	
}

DECL_HOOK(onFrameInGame, void) {
    xf::GUI::DrawHelper::renderSetup();
	displayCheck();
    gui->onTick();
}


DECL_HOOK(onFrameInMenu, void) {
	
gui->TimerMode = 0;
gui->StartTime = 0;
gui->CurrentTime = 0;
gui->FirstRun = true;
gui->FirstCheckPassed = false;
}


int c_main(void*) {
    // Init Export Functions and other Stuff
    code::init();

    HOOK(0x02D9CAD0, onFrameInGame, 0); //Info overlay
    HOOK(0x02D9C8B0, onFrameInMenu, 0); // Clear World Info

    return 0;
}

// Gets Called once at startup
void _main() {
    mc::C4JThreadImpl* thread = new mc::C4JThreadImpl(c_main, nullptr, "Setup Thread", 0x200);
    thread->Run();
    thread->SetDeleteOnExit(true);
	
    if (!isGuiInit) {
        gui = _new2(xf::InfoScreen());
		isGuiInit = true;
	}
}