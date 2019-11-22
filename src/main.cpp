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

int main() {
	//English
	std::vector<std::string> sentences_en({{"one apple"},
			{"eleven apples"},
			{"one hundred eleven apples"},
			{"one thousand one hundred eleven apples"},
			{"eleven thousand one hundred eleven apples"},
			{"one hundred eleven thousand one hundred eleven apples"},
			{"one million one hundred eleven thousand one hundred eleven apples"},
			{"eleven million one hundred eleven thousand one hundred eleven apples"},
			{"one hundred eleven million one hundred eleven thousand one hundred eleven apples"}});
	for(std::string sentence: sentences_en) {
		SentenceTranslator sentence_translator_en = SentenceTranslator(LANGUAGES::ENGLISH);
		std::cout << sentence_translator_en.translate(sentence)<<std::endl;
	}

	std::vector<std::string> sentences_sp({{"un avion"},
				{"once apples aviones"},
				{"ciento once aviones"},
				{"mil ciento once aviones"},
				{"once mil ciento once aviones"},
				{"ciento once mil ciento once aviones"},
				{"un millon ciento once mil ciento once aviones"},
				{"once millones ciento once mil ciento once aviones"},
				{"ciento once millones ciento once mil ciento once aviones"},
				{"ciento once millones ciento once mil ciento once aviones y un helicoptero"}});

		for(std::string sentence: sentences_sp) {
			SentenceTranslator sentence_translator_sp = SentenceTranslator(LANGUAGES::SPANISH);
			std::cout << sentence_translator_sp.translate(sentence)<<std::endl;
		}
};


