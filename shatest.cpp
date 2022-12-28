#include <iostream>
#include <string>
#include <openssl/sha.h>
using namespace std;

int main()
{
	string s = "Hello World"; // can be anything of any length
	unsigned char sha_buffer[SHA_DIGEST_LENGTH];
	char digest[SHA_DIGEST_LENGTH*2];
	SHA1((unsigned char *)(s.c_str()), s.length(), sha_buffer);
	for (int i=0; i < SHA_DIGEST_LENGTH; i++) sprintf(&digest[i*2], "%02x", sha_buffer[i]); //converts to hex
	cout << "SHA digest: " << digest << endl;
}
