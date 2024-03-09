#pragma once
#include <Includes.h>

class Helper : public Singleton<Helper> {
public:

	void DrawLine(ImVec2 src, ImVec2 dst, ImColor col, float thickness = 1);
	void DrawBorder(float x, float y, float w, float h, float thickness, ImColor BorderColor);
	void DrawBox(ImVec2 src, ImVec2 dst, ImColor col, float thickness, float rounding = 0);
	void FillRect(float x, float y, float w, float h, ImColor color, int rounding = 0);
	void WindowFillRect(float x, float y, float w, float h, ImColor color, int rounding = 0);
	void DrawCornerBox(float x, float y, float w, float h, int thickness, float coverage, ImColor col);
	void RenderHealthbar(float x, float y, float w, float h, float health, ImColor col, int rounding);
	void Rect(float x, float y, float w, float h, ImColor color, int rounding = 0);
	auto DrawText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) -> VOID;
	bool IsFullscreen(HWND windowHandle);


	ImVec2 GetWindowSize();
};