#pragma once
#include <Includes.h>

class World : public Singleton<World>
{
public:
	ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	bool isonscreen(ImVec2 coords);

	ImVec2 WorldToScreen(Vector3 vPos);
	Vector3 GetBone(DWORD64 cPed, int Bone);
	ImVec2 BoneToScreen(DWORD64 cPed, int Bone);
	float pythag(ImVec2 src, ImVec2 dst);

};