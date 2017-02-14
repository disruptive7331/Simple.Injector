#include "Utilities.hpp"

constexpr int min_exec_name_length = 5;
constexpr int offset_exec_spec = 4;
constexpr int length_exec_spec = 4;

namespace Utilities
{
	std::string ResolveFileSpecifier( std::string& process, const std::string& specifier, bool byval )
	{
		if ( process.length() < min_exec_name_length || process.substr( process.length( ) - offset_exec_spec, length_exec_spec ) != specifier )
		{
			if ( byval )
			{
				std::string ret = process;
				ret.append( specifier );
				return ret;
			}
			process.append( specifier );
		}

		return std::string( "" );
	}

	void FixDirSpecifiers( std::string& path )
	{
		size_t offset = 0;
		while ( true )
		{
			decltype( path.length( ) ) pos;
			if ( ( pos = path.find( "/", offset ) ) != std::string::npos )
			{
				offset += pos + 1;
				if ( offset > path.length( ) - 1 )
					break;

				path[ pos ] = '\\';
			}
			else
				break;
		}
	}

	bool FileExists( const std::string& path )
	{
		FILE* file;
		return( fopen_s( &file, path.c_str( ), "r" ) == 0 );
	}

	bool ResolvePathName( std::string& path )
	{
		if (path.length( ) < 4 || path.substr( 0, 3 ) != "C:\\" )
		{
			char buf[ MAX_PATH ];
			if ( !GetModuleFileNameA( NULL, buf, MAX_PATH ) )
				return false;

			std::string str( buf );
			decltype( str.length( ) ) pos;

			if ( ( pos = str.rfind( "\\" ) ) != std::string::npos )
				str.erase( pos + 1, str.length( ) - 1 );

			ResolveFileSpecifier( path );
			str.append( path );

			FixDirSpecifiers( str );

			path = str;

			return FileExists( str );
		}

		ResolveFileSpecifier( path );
		FixDirSpecifiers( path );
		return FileExists( path );
	}

	void ExitConsole( )
	{
		std::cout << std::endl
			<< "Exiting...";

		Sleep( 2000 );
		TerminateProcess( NULL, 0 );
	}

	void ToMultiByte( const wchar_t* wide, std::string& mb )
	{
		char converted[ MAX_PATH ];
		int bytes_needed = WideCharToMultiByte( CP_ACP, NULL, wide, -1, converted, 0, NULL, NULL );
		WideCharToMultiByte( CP_ACP, NULL, wide, -1, converted, bytes_needed, NULL, NULL );
		mb = converted;
	}

	std::string ToMultiByte( const wchar_t* wide )
	{
		char converted[ MAX_PATH ];
		int bytes_needed = WideCharToMultiByte( CP_ACP, NULL, wide, -1, converted, 0, NULL, NULL );
		WideCharToMultiByte( CP_ACP, NULL, wide, -1, converted, bytes_needed, NULL, NULL );
		return converted;
	}

	uint32_t GetProcessID( const std::string& process )
	{
		while ( true )
		{
			HANDLE snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

			if ( snapshot == INVALID_HANDLE_VALUE )
				continue;

			PROCESSENTRY32 pe;
			pe.dwSize = sizeof( PROCESSENTRY32 );

			if ( Process32First( snapshot, &pe ) )
			{
				if ( _stricmp( ToMultiByte( pe.szExeFile ).c_str( ), process.c_str( ) ) == 0 )
					return pe.th32ProcessID;
			}

			while ( Process32Next( snapshot, &pe ) )
			{
				if ( _stricmp( ToMultiByte( pe.szExeFile ).c_str( ), process.c_str( ) ) == 0 )
					return pe.th32ProcessID;
			}
		}
	}
}