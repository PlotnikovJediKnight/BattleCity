#include "protocols\fieldmessage.h"

#include <algorithm>
using namespace std;

#include <iostream>

namespace pv {

	#define INT_FIELD &int_type_name_
	#define STRING_FIELD &string_type_name_

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
			  { Fields::MESSAGE_SIZE, 0 },
			  { Fields::CORR_ID, "FieldMessage#" + std::to_string(message_id_)}
		},
		  enums_masks_(MAX_FIELDS_SUPPORTED_COUNT)
		{
			for (size_t i = 0; i < MAX_FIELDS_SUPPORTED_COUNT; ++i) {
				FieldsUnderlyingType enumValue = GET_ENUMERATOR_VALUE(i);
				enums_masks_[i] = enumValue;
			}
			++message_id_;
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
					fields_[setField] = stringValue;
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
					fields_[setField] = intValue;
				}
				else {
					throw logic_error("Field's type is not an int!");
				}
			}
		}
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
			auto deleteIterator = fields_.find(field);
			if (deleteIterator != fields_.end()) {
				fields_.erase(deleteIterator);
			}
		}
	}
}