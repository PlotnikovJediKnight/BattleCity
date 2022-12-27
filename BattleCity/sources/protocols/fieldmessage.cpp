#include "protocols\fieldmessage.h"

#include <sstream>
#include <cassert>
#include <algorithm>
#include <bitset>
#include <limits>
using namespace std;

#include <iostream>

namespace pv {

	#define INT_FIELD &int_type_name_
	#define STRING_FIELD &string_type_name_

	constexpr size_t MESSAGE_SIZE_BYTES = 8;
	constexpr size_t MASK_BYTES = 8;
	constexpr size_t FIELD_TYPE_BYTES = 1;
	constexpr size_t STRING_LEN_BYTES = 2;
	constexpr size_t INT_VALUE_BYTES = 4;
																						  //================value============/		
	constexpr int MIN_LEN_MESS_BYTES = static_cast<int>(MESSAGE_SIZE_BYTES + MASK_BYTES + (FIELD_TYPE_BYTES + INT_VALUE_BYTES) + FIELD_TYPE_BYTES + STRING_LEN_BYTES);
	constexpr int NEW_INT_FIELD_BYTES = static_cast<int>(FIELD_TYPE_BYTES + INT_VALUE_BYTES);
	
	constexpr int NEW_STR_FIELD_BYTES = static_cast<int>(FIELD_TYPE_BYTES + STRING_LEN_BYTES);

	const char INT_FIELD_BYTECODE = 0;
	const char STR_FIELD_BYTECODE = 127;

	FieldMessage::FieldMessage()
		: field_to_type_p_{ 
			{Fields::MESSAGE_SIZE, INT_FIELD},
			{Fields::CORR_ID, STRING_FIELD},
			{Fields::LIGHT_TANK_HEALTH, INT_FIELD},
			{Fields::CURRENT_PLAYER_NAME, STRING_FIELD},
			{Fields::GAME_OVER_STR_RESOURCE, STRING_FIELD},
			{Fields::HIGHEST_SCORE, INT_FIELD},
			{Fields::__LIMIT_FIELD__, INT_FIELD}
		},
		  fields_{
			  { Fields::MESSAGE_SIZE, MIN_LEN_MESS_BYTES },
			  { Fields::CORR_ID, "FieldMessage#" + std::to_string(message_id_)}
		},
		  enums_masks_(MAX_FIELDS_SUPPORTED_COUNT)
		{
			assert(sizeof(int) == INT_VALUE_BYTES);
			for (size_t i = 0; i < MAX_FIELDS_SUPPORTED_COUNT; ++i) {
				FieldsUnderlyingType enumValue = GET_ENUMERATOR_VALUE(i);
				enums_masks_[i] = enumValue;
			}
			++message_id_;

			get<int>(fields_[Fields::MESSAGE_SIZE]) += get<string>(fields_[Fields::CORR_ID]).size(); 
		}

	bool FieldMessage::FieldHasType(Fields field, const std::string* typeP) const {
		auto mapIterator = field_to_type_p_.find(field);
		if (mapIterator == field_to_type_p_.end()) {
			throw out_of_range("No such field present in enum!");
		} else {
			const auto& fieldTypeP = mapIterator->second;
			if (fieldTypeP == typeP) {
				return true;
			} else {
				return false;
			}
		}
	}

	bool FieldMessage::FieldIsSet(Fields field) const {
		auto mapIterator = fields_.find(field);
		if (mapIterator == fields_.end()) {
			return false;
		} else {
			return true;
		}
	}

	bool FieldMessage::FieldIsPresentInEnum(Fields field) const {
		FieldsUnderlyingType getFieldValue = static_cast<FieldsUnderlyingType>(field);
		auto vecIterator = find(enums_masks_.begin(), enums_masks_.end(), getFieldValue);
		if (vecIterator == enums_masks_.end()) {
			return false;
		} else {
			return true;
		}
	}

	void FieldMessage::SetStringField(Fields fields, std::string stringValue) {
		FieldsUnderlyingType setFieldsValue = static_cast<FieldsUnderlyingType>(fields);

		for (size_t i = 0; i < enums_masks_.size(); ++i) {
			FieldsUnderlyingType enumValue = enums_masks_[i];
			
			if ((enumValue & setFieldsValue) == enumValue) {
				Fields setField = static_cast<Fields>(enumValue);
				if (FieldHasType(setField, STRING_FIELD)) {
					AddNewField(setField, stringValue);
				} else {
					throw logic_error("Field's type is not a string!");
				}
			}
		}
	}

	void FieldMessage::SetIntField(Fields fields, int intValue) {
		FieldsUnderlyingType setFieldsValue = static_cast<FieldsUnderlyingType>(fields);

		for (size_t i = 0; i < enums_masks_.size(); ++i) {
			FieldsUnderlyingType enumValue = enums_masks_[i];

			if ((enumValue & setFieldsValue) == enumValue) {
				Fields setField = static_cast<Fields>(enumValue);
				if (FieldHasType(setField, INT_FIELD)) {
					AddNewField(setField, intValue);
				}
				else {
					throw logic_error("Field's type is not an int!");
				}
			}
		}
	}

	void FieldMessage::AddNewField(Fields setField, int intValue) {
		fields_[setField] = intValue;
		get<int>(fields_[Fields::MESSAGE_SIZE]) += NEW_INT_FIELD_BYTES;
	}

	void FieldMessage::AddNewField(Fields setField, const string& stringValue) {
		fields_[setField] = stringValue;
		get<int>(fields_[Fields::MESSAGE_SIZE]) += stringValue.size();
		get<int>(fields_[Fields::MESSAGE_SIZE]) += NEW_STR_FIELD_BYTES;
	}

	string FieldMessage::GetString(Fields field) const {
		if (!FieldIsPresentInEnum(field)) throw out_of_range("No such field present in enum!");
		if (!FieldHasType(field, STRING_FIELD)) throw logic_error("Field's type is not a string!");
		if (!FieldIsSet(field)) throw out_of_range("Field is not set!");

		return get<string>(fields_.at(field));
	}

	int FieldMessage::GetInt(Fields  field) const {
		if (!FieldIsPresentInEnum(field)) throw out_of_range("No such field present in enum!");
		if (!FieldHasType(field, INT_FIELD)) throw logic_error("Field's type is not an int!");
		if (!FieldIsSet(field)) throw out_of_range("Field is not set!");

		return get<int>(fields_.at(field));
	}

	bool FieldMessage::Has(Fields fields) const {
		FieldsUnderlyingType hasFieldsValue = static_cast<FieldsUnderlyingType>(fields);

		for (size_t i = 0; i < enums_masks_.size(); ++i) {
			FieldsUnderlyingType enumValue = enums_masks_[i];

			if ((enumValue & hasFieldsValue) == enumValue) {
				Fields hasField = static_cast<Fields>(enumValue);
				if (!FieldIsSet(hasField)) {
					return false;
				}
			}
		}

		return true;
	}

	void FieldMessage::DeleteField(Fields field) {
		if (FieldIsPresentInEnum(field)) {
			if (field == Fields::MESSAGE_SIZE || field == Fields::CORR_ID) throw logic_error("Cannot delete this field!");

			auto deleteIterator = fields_.find(field);
			if (deleteIterator != fields_.end()) {
				RemoveField(deleteIterator, field);
			}
		}
	}

	void FieldMessage::RemoveField(map<Fields, SupportedVariant>::iterator deleteIterator, Fields field) {
		
		int bytesRemoved = 0;
		auto& supportedVariant = (*deleteIterator).second;
		if (holds_alternative<string>(supportedVariant)) {
			bytesRemoved += NEW_STR_FIELD_BYTES;
			bytesRemoved += get<string>(supportedVariant).size();
		} else
		if (holds_alternative<int>(supportedVariant)) {
			bytesRemoved += NEW_INT_FIELD_BYTES;
		} else {
			throw logic_error("Unknown variant removal!");
		}

		fields_.erase(deleteIterator);
		get<int>(fields_[Fields::MESSAGE_SIZE]) -= bytesRemoved;
	}

	void FieldMessage::WriteMessageSize(stringstream& ss, size_t msgSize) const {
		using cchar = const char;
		unsigned long long promoted = msgSize;
		assert(sizeof(promoted) == MESSAGE_SIZE_BYTES);
		ss.write(reinterpret_cast<cchar*>(&promoted), sizeof(promoted));
	}

	void FieldMessage::WriteBitmask(stringstream& ss) const {
		unsigned long long bitmask = 0;

		for (size_t i = 0; i < MAX_FIELDS_SUPPORTED_COUNT; ++i) {
			FieldsUnderlyingType enumValue = enums_masks_[i];
			Fields field = static_cast<Fields>(enumValue);
			if (fields_.find(field) != fields_.end()) {
				bitmask = (bitmask << 1ull) | 1ull;
			} else {
				bitmask = (bitmask << 1ull) | 0ull;
			}
		}

		auto bitmaskString = bitset<64>(bitmask).to_string();
		reverse(begin(bitmaskString), end(bitmaskString));
		bitmask = bitset<64>(bitmaskString).to_ullong();

		using cchar = const char;
		ss.write(reinterpret_cast<cchar*>(&bitmask), sizeof(bitmask));
	}

	void FieldMessage::WriteField(std::stringstream& ss, int intValue) const {
		ss.write(&INT_FIELD_BYTECODE, FIELD_TYPE_BYTES);
		assert(sizeof(int) == INT_VALUE_BYTES);

		using cchar = const char;
		ss.write(reinterpret_cast<cchar*>(&intValue), INT_VALUE_BYTES);
	}

	void FieldMessage::WriteField(std::stringstream& ss, const std::string& stringValue) const {
		ss.write(&STR_FIELD_BYTECODE, FIELD_TYPE_BYTES);
		assert(sizeof(unsigned short) == STRING_LEN_BYTES);

		unsigned short stringSize = static_cast<unsigned short>(stringValue.size());

		using cchar = const char;
		ss.write(reinterpret_cast<cchar*>(&stringSize), STRING_LEN_BYTES);

		ss.write(stringValue.c_str(), stringValue.size());
	}

	void FieldMessage::WriteFieldsData(std::stringstream& ss) const {
		for (const auto& [field, supportedVariant] : fields_)
		{
			if (holds_alternative<string>(supportedVariant)) {
				WriteField(ss, get<string>(supportedVariant));
			} else
			if (holds_alternative<int>(supportedVariant)) {
				WriteField(ss, get<int>(supportedVariant));
			}
			else {
				throw logic_error("Unknown variant to write!");
			}
		}
	}

	string FieldMessage::to_string() const {
		const size_t msgSize = get<int>(fields_.at(Fields::MESSAGE_SIZE));
		string serializedMessage;
		stringstream ss(serializedMessage);

		WriteMessageSize(ss, msgSize);
		WriteBitmask(ss);
		WriteFieldsData(ss);

		return ss.str();
	}

	void FieldMessage::SetMessageSize(int newMessageSize) {
		get<int>(fields_.at(Fields::MESSAGE_SIZE)) = newMessageSize;
	}

	int FieldMessage::ReadMessageSize(std::stringstream& ss) const {
		char msgSizeChar[MESSAGE_SIZE_BYTES];
		ss.read(msgSizeChar, MESSAGE_SIZE_BYTES);

		unsigned long long msgSize = 0;
		assert(sizeof(msgSize) == MESSAGE_SIZE_BYTES);

		memcpy(reinterpret_cast<char*>(&msgSize), static_cast<char*>(msgSizeChar), MESSAGE_SIZE_BYTES);

		if (msgSize < MIN_LEN_MESS_BYTES || msgSize > numeric_limits<int>::max())
			throw out_of_range("Message size from string is too long!");

		int messageSize = static_cast<int>(msgSize);
		return messageSize;
	}

	std::string FieldMessage::ReadBitmask(std::stringstream& ss) const {
		char bitmaskChar[MASK_BYTES];
		ss.read(bitmaskChar, MASK_BYTES);
		
		unsigned long long bitmask;
		assert(sizeof(bitmask) == MASK_BYTES);
		
		memcpy(reinterpret_cast<char*>(&bitmask), static_cast<char*>(bitmaskChar), MASK_BYTES);

		auto bitmaskString = bitset<64>(bitmask).to_string();
		reverse(begin(bitmaskString), end(bitmaskString));

		return bitmaskString;
	}

	void FieldMessage::SetDefaultFieldValues(const std::string& msgBitmask) {
		assert(msgBitmask.size() == MAX_FIELDS_SUPPORTED_COUNT);
		assert(enums_masks_.size() == MAX_FIELDS_SUPPORTED_COUNT);

		for (size_t i = 0; i < MAX_FIELDS_SUPPORTED_COUNT; ++i) {
			if (msgBitmask[i] == '1') {
				FieldsUnderlyingType enumValue = enums_masks_[i];
				Fields field = static_cast<Fields>(enumValue);

				auto fieldFoundIter = field_to_type_p_.find(field);
				if (fieldFoundIter == field_to_type_p_.end())
					throw out_of_range("Wrong bitmask format!");

				{
					auto& [field, fieldType] = *fieldFoundIter;
					if (fieldType == STRING_FIELD) {
						fields_[field] = "";
					} else
					if (fieldType == INT_FIELD) {
						fields_[field] = 0;
					} else {
						throw logic_error("Unsupported field type!");
					}
				}
			}
		}
	}

	int FieldMessage::ReadIntValue(std::stringstream& ss) {
		char intValueChar[INT_VALUE_BYTES];
		ss.read(intValueChar, INT_VALUE_BYTES);

		int intValue = 0;
		assert(sizeof(intValue) == INT_VALUE_BYTES);

		memcpy(reinterpret_cast<char*>(&intValue), static_cast<char*>(intValueChar), INT_VALUE_BYTES);

		return intValue;
	}

	string FieldMessage::ReadStringValue(std::stringstream& ss) {
		char strLenChar[STRING_LEN_BYTES];
		ss.read(strLenChar, STRING_LEN_BYTES);

		assert(sizeof(unsigned short) == STRING_LEN_BYTES);

		unsigned short strLength = 0;
		memcpy(reinterpret_cast<char*>(&strLength), static_cast<char*>(strLenChar), STRING_LEN_BYTES);
		
		string strValue(strLength, '\0');
		ss.read(strValue.data(), strLength);
		
		return strValue;
	}

	void FieldMessage::ReadField(stringstream& ss, int& writeToInt, size_t& supposedCurrPosition) {
		char fieldTypeByte;
		ss.read(&fieldTypeByte, FIELD_TYPE_BYTES);

		supposedCurrPosition++;
		if (ss.tellg() != supposedCurrPosition)
			throw out_of_range("Wrong string format! Failed to read field type.");


		if (fieldTypeByte == INT_FIELD_BYTECODE) {
			writeToInt = ReadIntValue(ss);

			supposedCurrPosition += INT_VALUE_BYTES;
			if (ss.tellg() != supposedCurrPosition)
				throw out_of_range("Wrong string format! Failed to read an int value.");

		} else {
			throw out_of_range("Wrong string format! Field type bytecode wrong.");
		}
	}

	void FieldMessage::ReadField(stringstream& ss, string& writeToString, size_t& supposedCurrPosition) {
		char fieldTypeByte;
		ss.read(&fieldTypeByte, FIELD_TYPE_BYTES);

		supposedCurrPosition++;
		if (ss.tellg() != supposedCurrPosition)
			throw out_of_range("Wrong string format! Failed to read field type.");


		if (fieldTypeByte == STR_FIELD_BYTECODE) {
			writeToString = ReadStringValue(ss);

			supposedCurrPosition += STRING_LEN_BYTES + writeToString.size();
			if (ss.tellg() != supposedCurrPosition)
				throw out_of_range("Wrong string format! Failed to read a string value.");
		} else {
			throw out_of_range("Wrong string format! Field type bytecode wrong.");
		}
	}

	void FieldMessage::ReadFieldValues(std::stringstream& ss, size_t& supposedCurrPosition) {
		for (auto& [field, supportedVariant] : fields_) {
			if (holds_alternative<string>(supportedVariant)) {
				ReadField(ss, get<string>(supportedVariant), supposedCurrPosition);
			} else
			if (holds_alternative<int>(supportedVariant)) {
				ReadField(ss, get<int>(supportedVariant), supposedCurrPosition);
			}
			else {
				throw logic_error("Unknown variant to write!");
			}
		}
	}

	void FieldMessage::from_string(const std::string& serializedMessage) {
		stringstream ss(serializedMessage);
		
		{
			int messageSize = ReadMessageSize(ss);
			SetMessageSize(messageSize);
			size_t const POS_AFTER_MSG_SIZE = 8;
			if (ss.tellg() != POS_AFTER_MSG_SIZE)
				throw out_of_range("Wrong string format! ReadMessage block.");
		}


		{
			string msgBitmask = ReadBitmask(ss);
			size_t const POS_AFTER_BITMASK = 16;
			if (ss.tellg() != POS_AFTER_BITMASK)
				throw out_of_range("Wrong string format! ReadBitmask block.");

			fields_.clear();
			SetDefaultFieldValues(msgBitmask);

			size_t supposedCurrPosition = POS_AFTER_BITMASK;
			ReadFieldValues(ss, supposedCurrPosition);

			if (supposedCurrPosition != get<int>(fields_.at(Fields::MESSAGE_SIZE))) {
				throw out_of_range("Wrong string format! Unnecessary trailing bytes.");
			}
		}
	}
}