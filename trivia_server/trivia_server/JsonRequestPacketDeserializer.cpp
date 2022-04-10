#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

bool JsonRequestPacketDeseializer::isRequestRelevant(RequestInfo r)
{
	return r.requestCode == SIGN_CODE;
}

RequestResult JsonRequestPacketDeseializer::handleRequest(RequestInfo r)
{
	RequestResult result;
	
	std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
	result.buffer = data;
	
	result.newHandler = new JsonRequestPacketDeseializer();
	
	return result;
}

LoginRequest JsonRequestPacketDeseializer::deserializeLoginRequest(RequestInfo r)
{
	LoginRequest l;
	JsonRequestPacketDeseializer j;// has to be for runnig the function while its a static function and virtual cant be static
	if(j.isRequestRelevant(r))
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password> }
		
		l.username = data.substr(data.find(':') + 1, data.find(',')); //extricate the username
		data = data.substr(data.find(',') + 1); // cuts the data string
		l.password = data.substr(data.find(':') + 1, data.find('}')); //extricate the password
	}
	return l;
}

SignupRequest JsonRequestPacketDeseializer::deserializeSignupRequest(RequestInfo r)
{
	SignupRequest s;
	JsonRequestPacketDeseializer j;
	if (j.isRequestRelevant(r))
	{
		std::string data(r.json.begin(), r.json.end());// converts the data from bytes to string
		//now the data looks like this:
		//{ username: <username>, password: <password>, email: <email> }

		s.username = data.substr(data.find(':') + 1, data.find(',')); //extricate the username
		data = data.substr(data.find(',') + 1); // cuts the data string
		s.password = data.substr(data.find(':') + 1, data.find(',')); //extricate the password
		data = data.substr(data.find(',') + 1); // cuts the data string
		s.email = data.substr(data.find(':') + 1, data.find('}')); //extricate the email

	}
	return s;
}
