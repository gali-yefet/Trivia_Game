#include "IRequestHandler.h"

/*
create a requestResult
in: buffer, new handler
out: requestResult
*/
RequestResult IRequestHandler::createRequestResult(std::vector<unsigned char> buffer, IRequestHandler* newHandler)
{
	RequestResult result;
	result.newHandler = newHandler;
	result.buffer = std::string(buffer.begin(), buffer.end());
	return result;
}
