#pragma once

#include <Includes.h>

class Init : public Singleton<Init> {
public:

	DWORD g_worldptr, g_replayifcptr, g_amor, g_viewportptr, g_boneptr, g_localplayer;
	DWORD64 g_world, g_replayifc, g_viewport, g_bone;

	void Initialize();
};
