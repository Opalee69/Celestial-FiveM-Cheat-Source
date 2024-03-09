#include <Aimhelper.h>


void Aimhelper::MouseVector(uintptr_t entity) {

	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
		};

	auto bone_pos = World::Instance().BoneToScreen(entity, 0);

	float aimspeedon = m_var->aimbot.smooth + 1;
	ImVec2 screen = bone_pos;

	auto center_x = 1920 / 2;
	auto center_y = 1080 / 2;
	auto fov = get_distance(center_x, center_y, screen.x, screen.y);
	float TargetX = 0;
	float TargetY = 0;

	if (screen.x != 0) {
		if (screen.x > center_x) {
			TargetX = -(center_x - screen.x);
			TargetX /= aimspeedon;
			if (TargetX + center_x > center_x * 2) TargetX = 0;
		}

		if (screen.x < center_x) {
			TargetX = screen.x - center_x;
			TargetX /= aimspeedon;
			if (TargetX + center_x < 0) TargetX = 0;
		}
	}

	if (screen.y != 0) {
		if (screen.y > center_y) {
			TargetY = -(center_y - screen.y);
			TargetY /= aimspeedon;
			if (TargetY + center_y > center_y * 2) TargetY = 0;
		}

		if (screen.y < center_y) {
			TargetY = screen.y - center_y;
			TargetY /= aimspeedon;
			if (TargetY + center_y < 0) TargetY = 0;
		}
	}

	if (fov < m_var->aimbot.fovsize)
	{
		mouse_event(MOUSEEVENTF_MOVE, float(TargetX), float(TargetY / 1.2), 0, 0);

	}

}

uintptr_t Aimhelper::Target() {

	uintptr_t ClosestPlayer = 0;
	float closestdist = FLT_MAX;
	float dist;

	uintptr_t pedifc = *(uintptr_t*)(Init::Instance().g_replayifc + 0x18);

	for (int i = 0; i < 255; i++) {
		uintptr_t ped_list = *(uintptr_t*)(pedifc + 0x100);
		uintptr_t cPed = *(uintptr_t*)(ped_list + (i * 0x10));
		if (!cPed) continue;

		if (cPed == Init::Instance().g_localplayer) continue;

		float Health = *(float*)(cPed + 0x280);
		if (Health <= 0) continue;

		Vector3 PPos = *(Vector3*)(cPed + 0x90);
		ImVec2 Ped = World::Instance().WorldToScreen(PPos);

		ImVec2 Head = World::Instance().BoneToScreen(cPed, 0);

		ImVec2 middle = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);
		dist = World::Instance().pythag(middle, Head);

		if (dist < closestdist)
		{
			closestdist = dist;
			ClosestPlayer = cPed;
		}
	}

	return ClosestPlayer;
}



void Aimhelper::Loop() {

	if (m_var->aimbot.enable) {

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {

			MouseVector(Target());

		}

	}
}