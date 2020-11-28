#include <string>
#include <cstring>

class ClientInfo {
public:
	void setId(std::string id);
	void setPassword(std::string password);
	std::string getId();
	std::string getPassword();

private:
	std::string id, password;
};
