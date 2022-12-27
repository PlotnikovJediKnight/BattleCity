#include <iostream>
#include "protocols\fieldmessage.h"

using namespace std;
using namespace pv;


int main() {
	FieldMessage fieldMessage, fieldMessage2, fieldMessage3;

	cout << std::boolalpha << 
		fieldMessage.GetString(FieldMessage::Fields::CORR_ID) << endl;

	cout << fieldMessage2.GetString(FieldMessage::Fields::CORR_ID) << endl;
	cout << fieldMessage3.GetString(FieldMessage::Fields::CORR_ID) << endl;

	return 0;
}