#include <Visuals.h>

void Visuals::Loop() {

	if (m_var->esp.fov) {

		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), m_var->aimbot.fovsize, ImColor(255, 255, 255), 90.F);

	}

	if (m_var->esp.enable) {

		uintptr_t pedifc = *(uintptr_t*)(Init::Instance().g_replayifc + 0x18);

		for (int i = 0; i < 255; i++) {
			uintptr_t ped_list = *(uintptr_t*)(pedifc + 0x100);
			uintptr_t cPed = *(uintptr_t*)(ped_list + (i * 0x10));
			if (!cPed) continue;

			//if (cPed = Init::Instance().g_localplayer) continue;

			Vector3 PPos = *(Vector3*)(cPed + 0x90);
			ImVec2 Ped = World::Instance().WorldToScreen(PPos);

			Vector3 HPos(PPos.x, PPos.y, PPos.z + 0.8f);
			Vector3 FPos(PPos.x, PPos.y, PPos.z - 0.95f);
			Vector3 FPos1(PPos.x, PPos.y, PPos.z - 0.96f);

			ImVec2 Head = World::Instance().WorldToScreen(HPos);
			ImVec2 Foot = World::Instance().WorldToScreen(FPos);
			ImVec2 Foot1 = World::Instance().WorldToScreen(FPos1);

			ImVec2 Headpopo = World::Instance().BoneToScreen(cPed, 0);

			float Health = *(float*)(cPed + 0x280) - 100;
			float Armor = *(float*)(cPed + Init::Instance().g_amor);

			if (Health <= 0) continue;

			float height = Head.y - Foot.y;
			float width = (Foot.y - Head.y) / 4.5f;

			if (m_var->esp.Box) {

				if (World::Instance().isonscreen({ Foot.x + width, Head.y }) && World::Instance().isonscreen({ Foot.x - width, Foot.y })) {

					ImGui::GetBackgroundDrawList()->addrect({ Foot.x - width, Foot.y }, { Foot.x + width, Head.y }, ImColor(255, 255, 255), -2, 0, 2);

				}


			}

			if (m_var->esp.target) {
				if (Aimhelper::Instance().Target()) {

					Vector3 TargetPos = *(Vector3*)(Aimhelper::Instance().Target() + 0x90);
					ImVec2 Target = World::Instance().WorldToScreen(TargetPos);

					Vector3 TargetHPos(TargetPos.x, TargetPos.y, TargetPos.z + 0.8f);
					Vector3 TargetFPos(TargetPos.x, TargetPos.y, TargetPos.z - 0.95f);

					ImVec2 TargetHead = World::Instance().WorldToScreen(TargetHPos);
					ImVec2 TargetFoot = World::Instance().WorldToScreen(TargetFPos);

					float Targetheight = TargetHead.y - TargetFoot.y;
					float Targetwidth = (TargetFoot.y - TargetHead.y) / 4.5f;

					ImGui::GetBackgroundDrawList()->addrect({ TargetFoot.x - Targetwidth, TargetFoot.y }, { TargetFoot.x + Targetwidth, TargetHead.y }, ImColor(255, 0, 0), -2, 0, 2);
				}
			}


			if (m_var->esp.Vitality) {

				ImColor HealthC;
				if (Health > 75) {
					HealthC = ImColor(50, 205, 50);
				}
				else if (Health < 75 && Health > 50) {
					HealthC = ImColor(172, 187, 47);
				}
				else if (Health < 50 && Health > 25) {
					HealthC = ImColor(255, 140, 0);
				}
				else if (Health < 25 && Health > 15) {
					HealthC = ImColor(255, 69, 0);
				}
				else if (Health < 15 && Health > 0)
				{
					HealthC = ImColor(255, 0, 0);
				}

				if (Health > 0)
				{
					float cur_w = width + width;
					float W_HEALTH = (cur_w / 100) * Health;
					Helper::Instance().DrawBorder(Foot.x - width - 0.75, Foot.y - 0.75, cur_w + 0.75, 2.5f + 0.75, 1, ImColor(0, 0, 0));
					Helper::Instance().FillRect(Foot.x - width, Foot.y, cur_w, 2.5f, ImColor(0, 0, 0), 0);
					Helper::Instance().FillRect(Foot.x - width, Foot.y, W_HEALTH, 2.5f, HealthC, 0);
				}

				if (Armor > 0) {

					float cur_w = width + width;
					float W_HEALTH = (cur_w / 100) * Armor;
					Helper::Instance().DrawBorder(Foot1.x - width - 1, Foot1.y + 5.25 - 1, cur_w + 1, 2.5f + 1, 1, ImColor(0, 0, 0));
					Helper::Instance().FillRect(Foot1.x - width, Foot1.y + 5.25, cur_w, 2.5f, ImColor(0, 0, 0), 0);
					Helper::Instance().FillRect(Foot1.x - width, Foot1.y + 5.25, W_HEALTH, 2.5f, ImColor(58, 95, 205), 0);

				}

			}

		}

	}

}