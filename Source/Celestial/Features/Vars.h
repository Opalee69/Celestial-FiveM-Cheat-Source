#pragma once

#include <Includes.h>

class Variables : public Singleton<Variables> {
public:
	struct {
		bool enable = false;
		bool fov = false;
		int distance = 200;
		float fovsize = 90;
		int smooth = 1;
		int keybind = 0x0;
		int type[2];

	}aimbot;

	struct {
		bool enable = false;
		bool Box = false;
		bool target = false;
		bool fov = false;
		bool Vitality = false;
		bool Skeleton = false;
	}esp;

	struct {
		ImColor Box = (255, 255, 255, 255);
		float BoxArray[4] = { Box.Value.x, Box.Value.y, Box.Value.z, Box.Value.w };

		ImColor Target = (255, 0, 0, 0);
		float TargetArray[4] = { Target.Value.x, Target.Value.y, Target.Value.z, Target.Value.w };

		ImColor Fov = (255, 255, 255, 255);
		float FovArray[4] = { Fov.Value.x, Fov.Value.y, Fov.Value.z, Fov.Value.w };


	}color;
};

inline Variables* m_var = new Variables;