#include <iostream>
#include "protocols\fieldmessage.h"

using namespace std;
using namespace pv;


int main() {
	FieldMessage fieldMessage;

	cout << std::boolalpha <<
		fieldMessage.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;

	fieldMessage.SetIntField(FieldMessage::Fields::HIGHEST_SCORE, 1917);
	fieldMessage.SetIntField(FieldMessage::Fields::LIGHT_TANK_HEALTH, 2023);

	cout << fieldMessage.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;
	fieldMessage.SetStringField(FieldMessage::Fields::CURRENT_PLAYER_NAME, "VLADISLAV");
	cout << fieldMessage.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;
	//fieldMessage.DeleteField(FieldMessage::Fields::HIGHEST_SCORE);
	cout << fieldMessage.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;
	//fieldMessage.DeleteField(FieldMessage::Fields::CURRENT_PLAYER_NAME);
	cout << fieldMessage.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;

	auto str = fieldMessage.to_string();

	FieldMessage fieldMessage2;
	fieldMessage2.from_string(str);

	cout << "====================================" << endl;

	cout << fieldMessage2.GetInt(FieldMessage::Fields::MESSAGE_SIZE) << endl;
	cout << fieldMessage2.GetInt(FieldMessage::Fields::HIGHEST_SCORE) << endl;
	cout << fieldMessage2.GetInt(FieldMessage::Fields::LIGHT_TANK_HEALTH) << endl;
	cout << fieldMessage2.GetString(FieldMessage::Fields::CURRENT_PLAYER_NAME) << endl;

	//id got copied - bad semantics?
	cout << fieldMessage2.GetString(FieldMessage::Fields::CORR_ID) << endl;

	return 0;
}