#include "include.h"


void ThreadESP() {
	while (true){
        std::this_thread::sleep_for(chrono::milliseconds(10));
	const auto Color = color(231.f, 135.f, 0.f);
	const auto Bo = bo(true, true);

	const auto localPlayer = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
        if( !localPlayer ) continue;

	const auto glowObjectManager = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwGlowObjectManager);
        if( !glowObjectManager ) continue;


	if (localPlayer) {
		for (int i = 0; i < 64; ++i) {
			const auto entity = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwEntityList + i * 0x10);
			const auto weapon = mem.Read<std::uintptr_t>(g_client_base + offsets::netvars::m_flFlashDuration + i * 0x10);

			if (mem.Read<std::uintptr_t>(entity + offsets::netvars::m_iTeamNum) == mem.Read<std::uintptr_t>(localPlayer + offsets::netvars::m_iTeamNum))
				continue;

			const auto glowIndex = mem.Read<std::int32_t>(entity + offsets::netvars::m_iGlowIndex);

			mem.Write<color>(glowObjectManager + (glowIndex * 0x38) + 0x8, Color); // color
			mem.Write<bo>(glowObjectManager + (glowIndex * 0x38) + 0x27, Bo);
		}
	}
    }

}

void ThreadBhop() {
	while (true) {
        std::this_thread::sleep_for(chrono::milliseconds(10));
	if( GetAsyncKeyState( VK_SPACE ) ){
		
	 const auto localPlayer = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
	 if( !localPlayer ) continue;
		
	 const auto onGround = mem.Read<bool>(localPlayer + offsets::netvars::m_fFlags);
	 mem.Write<BYTE>(client + offsets::signatures::dwForceJump, 6);
	 }
		
	}

}

void NoFlash() {
 while (true){
        std::this_thread::sleep_for(chrono::milliseconds(10));
	const auto localPlayer = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
	mem.Write<float>(localPlayer + offsets::netvars::m_flFlashMaxAlpha, 0.f);
 }

}


int main() {
	
                auto mem = Memory("csgo.exe");
	        g_client_base = mem.GetModuleAddress("client.dll");
	
		std::thread Thread1(ThreadESP);
                std::thread Thread2(ThreadBhop);
                std::thread Thread3(NoFlash);
	
		Thread1.detach();
                Thread2.detach();
                Thread3.detach();
		
  if( getchar() )
	  return 0;

}

