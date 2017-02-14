#include "NativeInject.hpp"
#include "Utilities.hpp"

bool NativeInject::PrepareEnvironment( const std::string& target_process, const std::string& dll_path )
{
	this->m_szProcess = target_process;
	this->m_szPath = dll_path;

	if ( !( this->m_hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, Utilities::GetProcessID( target_process ) ) ) )
		return false;

	this->m_pszString = reinterpret_cast< const char* >( VirtualAllocEx( this->m_hProcess, nullptr, dll_path.length( ) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE ) );

	if ( !this->m_pszString )
		return false;

	if ( WriteProcessMemory( this->m_hProcess, ( LPVOID )( this->m_pszString ), dll_path.c_str( ), dll_path.length( ), nullptr ) )
		return true;

	return false;
}

bool NativeInject::Inject( )
{
	if ( CreateRemoteThread( this->m_hProcess, nullptr, 0, ( LPTHREAD_START_ROUTINE )LoadLibraryA, ( LPVOID )this->m_pszString, NULL, nullptr ) )
		return true;

	return false;
}
