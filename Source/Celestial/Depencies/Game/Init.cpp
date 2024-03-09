#include <Init.h>

void Init::Initialize() {

	DWORD_PTR Baseaddr = Memory::Instance().get_proc_base(GetCurrentProcessId());

    if ((GetModuleHandleA)("FiveM_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2545_GameProcess.exe")) {
        g_worldptr = 0x247F840;
        g_replayifcptr = 0x1EFD4C8;
        g_boneptr = 0x430;
        g_amor = 0x14B0;
    }
    if ((GetModuleHandleA)("FiveM_b1609_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b1609_GameProcess.exe")) {
        g_worldptr = 0x247F840;
        g_replayifcptr = 0x1EFD4C8;
        g_viewportptr = 0x2087780;
        g_boneptr = 0x779D64;
        g_amor = 0x0; //needed
    }

    if ((GetModuleHandleA)("FiveM_b2545_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2545_GameProcess.exe")) {
        g_worldptr = 0x25667E8;
        g_replayifcptr = 0x1F2E7A8;
        g_viewportptr = 0x1FD6F70;
        g_boneptr = 0x78C5E4;
        g_amor = 0x14E0 + 0x50;
    }
    if ((GetModuleHandleA)("FiveM_b2699_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2699_GameProcess.exe")) {
        g_worldptr = 0x26684D8;
        g_replayifcptr = 0x20304C8;
        g_viewportptr = 0x20D8C90;
        g_boneptr = 0x78F450;
        g_amor = 0x1530;
    }
    if ((GetModuleHandleA)("FiveM_b2189_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2189_GameProcess.exe")) {
        g_worldptr = 0x24E6D90;
        g_replayifcptr = 0x026332B8;
        g_viewportptr = 0x1F888C0;
        g_boneptr = 0x79B5DC;
        g_amor = 0x14E0;
    }
    if ((GetModuleHandleA)("FiveM_b2944_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2944_GameProcess.exe")) {
        g_worldptr = 0x257BEA0;
        g_replayifcptr = 0x1F42068;
        g_viewportptr = 0x1feaac0;
        g_boneptr = 0x410;
        g_amor = 0x150C;
    }
    if ((GetModuleHandleA)("FiveM_b3095_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b3095_GameProcess.exe")) {
        g_worldptr = 0x2593320;
        g_replayifcptr = 0x1F58B58;
        g_viewportptr = 0x20019E0;
        g_boneptr = 0x410;
        g_amor = 0x150C; //needed
    }
    if ((GetModuleHandleA)("FiveM_b2802_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2802_GameProcess.exe")) {
        g_worldptr = 0x2593320;
        g_replayifcptr = 0x254D448;
        g_viewportptr = 0x1FBC100;
        g_boneptr = 0x410;
        g_amor = 0x150C;
    }
    if ((GetModuleHandleA)("FiveM_b2060_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2060_GameProcess.exe")) {
        g_worldptr = 0x24C8858;
        g_replayifcptr = 0x1EC3828;
        g_viewportptr = 0x1F6A7E0;
        g_boneptr = 0x430;
        g_amor = 0x14E0;
    }
    if ((GetModuleHandleA)("FiveM_b2612_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2060_GameProcess.exe")) {
        g_worldptr = 0x2567DB0;
        g_replayifcptr = 0x1F77EF0;
        g_viewportptr = 0x1FD8570;
        g_boneptr = 0x430;
        g_amor = 0x1530;
    }
    if ((GetModuleHandleA)("FiveM_b2372_GTAProcess.exe") || (GetModuleHandleA)("FiveM_b2372_GameProcess.exe")) {
        g_worldptr = 0x252DCD8;
        g_replayifcptr = 0x1F05208;
        g_viewportptr = 0x1F9E9F0;
        g_boneptr = 0x430;
        g_amor = 0x14E0;
    }

    g_world = *(DWORD64*)(Baseaddr + g_worldptr);
    g_replayifc = *(DWORD64*)(Baseaddr + g_replayifcptr);
    g_viewport = *(DWORD64*)(Baseaddr + g_viewportptr);
    g_bone = *(DWORD64*)(Baseaddr + g_boneptr);

    g_localplayer = *(DWORD64*)(g_world + 0x8);

}
