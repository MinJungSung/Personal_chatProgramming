#include <string>
#include <cstring>

class ClientInfo {
public:
	void setId(std::string id);
	void setPassword(std::string password);
	void setRoomNo(int RoomNo);
	std::string getId();
	std::string getPassword();
	int getRoomNo();

private:
	std::string id, password;
	int RoomNo;
};
