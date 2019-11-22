/*
 * dictionary.hpp
 *
 *  @created: Nov 2019
 *  @author: Cristobal Pio
 *  @contact: keijuro@gmail.es
 */

#include <sstream>
#include "dictionary.hpp"

WordInformation::WordInformation(uint64_t value, WORDTYPE type){
	this->type = type;
	this->value = value;
};
WORDTYPE WordInformation::getType(){
	return this->type;
};
uint64_t WordInformation::getValue(){
	return this->value;
};


EnglishValues::EnglishValues(){
	this->values.insert({"zero", {0, WORDTYPE::SINGLE}});
	this->values.insert({"one", {1, WORDTYPE::SINGLE}});
	this->values.insert({"two", {2, WORDTYPE::SINGLE}});
	this->values.insert({"three", {3, WORDTYPE::SINGLE}});
	this->values.insert({"four", {4, WORDTYPE::SINGLE}});
	this->values.insert({"five", {5, WORDTYPE::SINGLE}});
	this->values.insert({"six", {6, WORDTYPE::SINGLE}});
	this->values.insert({"seven", {7, WORDTYPE::SINGLE}});
	this->values.insert({"eight", {8, WORDTYPE::SINGLE}});
	this->values.insert({"nine", {9, WORDTYPE::SINGLE}});
	this->values.insert({"ten", {10, WORDTYPE::SINGLE}});
	this->values.insert({"eleven", {11, WORDTYPE::SINGLE}});
	this->values.insert({"twelve", {12, WORDTYPE::SINGLE}});
	this->values.insert({"thirteen", {13, WORDTYPE::SINGLE}});
	this->values.insert({"fourteen", {14, WORDTYPE::SINGLE}});
	this->values.insert({"fifteen", {15, WORDTYPE::SINGLE}});
	this->values.insert({"sixteen", {16, WORDTYPE::SINGLE}});
	this->values.insert({"seventeen", {17, WORDTYPE::SINGLE}});
	this->values.insert({"eighteen", {18, WORDTYPE::SINGLE}});
	this->values.insert({"nineteen", {19, WORDTYPE::SINGLE}});
	this->values.insert({"twenty", {20, WORDTYPE::SINGLE}});
	this->values.insert({"thirty", {30, WORDTYPE::SINGLE}});
	this->values.insert({"forty", {40, WORDTYPE::SINGLE}});
	this->values.insert({"fifty", {50, WORDTYPE::SINGLE}});
	this->values.insert({"sixty", {60, WORDTYPE::SINGLE}});
	this->values.insert({"seventy", {70, WORDTYPE::SINGLE}});
	this->values.insert({"eighty", {80, WORDTYPE::SINGLE}});
	this->values.insert({"ninety", {90, WORDTYPE::SINGLE}});
	this->values.insert({"hundred", {100, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"thousand", {1000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"million", {1000000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"billion", {1000000000, WORDTYPE::ACCUMULATOR}});
};

bool EnglishValues::wordExists(std::string word) {
	auto value = this->values.find(word);
	if(value == this->values.end()) return false;
	return true;
};

const WordInformation& EnglishValues::getValueProperties(std::string word){
	auto value = this->values.find(word);
		if(value == this->values.end()) {
			std::stringstream ss;
			ss<<"value not found: "<<word<<std::endl;
			throw std::runtime_error(ss.str());
		}
		return value->second;
};

bool SpanishValues::wordExists(std::string word) {
	auto value = this->values.find(word);
	if(value == this->values.end()) return false;
	return true;
};

const WordInformation& SpanishValues::getValueProperties(std::string word){
	auto value = this->values.find(word);
	if(value == this->values.end()) {
		std::stringstream ss;
		ss<<"value not found: "<<word<<std::endl;
		throw std::runtime_error(ss.str());
	}
	return value->second;
};

SpanishValues::SpanishValues(){
	this->values.insert({"y", {0, WORDTYPE::TEXT_IN_NUMBER}});
	this->values.insert({"cero", {0, WORDTYPE::SINGLE}});
	this->values.insert({"un", {1, WORDTYPE::SINGLE}});
	this->values.insert({"uno", {1, WORDTYPE::SINGLE}});
	this->values.insert({"dos", {2, WORDTYPE::SINGLE}});
	this->values.insert({"tres", {3, WORDTYPE::SINGLE}});
	this->values.insert({"cuatro", {4, WORDTYPE::SINGLE}});
	this->values.insert({"cinco", {5, WORDTYPE::SINGLE}});
	this->values.insert({"seis", {6, WORDTYPE::SINGLE}});
	this->values.insert({"siete", {7, WORDTYPE::SINGLE}});
	this->values.insert({"ocho", {8, WORDTYPE::SINGLE}});
	this->values.insert({"nueve", {9, WORDTYPE::SINGLE}});
	this->values.insert({"diez", {10, WORDTYPE::SINGLE}});
	this->values.insert({"once", {11, WORDTYPE::SINGLE}});
	this->values.insert({"doce", {12, WORDTYPE::SINGLE}});
	this->values.insert({"trece", {13, WORDTYPE::SINGLE}});
	this->values.insert({"catorce", {14, WORDTYPE::SINGLE}});
	this->values.insert({"quince", {15, WORDTYPE::SINGLE}});
	this->values.insert({"dieciseis", {16, WORDTYPE::SINGLE}});
	this->values.insert({"diecisiete", {17, WORDTYPE::SINGLE}});
	this->values.insert({"dieciocho", {18, WORDTYPE::SINGLE}});
	this->values.insert({"diecinueve", {19, WORDTYPE::SINGLE}});
	this->values.insert({"veinte", {20, WORDTYPE::SINGLE}});
	this->values.insert({"veintiuno", {21, WORDTYPE::SINGLE}});
	this->values.insert({"treinta", {30, WORDTYPE::SINGLE}});
	this->values.insert({"cuarenta", {40, WORDTYPE::SINGLE}});
	this->values.insert({"cincuenta", {50, WORDTYPE::SINGLE}});
	this->values.insert({"sesenta", {60, WORDTYPE::SINGLE}});
	this->values.insert({"setenta", {70, WORDTYPE::SINGLE}});
	this->values.insert({"ochenta", {80, WORDTYPE::SINGLE}});
	this->values.insert({"noventa", {90, WORDTYPE::SINGLE}});
	this->values.insert({"cien", {100, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"ciento", {100, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"cientos", {100, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"quinientos", {500, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"novecientos", {900, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"mil", {1000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"millon", {1000000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"millones", {1000000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"billon", {1000000000000, WORDTYPE::ACCUMULATOR}});
	this->values.insert({"billones", {1000000000000, WORDTYPE::ACCUMULATOR}});
};


Values* ValuesFactory::getValues(LANGUAGES language) {
	switch(language) {
		case ENGLISH: return new EnglishValues();
		case SPANISH: return new SpanishValues();
	}
	return NULL;
};



