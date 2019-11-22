/*
 * dictionary.cpp
 *
 *  @created: Nov 2019
 *  @author: Cristobal Pio
 *  @contact: keijuro@gmail.es
 */

#include <string>
#include <map>


#ifndef INCLUDE_DICTIONARY_HPP_
#define INCLUDE_DICTIONARY_HPP_

enum LANGUAGES: uint8_t {
    ENGLISH,
	SPANISH
};

enum WORDTYPE: uint8_t {
	TEXT_IN_NUMBER = 0,
	SINGLE = 54,
	ACCUMULATOR = 109,
};

class WordInformation {
	public:
	WordInformation(uint64_t value, WORDTYPE type);
	WORDTYPE getType();
	uint64_t getValue();
	private:
	uint64_t value;
	WORDTYPE type;
};

class Values {
	public:
	virtual const WordInformation& getValueProperties(std::string word) = 0;
	virtual bool wordExists(std::string word) = 0;
	virtual ~Values(){};
};

class EnglishValues: public Values {
	public:
	EnglishValues();
	virtual ~EnglishValues(){};
	const WordInformation& getValueProperties(std::string word);
	bool wordExists(std::string word);
	private:
	std::map<std::string, WordInformation> values;
};

class SpanishValues: public Values {
	public:
	SpanishValues();
	~SpanishValues(){};
	const WordInformation& getValueProperties(std::string word);
	bool wordExists(std::string word);
	private:
	std::map<std::string, WordInformation> values;
};

class ValuesFactory {
	public:
	static Values* getValues(LANGUAGES language);
};

class WordTranslator;
class Dictionary {
	public:
    virtual WordTranslator* translateWord(const std::string& word) const = 0;
    virtual bool hasWord(const std::string& word) const = 0;
    virtual ~Dictionary(){};
};

#endif /* INCLUDE_DICTIONARY_HPP_ */
