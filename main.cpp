#include "include.h"


void ThreadESP() {
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		const auto Color = color(220.f, 20.f, 60.f);
		const auto ÑolorC4 = ñolorc4(255.f, 0.f, 0.f);
		const auto Bo = bo(true, true);

		const auto localPlayer = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
		const auto glowObjectManager = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwGlowObjectManager);

		if (!localPlayer) continue;

	while (true){
        std::this_thread::sleep_for(chrono::milliseconds(10));
	const auto Color = color(231.f, 135.f, 0.f);
	const auto Bo = bo(true, true);

	const auto localPlayer = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
        if( !localPlayer ) continue;

	const auto glowObjectManager = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwGlowObjectManager);
        if( !glowObjectManager ) continue;


		for (int i = 0; i < 64; ++i) {
			const auto entity = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwEntityList + i * 0x10);
			//const auto c4planted = g_mem.Read<std::uintptr_t>(g_client_base + offsets::netvars::m_bBombTicking);
			
			const auto entity = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwEntityList + i * 0x10);
			//const auto weapon = mem.Read<std::uintptr_t>(g_client_base + offsets::netvars::m_flFlashDuration + i * 0x10);

			if (g_mem.Read<std::uintptr_t>(entity + offsets::netvars::m_iTeamNum) == g_mem.Read<std::uintptr_t>(localPlayer + offsets::netvars::m_iTeamNum)) continue;

			//const auto glowIndexC4 = g_mem.Read<std::int32_t>(c4planted + offsets::netvars::m_iGlowIndex);
			const auto glowIndex = g_mem.Read<std::int32_t>(entity + offsets::netvars::m_iGlowIndex);

		
			g_mem.Write<color>(glowObjectManager + (glowIndex * 0x38) + 0x8, Color); // color
			g_mem.Write<bo>(glowObjectManager + (glowIndex * 0x38) + 0x27, Bo);

			//g_mem.Write<ñolorc4>(glowObjectManager + (glowIndexC4 * 0x38) + 0x8, ÑolorC4); // color
			//g_mem.Write<bo>(glowObjectManager + (glowIndexC4 * 0x38) + 0x27, Bo);

			mem.Write<color>(glowObjectManager + (glowIndex * 0x38) + 0x8, Color); // color
			mem.Write<bo>(glowObjectManager + (glowIndex * 0x38) + 0x27, Bo);

		}
	}
    }

}

void ThreadBhop() {

	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		if (GetAsyncKeyState(VK_SPACE)) {
			const auto localPlayer = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);

			if (!localPlayer) continue;

			const auto onGround = g_mem.Read<bool>(localPlayer + offsets::netvars::m_fFlags);
			g_mem.Write<BYTE>(g_client_base + offsets::signatures::dwForceJump, 6);
		}

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

void ThreadNoFlash() {
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		const auto localPlayer = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);

		g_mem.Write<float>(localPlayer + offsets::netvars::m_flFlashMaxAlpha, 145.f);
	}
void NoFlash() {
 while (true){
        std::this_thread::sleep_for(chrono::milliseconds(10));
	const auto localPlayer = mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
	mem.Write<float>(localPlayer + offsets::netvars::m_flFlashMaxAlpha, 0.f);
 }

}

void Fov() {
	const auto localPlayer = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
	g_mem.Write<int>(localPlayer + offsets::netvars::m_iDefaultFOV, 150);
}

void ThreadRadarHack() {
	while (1) {
		const auto localPlayer = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwLocalPlayer);
		const auto localTeam = g_mem.Read<std::uintptr_t>(g_client_base + offsets::netvars::m_iTeamNum);
		for (int i = 0; i < 64; i++) {
			const auto entity = g_mem.Read<std::uintptr_t>(g_client_base + offsets::signatures::dwEntityList + i * 0x10);
			if (g_mem.Read<std::uintptr_t>(entity + offsets::netvars::m_iTeamNum) == localTeam)
				continue;

			g_mem.Write<bool>(entity + offsets::netvars::m_bSpotted, true);
		}
	}
}

auto Point() {
	HDC hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
	return hdc;
}

void Rendering(auto &hdc) {
	while (1) {
		int r = 3;
		int w = GetDeviceCaps(hdc, HORZRES);
		int h = GetDeviceCaps(hdc, VERTRES);
		Ellipse(hdc, w / 2 - r, h / 2 - r, w / 2 + r, h / 2 + r);
	}
}

int main() {
	g_client_base = g_mem.GetModuleAddress("client.dll");
	std::thread Thread1(ThreadESP);
	std::thread Thread2(ThreadBhop);
	std::thread Thread3(ThreadNoFlash);
	std::thread Thread4(ThreadRadarHack);


	Thread1.detach();
	Thread2.detach();
	Thread3.detach();
	Thread4.detach();

	Fov();
	auto set = Point();
	Rendering(set);

	if (getchar())
		return 0;
	
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

