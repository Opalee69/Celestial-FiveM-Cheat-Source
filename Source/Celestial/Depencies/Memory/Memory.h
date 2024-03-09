#pragma once
#include <Includes.h>

class Memory : public Singleton<Memory>
{
public:
	uintptr_t find_pattern_ex( uintptr_t baseModule, const char* pattern );
	uintptr_t is_relative( uintptr_t addr, int length );
	uintptr_t find_pattern( const char* moduleName, const char* pattern, int length );
	DWORD_PTR get_proc_base( DWORD procId );
};