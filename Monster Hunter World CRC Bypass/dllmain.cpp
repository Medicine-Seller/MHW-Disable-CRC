#include "MSLib/include/MSLib.h"
#pragma comment(lib, "MSLib/lib/MSLib.lib")

ms::SPatch CRC1
{
    "CRC Patch #1",
    "MonsterHunterWorld.exe",
    "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? E8",
    "C3"
};

ms::SPatch CRC2
{
    "CRC Patch #2",
    "MonsterHunterWorld.exe",
    "40 55 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 89 BC 24 ?? ?? ?? ?? E8",
    "C3"
};

VOID MainThread(HMODULE hModule)
{
    ms::ConsoleOpen();
    CRC1.Attach(ms::STOP_CONDITION::NONE);
    CRC2.Attach(ms::STOP_CONDITION::NONE);

    std::string input;
    while (true)
    {
        std::cin >> input;
        if (input == "exit")
            break;
        else if (input == "patch")
        {
            CRC1.Attach(ms::STOP_CONDITION::NONE);
            CRC2.Attach(ms::STOP_CONDITION::NONE);
        }
        else if (input == "undo")
        {
            CRC1.Detach();
            CRC2.Detach();
        }
    }

    ms::ConsoleClose();
    FreeLibraryAndExitThread(hModule, 0);
    return;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

