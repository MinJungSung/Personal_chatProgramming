#include "pch.h"
#include <stdio.h>
#include "tipsware.h"


// A struct to manage logged in clients (for one person)
struct UserData {

	unsigned int h_socket; // socket handle
	char ip_address[16]; // Client address
};

// This function is called when a new user logs in
// ap_user_data already has logged in client information
// ap_server has an address for server object
void OnNewUser(UserData *ap_user_data, void *ap_server, int a_server_index) {

	char temp_str[64];
	sprint_s(temp_str, 64, "A new user logged in from %s", ap_user_data->ip_address);
	// Add a string with logged client to listbox(control id 1000)
	ListBox_InsertString(FindControl(1000), -1, temp_str);

}

int OnClientMessage(CurrentServerNetworkData *ap_data, void *ap_server, int a_server_index) {

	// Use delivered client information to claimed struct
	// When a server is created, Sizeof(Userdata) requests to be a specific size, 
	// internally user data is managed as UserData format
	UserData *p_user_data = (UserData *)ap_data->mp_net_user;
	char temp_str[128];
	if (ap_data->m_net_msg_id == 1_ { // Chatting data delivered (No.1 id is set by developer)
		// To check who sent , display the information with client's internet address in front of 
		// chat data
		sprintf_s(temp_str, 128, "%s : %s", p_user_data->ip_address, ap_data->mp_net_body_data);
		// Reproduce the chat information in listbox (control id 1000)
		ListBox_InsertString(FindControl(1000), -1, temp_str);
		// Send again to all clients
		BroadcastFrameData(ap_server, 1, temp_str, strlen(temp_str) + 1);
	
	}
	return 1;

}


//This program doesn't use special messages
NOT_USER_MESSAGE


int main() {

	ChangeWorkSize(620, 240); // Set WorkArea
	Clear(0, RGB(72, 87, 114)); // Window background RGB(72, 87, 114)
	StartSocketSystem(); // This program sets to use socket system

	//User data creates a server. This server calls OnNewUser, OnClientMessage,
	//OnCloseUser function based on its status and proceed.
	void *p_server = CreateServerSocket(sizeof(UserData), OnNewUser, OnClientMessage, OnCloseUser);




	CreateListBox(10, 30, 600, 200, 1000); // Create a listbox with No.1000
	SelectFontObject("굴림", 12); // Provide font and font size
	TextOut(15, 10, RGB(200, 255, 200), "User Chat list"); //Print listbox title


	ShowDisplay(); //Display Window
	return 0;
}
