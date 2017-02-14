#pragma once

#include "Common.hpp"

class NativeInject
{
public:
	bool PrepareEnvironment( const std::string& target_process, const std::string& dll_path );
	bool Inject( );

private:
	std::string m_szProcess, m_szPath;
	HANDLE m_hProcess;
	const char* m_pszString;
};