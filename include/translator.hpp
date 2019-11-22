/*
 * translator.hpp
 *
 *  @created: Nov 2019
 *  @author: Cristobal Pio
 *  @contact: keijuro@gmail.es
 */

#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include "dictionary.hpp"

#ifndef INCLUDE_TRANSLATOR_HPP_
#define INCLUDE_TRANSLATOR_HPP_

class WordTranslator {
	public:
	WordTranslator();
	virtual void chainValue(std::stack<std::string>& new_word)= 0;
	virtual uint64_t collapse() const = 0;
	WordTranslator* getNextLink() const ;
	void setNextLink(WordTranslator* next_link);
	virtual ~WordTranslator();
	virtual WORDTYPE getType() const = 0;
	virtual uint64_t getValue() const = 0;
	friend bool operator<(const WordTranslator& translatorA, const WordTranslator& translatorB);
	friend bool operator>(const WordTranslator& translatorA, const WordTranslator& translatorB);
};

class WordSingleTranslator: public WordTranslator {
	public:
	WordSingleTranslator(uint64_t value, WORDTYPE type);
	void chainValue(std::stack<std::string>& new_word);
	uint64_t collapse() const;
	WORDTYPE getType() const;
	uint64_t getValue() const;
	WordTranslator* getNextLink() const { return NULL;};
	void setNextLink(WordTranslator* next_link){};
	virtual ~WordSingleTranslator(){};
	private:
	WORDTYPE type;
	uint64_t value;
};

class WordAccumulatorTranslator: public WordTranslator {
	public:
	WordAccumulatorTranslator(uint64_t value, const Dictionary *dictionary);
	void chainValue(std::stack<std::string>& new_word);
	uint64_t collapse() const;
	WORDTYPE getType() const;
	uint64_t getValue() const;
	WordTranslator* getNextLink() const {return this->next_link;};
	void setNextLink(WordTranslator* next_link){this->next_link = next_link;};
	const Dictionary* getDictionary();
	virtual ~WordAccumulatorTranslator();
	private:
	static WORDTYPE type;
	const Dictionary* dictionary;
	uint64_t final_value;
	WordTranslator* next_link;
	uint64_t value;
};

class UnityTranslator: public WordTranslator {
	public:
	UnityTranslator(const Dictionary *dictionary);
	void chainValue(std::stack<std::string>& new_word);
	uint64_t collapse() const;
	WORDTYPE getType() const;
	uint64_t getValue() const;
	WordTranslator* getNextLink() const {return this->next_link;};
	void setNextLink(WordTranslator* next_link){this->next_link = next_link;};
	virtual ~UnityTranslator();
	private:
	uint64_t final_value;
	WordTranslator* next_link;
	WordAccumulatorTranslator word_accumulator;
};

class MemoryDictionary: public Dictionary {
	public:
	MemoryDictionary(LANGUAGES language);
	MemoryDictionary();
	virtual ~MemoryDictionary();
	WordTranslator* translateWord(const std::string& word) const;
	bool hasWord(const std::string& word) const;
	private:
	virtual void changeLanguage(LANGUAGES language);
	Values* values;
};

class NumberTranslator {
	public:
	NumberTranslator(const Dictionary* dictionary);
	~NumberTranslator();
	uint64_t toNumber(std::stack<std::string>& return_vector);
	std::string getText();
	private:
	const Dictionary* dictionary;
	std::string text;
	uint64_t value;
	UnityTranslator *word_root;
	void createTree(std::stack<std::string>& word_vector);
	uint64_t calculateValues();
};

class SentenceTranslator {
	public:
	~SentenceTranslator();
	std::string translate(const std::string& string_to_translate);
	SentenceTranslator(LANGUAGES language);
	private:
	void setDictionary(const Dictionary * dictionary);
	std::string translateNumber(std::queue<std::string>& words);
	const Dictionary* dictionary;
	std::stringstream* final_sentence;
	static std::queue<std::string>& split(std::string strToSplit, char delimeter);
};


#endif /* INCLUDE_TRANSLATOR_HPP_ */
