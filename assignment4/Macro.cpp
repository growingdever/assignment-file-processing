#include "Macro.h"

std::vector<std::string> GetTokensFromString(std::string input, std::string delimiter)
{
	std::vector<std::string> tokens;

	size_t pos = 0;
	std::string token;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		tokens.push_back( input.substr(0, pos) );
		input.erase(0, pos + delimiter.length());
	}

	if( input.size() > 0 ) {
		tokens.push_back( input );
	}

	return tokens;
}