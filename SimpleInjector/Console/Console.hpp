#pragma once

#include "Common.hpp"

extern HANDLE console_out_handle;

namespace FancyConsole
{
	std::ostream& Green( std::ostream& strm );
	std::ostream& Red( std::ostream& strm );
	std::ostream& Blue( std::ostream& strm );
	std::ostream& Orange( std::ostream& strm );
	std::ostream& Yellow( std::ostream& strm );
	std::ostream& Turquoise( std::ostream& strm );
	std::ostream& Standard( std::ostream& strm );
}