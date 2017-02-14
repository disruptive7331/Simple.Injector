#include "Common.hpp"
#include "Utilities.hpp"
#include "NativeInject.hpp"

int main( )
{
	console_out_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	std::string process, filename;
	bool file_state;

	SetConsoleTitleA( "[x86/Native] Simple CLI Injector" );

	std::cout << FancyConsole::Blue << "Process: " << FancyConsole::Standard;
	std::cin >> process;

	std::cout << FancyConsole::Blue << "DLL: " << FancyConsole::Standard;
	std::cin >> filename;

	Utilities::ResolveFileSpecifier( process );
	file_state = Utilities::ResolvePathName( filename );

	system( "cls" );
	std::cout << FancyConsole::Blue << "Process: " << FancyConsole::Standard << process << std::endl;
	if ( file_state )
		std::cout << FancyConsole::Blue << "DLL: " << FancyConsole::Standard << filename << std::endl;
	else
	{
		std::cout << FancyConsole::Blue << "DLL: " << FancyConsole::Standard << "File does not exists" << std::endl;
		Utilities::ExitConsole( );
	}

	NativeInject injector;
	if ( !injector.PrepareEnvironment( process, filename ) || !injector.Inject( ) )
		std::cout << "Something went wrong :/" << std::endl;
	else
		std::cout << "Success." << std::endl;
}