#include "messageList.h"

using namespace std;

string MessageList::printMessage(int m_choice, string m_param){
	string result = "";
	switch(m_choice){
		case 0:
			result += "You successfully created a room";
			break;
		case 1:
			result += "You successfully joined the chat";
			break;
		case 2:
			result += "You left the chat";
			break;
		case 3:
			result += m_param + " joined the chat";
			break;
		case 4:
			result += m_param + " left the chat";
			break;
		case 5:
			result += m_param + " is incorrect input";
			break;
		case 6:
			result += "Which room do you want to join?";
			break;
		case 7:
			result += "You are already in the chat";
			break;
		case 8:
			result += "You are already in the lounge";
			break;
		case 9:
			result += "Same username already exitst";
			break;
		case 10:
			result += m_param;
			break;
		case 11:
			result += "Successfully connected";
			break;
		case 12:
			result += "Username or password is incorrect";
			break;
		case 13:
			result += m_param + " changed";
			break;
		case 14:
			result += "Cannot change clientInfo";
			break;
	} 
	return result += "\n";
}
