#include <World.h>


bool World::isonscreen(ImVec2 coords)
{
	if (coords.x < 0.1f || coords.y < 0.1 || coords.x > ImGui::GetIO().DisplaySize.x || coords.y > ImGui::GetIO().DisplaySize.y)
	{
		return false;
	}
	else {
		return true;
	}
}

ImVec2 World::WorldToScreen(Vector3 vPos)
{
	D3DXMATRIX viewmatrix = *(D3DXMATRIX*)(Init::Instance().g_viewport + 0x24c);

	D3DXMatrixTranspose(&viewmatrix, &viewmatrix);
	auto vec_x = D3DXVECTOR4(viewmatrix._21, viewmatrix._22, viewmatrix._23, viewmatrix._24),
		vec_y = D3DXVECTOR4(viewmatrix._31, viewmatrix._32, viewmatrix._33, viewmatrix._34),
		vec_z = D3DXVECTOR4(viewmatrix._41, viewmatrix._42, viewmatrix._43, viewmatrix._44);

	auto screen_pos = D3DXVECTOR3((vec_x.x * vPos.x) + (vec_x.y * vPos.y) + (vec_x.z * vPos.z) + vec_x.w,
		(vec_y.x * vPos.x) + (vec_y.y * vPos.y) + (vec_y.z * vPos.z) + vec_y.w,
		(vec_z.x * vPos.x) + (vec_z.y * vPos.y) + (vec_z.z * vPos.z) + vec_z.w);

	if (screen_pos.z <= 0.1f)
		return ImVec2(0, 0);

	screen_pos.z = 1.0f / screen_pos.z;
	screen_pos.x *= screen_pos.z;
	screen_pos.y *= screen_pos.z;

	auto width = ImGui::GetIO().DisplaySize.x;
	auto height = ImGui::GetIO().DisplaySize.y;
	float x_temp = width / 2;
	float y_temp = height / 2;

	screen_pos.x += x_temp + float(0.5f * screen_pos.x * width + 0.5f);
	screen_pos.y = y_temp - float(0.5f * screen_pos.y * height + 0.5f);

	return ImVec2(screen_pos.x, screen_pos.y);
}


Vector3 World::GetBone(DWORD64 cPed, int Bone)
{
	D3DXMATRIX matrix = *(D3DXMATRIX*)(cPed + 0x60);
	D3DXVECTOR3 bone = *(D3DXVECTOR3*)(cPed + (0x430 + Bone * 0x10));

	D3DXVECTOR4 transform;
	D3DXVec3Transform(&transform, &bone, &matrix);

	return Vector3(transform.x, transform.y, transform.z);
}

ImVec2 World::BoneToScreen(DWORD64 cPed, int Bone)
{
	__try
	{
		return WorldToScreen(GetBone(cPed, Bone));
	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
}

float World::pythag(ImVec2 src, ImVec2 dst)
{
	return sqrtf(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
}