#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <string>
#include <iostream>


/*
check if the request is a login request, and if so deseialize it
in: request info
out: login request
*/
LoginRequest JsonRequestPacketDeseializer::deserializeLoginRequest(RequestInfo r)
{
	LoginRequest l;
	if(r.requestCode == LOGIN_CODE)
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

/*
check if the request is a signup request, and if so deseialize it
in: request info
out: signup request
*/
SignupRequest JsonRequestPacketDeseializer::deserializeSignupRequest(RequestInfo r)
{
	SignupRequest s;
	if (r.requestCode == SIGN_CODE)
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
