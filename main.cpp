#include "include.h"


void ThreadESP() {
	auto mem = Memory("csgo.exe");
	const auto client = mem.GetModuleAddress("client.dll");

	const auto Color = color(231.f, 135.f, 0.f);
	const auto Bo = bo(true, true);

	const auto localPlayer = mem.Read<std::uintptr_t>(client + offsets::signatures::dwLocalPlayer);
	const auto glowObjectManager = mem.Read<std::uintptr_t>(client + offsets::signatures::dwGlowObjectManager);

	if (localPlayer) {
		for (int i = 0; i < 64; ++i) {
			const auto entity = mem.Read<std::uintptr_t>(client + offsets::signatures::dwEntityList + i * 0x10);
			const auto weapon = mem.Read<std::uintptr_t>(client + offsets::netvars::m_flFlashDuration + i * 0x10);

			if (mem.Read<std::uintptr_t>(entity + offsets::netvars::m_iTeamNum) == mem.Read<std::uintptr_t>(localPlayer + offsets::netvars::m_iTeamNum))
				continue;

			const auto glowIndex = mem.Read<std::int32_t>(entity + offsets::netvars::m_iGlowIndex);


			mem.Write<color>(glowObjectManager + (glowIndex * 0x38) + 0x8, Color); // color
			mem.Write<bo>(glowObjectManager + (glowIndex * 0x38) + 0x27, Bo);
		}
	}
}

void ThreadBhop() {
	auto mem = Memory("csgo.exe");
	const auto client = mem.GetModuleAddress("client.dll");
	const auto localPlayer = mem.Read<std::uintptr_t>(client + offsets::signatures::dwLocalPlayer);
	if (localPlayer) {
		const auto onGround = mem.Read<bool>(localPlayer + offsets::netvars::m_fFlags);
		mem.Write<BYTE>(client + offsets::signatures::dwForceJump, 6);
	}

}

void NoFlash() {
	auto mem = Memory("csgo.exe");
	const auto client = mem.GetModuleAddress("client.dll");
	const auto localPlayer = mem.Read<std::uintptr_t>(client + offsets::signatures::dwLocalPlayer);

	mem.Write<float>(localPlayer + offsets::netvars::m_flFlashMaxAlpha, 0.f);
}


int main() {
	while (1) {
		std::thread Thread1(ThreadESP);
		Thread1.join();
		if (GetAsyncKeyState(VK_SPACE)) {
			std::thread Thread2(ThreadBhop);
			Thread2.join();
		}
		std::thread Thread3(NoFlash);
		Thread3.join();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

