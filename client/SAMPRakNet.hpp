#pragma once

#include <cstdint>
#include <string>
#include <exception>

#if defined _WIN32 || defined WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netinet/in.h>
typedef int SOCKET;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#if __has_include(<MTUSize.h>) 
#include <MTUSize.h> 
#endif

#ifndef MAXIMUM_MTU_SIZE
#define MAXIMUM_MTU_SIZE 1500
#endif

#define MAX_AUTH_RESPONSE_LEN (64)

#define MAX_UNVERIFIED_RPCS (5)

class SAMPRakNet
{
public:
	enum AuthType {
		AuthType_Invalid,
		AuthType_Player,
		AuthType_NPC
	};

	struct RemoteSystemData {
		uint8_t authIndex;
		AuthType authType;
		uint8_t unverifiedRPCs;

		RemoteSystemData() : authIndex(0), authType(AuthType_Invalid), unverifiedRPCs(0)
		{}
	};

	static uint8_t * Decrypt(uint8_t const * src, int len);
	static uint8_t * Encrypt(uint8_t const * src, int len);

	static uint16_t GetPort();
	static void SetPort(uint16_t value);

	static uint32_t GetToken() { return token_; }
	static void SeedToken() { token_ = rand(); }

	const char* GenerateAuth();
	bool		CheckAuth(uint8_t index, char* auth);

	static void SeedCookie();
	static uint16_t GetCookie(unsigned int address);

	static void SetTimeout(unsigned int timeout) { timeout_ = timeout; }
	static unsigned int GetTimeout() { return timeout_; }


	static void SetLogCookies(bool log) { logCookies_ = log; }
	static bool ShouldLogCookies() { return logCookies_; }

private:
	static uint8_t buffer_[MAXIMUM_MTU_SIZE];
	static uint32_t token_;
	static uint16_t portNumber;
	static unsigned int timeout_;
	static bool logCookies_;
};

class SAMPRakNetChecksumException : public std::exception
{
public:
	explicit
		SAMPRakNetChecksumException(uint8_t expected, uint8_t got);

	char const *
		what() const noexcept override;

	const uint8_t
		Expected,
		Got;
};
