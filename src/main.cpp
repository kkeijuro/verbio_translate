/*
 * main.cpp
 *
 *  @created: Nov 2019
 *  @author: Cristobal Pio
 *  @contact: keijuro@gmail.es
 */

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "dictionary.hpp"
#include "translator.hpp"

static std::map<std::string, uint64_t> test_cases_english = {
		{"eleven hundred", 1100},
		{"eleven hundred million", 1100000000},
		{"eleven thousand one hundred eleven", 11111},
		{"five hundred one", 501},
		{"five thousand", 5000},
		{"five thousand thirty three", 5033},
		{"forty seven", 47},
		{"one hundred twenty",120},
		{"one thousand one hundred million", 1100000000},
		{"thirteen million", 13000000},
		{"one hundred eleven", 111},
		{"one thousand one hundred eleven", 1111},
		{"one hundred eleven thousand one hundred eleven", 111111},
		{"one million one hundred eleven thousand one hundred eleven", 1111111},
		{"zero",0}
};

static std::map<std::string, uint64_t> test_cases_spanish = {
		{"cero", 0},
		{"ciento once", 111},
		{"ciento once mil", 111000},
		{"ciento once mil ciento once", 111111},
		{"ciento veinte", 120},
		{"mil millones mil quinientos veinte y cinco", 1000001525},
		{"mil quinientos", 1500},
		{"mil quinientos millones", 1500000000},
		{"mil quinientos veinte y cinco", 1525},
		{"mil ciento once", 1111},
		{"mil ciento once mil ciento once", 1111111},
		{"novecientos ochenta siete millones seis cientos cincuenta y cuatro mil tres cientos veintiuno",987654321},
		{"once mil ciento once", 11111},

};

struct dotted : std::numpunct<char> {
    char do_thousands_sep()   const { return '.'; }  // separate with dots
    std::string do_grouping() const { return "\3"; } // groups of 3 digits
    static void imbue(std::ostream &os) {
        os.imbue(std::locale(os.getloc(), new dotted));
    }
};

static std::string printInteger(uint64_t value) {
	std::stringstream ss;
    dotted::imbue(ss);
    ss << value;
    return ss.str();
}

int main() {
	Dictionary* english_dictionary = new MemoryDictionary();

	for(std::pair<std::string, uint64_t> test_case: test_cases_english) {
		NumberTranslator test_translate(english_dictionary);
		try {
			std::cout<<"Test Case: "<< test_case.first<<" "<<printInteger(test_translate.toNumber(test_case.first))<<std::endl;
			assert(test_translate.toNumber(test_case.first) == test_case.second);
		}
		catch(std::exception& ex) {
			std::cout<<"Catched Exception!: "<< ex.what()<<std::endl;
		}
	}
	Dictionary* spanish_dictionary = new MemoryDictionary(LANGUAGES::SPANISH);
	for(std::pair<std::string, uint64_t> test_case: test_cases_spanish) {
		NumberTranslator test_translate(spanish_dictionary);
		try {
			std::cout<<"Test Case: "<< test_case.first<<" "<<printInteger(test_translate.toNumber(test_case.first))<<" "<<test_case.second<<std::endl;
			assert(test_translate.toNumber(test_case.first) == test_case.second);
		}
		catch(std::exception& ex) {
			std::cout<<"Catched Exception!: "<< ex.what()<<std::endl;
		}
	}
};


