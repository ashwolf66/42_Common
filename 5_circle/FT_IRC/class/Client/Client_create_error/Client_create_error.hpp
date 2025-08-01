#pragma once
#ifndef CLIENT_CREATE_ERROR_COPY_HPP
#define CLIENT_CREATE_ERROR_COPY_HPP

#include <stdexcept>
#include <string>

class ClientCreateError : public std::exception
{
private:
	std::string msg;
public:
	ClientCreateError(const std::string &message);
	~ClientCreateError() throw();
	virtual const char* what() const throw();
};

# endif