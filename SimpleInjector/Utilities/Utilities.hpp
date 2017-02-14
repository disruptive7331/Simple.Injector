#pragma once

#include "Common.hpp"
#include "Console.hpp"

namespace Utilities
{
	template <typename cvt_from, typename cvt_to>
	cvt_to encode_string( cvt_from src_string )
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		if ( std::is_same<cvt_to, std::string> && std::is_same<cvt_from, std::wstring> ) return converter.to_bytes( src_string );
		else if ( std::is_same<cvt_to, std::wstring> && std::is_same<cvt_from, std::string> ) return converter.from_bytes( src_string );
	}

	std::string ResolveFileSpecifier( std::string& process, const std::string& specifier = ".exe", bool byval = false );
	void FixDirSpecifiers( std::string& path );
	bool FileExists( const std::string& path );
	bool ResolvePathName( std::string& path );

	void ExitConsole( );

	void ToMultiByte( const wchar_t* wide, std::string& mb );
	std::string ToMultiByte( const wchar_t* wide );
	uint32_t GetProcessID( const std::string& process );
}