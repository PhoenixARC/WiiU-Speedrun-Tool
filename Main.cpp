#include <code/code.h>

#include <code/tcpgecko.h>
#include <code/wups.h>

#include <exports/curl_functions.h>
#include <exports/socket_functions.h>
#include <exports/vpad_functions.h>
#include <exports/gx2_functions.h>
#include <exports/kernel.h>
#include <exports/os_functions.h>
#include <exports/memory.h>

#include <minecraft/mc.h>

void init() {
    InitTCPGecko();
    InitWups();

    InitSocketFunctionPointers();
    InitKernelFunctionPointers();
    InitVPadFunctionPointers();
    InitMemoryFunctionPointers();
    InitOSFunctionPointers();
    InitGX2FunctionPointers();
    InitLibCurlFunctionPointers();

    memoryInitialize();
}

int c_main(void*) {
    init();

    // Your Code here gets executed in a thread

    return 0;
}

// Gets Called once at startup
void _main() {
    mc::C4JThreadImpl* thread = new mc::C4JThreadImpl(c_main, nullptr, "Setup Thread", 0x200);
    thread->Run();
    thread->SetDeleteOnExit(true);
}