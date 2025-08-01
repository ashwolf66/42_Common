#include "Client_create_error.hpp"

ClientCreateError::ClientCreateError(const std::string &message)
	: msg("Client creation error: " + message) {}

ClientCreateError::~ClientCreateError() throw() {}

const char* ClientCreateError::what() const throw()
{
	return msg.c_str();
}