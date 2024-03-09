#include <Helper.h>

void Helper::DrawBox(ImVec2 src, ImVec2 dst, ImColor col, float thickness, float rounding)
{
	if (World::Instance().isonscreen(dst) && World::Instance().isonscreen(src))
	{
		ImGui::GetBackgroundDrawList()->addrect({ src.x, src.y }, { dst.x, dst.y }, col, rounding);
	}
}

void Helper::DrawCornerBox(float x, float y, float w, float h, int thickness, float coverage, ImColor col)
{
	DrawLine({ x, y }, { x + (w * coverage), y }, col, thickness);
	DrawLine({ x, y }, { x, y + (h * coverage / 2) }, col, thickness);

	DrawLine({ x, y + h }, { x + (w * coverage), y + h }, col, thickness);
	DrawLine({ x, y + h }, { x, (y + h) - (h * coverage / 2) }, col, thickness);

	DrawLine({ x + w, y }, { (x + w) - (w * coverage), y }, col, thickness);
	DrawLine({ x + w, y }, { x + w, y + (h * coverage / 2) }, col, thickness);

	DrawLine({ x + w, y + h }, { (x + w) - (w * coverage), y + h }, col, thickness);
	DrawLine({ x + w, y + h }, { x + w, (y + h) - (h * coverage / 2) }, col, thickness);
}



auto Helper::DrawText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) -> VOID
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}


void Helper::DrawLine(ImVec2 src, ImVec2 dst, ImColor col, float thickness)
{

	if (World::Instance().isonscreen(dst) && World::Instance().isonscreen(src))
	{
		ImGui::GetBackgroundDrawList()->AddLine({ src.x, src.y }, { dst.x, dst.y }, col, thickness);
	}
}

void Helper::DrawBorder(float x, float y, float w, float h, float thickness, ImColor BorderColor)
{

	FillRect(x, y, w, thickness, BorderColor);

	FillRect(x, y, thickness, h, BorderColor);

	FillRect((x + w), y, thickness, h, BorderColor);

	FillRect(x, y + h, w + thickness, thickness, BorderColor);
}

void Helper::FillRect(float x, float y, float w, float h, ImColor color, int rounding)
{
	if (World::Instance().isonscreen({ x, y }))
	{
		ImGui::GetBackgroundDrawList()->addrectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, rounding);

	}
}

double deg2rad(double deg) {
	return deg * DirectX::XM_PI / 180.0;
}

bool Helper::IsFullscreen(HWND windowHandle)
{
	MONITORINFO monitorInfo = { 0 };
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

	RECT windowRect;
	GetWindowRect(windowHandle, &windowRect);

	return windowRect.left == monitorInfo.rcMonitor.left &&
		windowRect.right == monitorInfo.rcMonitor.right &&
		windowRect.top == monitorInfo.rcMonitor.top &&
		windowRect.bottom == monitorInfo.rcMonitor.bottom;
}

ImVec2 Helper::GetWindowSize() {
	RECT rect;
	HWND hwnd = GetActiveWindow();
	if (GetWindowRect(hwnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		if (this->IsFullscreen(hwnd))
		{
			return ImVec2(width / 2, height / 2);
		}
		return ImVec2((width - 17) / 2, (height - 35) / 2);
	}
	return ImVec2(0, 0);
}

void Helper::Rect(float x, float y, float w, float h, ImColor color, int rounding)
{
	if (World::Instance().isonscreen({ x, y }))
	{
		ImGui::GetBackgroundDrawList()->addrect(ImVec2(x, y), ImVec2(x + w, y + h), color, rounding);

	}
}

void Helper::WindowFillRect(float x, float y, float w, float h, ImColor color, int rounding)
{
	ImGui::GetWindowDrawList()->addrectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, rounding);
}

void Helper::RenderHealthbar(float x, float y, float w, float h, float health, ImColor col, int rounding)
{
	float cur_w = w + w;
	float Health = (cur_w / 100) * health;
	this->FillRect(x - w, y, cur_w, h, ImColor(0, 0, 0), rounding);
	this->FillRect(x - w, y, Health, h, col, rounding);
}