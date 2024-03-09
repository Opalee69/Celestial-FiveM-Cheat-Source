#pragma once
#include <Includes.h>

class Aimhelper : public Singleton<Aimhelper> {
public:
	void MouseVector(uintptr_t entity);


	uintptr_t Target();
	void Loop();


};