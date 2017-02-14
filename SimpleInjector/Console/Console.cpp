#include "Console.hpp"

HANDLE console_out_handle;

namespace FancyConsole
{
	std::ostream& Green( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		return strm;
	}

	std::ostream& Red( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_RED |  FOREGROUND_INTENSITY );
		return strm;
	}

	std::ostream& Blue( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		return std::cout;
	}

	std::ostream& Orange( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		return strm;
	}

	std::ostream& Yellow( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
		return strm;
	}

	std::ostream& Turquoise( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_BLUE | FOREGROUND_GREEN );
		return strm;
	}

	std::ostream& Standard( std::ostream& strm )
	{
		SetConsoleTextAttribute( console_out_handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN );
		return strm;
	}
}