/*
 * translator.hpp
 *
 *  @created: Nov 2019
 *  @author: Cristobal Pio
 *  @contact: keijuro@gmail.es
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include "translator.hpp"

MemoryDictionary::MemoryDictionary(): values(ValuesFactory::getValues(LANGUAGES::ENGLISH)){};
MemoryDictionary::MemoryDictionary(LANGUAGES language): values(ValuesFactory::getValues(language)){};
MemoryDictionary::~MemoryDictionary(){};

/*
 * Returns if dictionary contains selected word
 */
bool MemoryDictionary::hasWord(const std::string& word) const {
	return this->values->wordExists(word);
};


/*
 * Translate selected word. Its kind of class factory
 */
WordTranslator* MemoryDictionary::translateWord(const std::string& word) const {
	auto properties = this->values->getValueProperties(word);
	switch(properties.getType()) {
	case ACCUMULATOR:
		return new WordAccumulatorTranslator(properties.getValue(), this);
	case TEXT_IN_NUMBER:
	case SINGLE:
		return new WordSingleTranslator(properties.getValue(), properties.getType());
	};
	return NULL;
};

/*
 * Change Dictionary Language
 */
void MemoryDictionary::changeLanguage(LANGUAGES language) {
	this->values = ValuesFactory::getValues(language);
};

/*Word Translator:
 * three flavours:
 * WordAccumulatorTranslator -> For accumulator Values
 * UnityTranslator -> FOr Unity values
 * WordAccumulatorTranslator is different than UnityTranslator because they have different behavour on chaining values and
 * when returning if no data accumulated (Unity should return 0, WordAccumulator the value)
 * WordSingleTranslator -> For single Values
 */

WordTranslator::WordTranslator(){};

WordTranslator::~WordTranslator(){
};

bool operator<(const WordTranslator& translatorA, const WordTranslator& translatorB){
	return (translatorA.getValue() < translatorB.getValue());
};

bool operator>(const WordTranslator& translatorA, const WordTranslator& translatorB){
	return (translatorA.getValue() > translatorB.getValue());
};

WORDTYPE WordAccumulatorTranslator::type = WORDTYPE::ACCUMULATOR;
WordAccumulatorTranslator::WordAccumulatorTranslator(uint64_t value, const Dictionary* dictionary):
																		dictionary(dictionary),
																		final_value(value),
																		next_link(NULL),
																		value(value){};

void WordAccumulatorTranslator::chainValue(std::stack<std::string>& new_words) {
	std::deque<std::string> all_values;
	while(new_words.size() != 0) {
		auto word = new_words.top();
		new_words.pop();
		auto translated_word = dictionary->translateWord(word);
		if(translated_word->getType() == WORDTYPE::SINGLE) {
			all_values.push_back(word);
		}
		else {
			if((*translated_word > (*this))) {
				this->setNextLink(translated_word);
				translated_word->chainValue(new_words);
			}
			else {
				all_values.push_back(word);
			}
		}
	}
	if(all_values.size() > 0) {
		std::reverse(all_values.begin(), all_values.end());
		UnityTranslator word_root(this->dictionary);
		std::stack<std::string> m_stack(all_values);
		word_root.chainValue(m_stack);
		this->final_value *= word_root.collapse();
	}
};

uint64_t WordAccumulatorTranslator::collapse() const {
	uint64_t inherit_value = 0;
	if(this->getNextLink() != NULL) inherit_value = this->next_link->collapse();
	return this->final_value + inherit_value;
};

WORDTYPE WordAccumulatorTranslator::getType() const {
	return WordAccumulatorTranslator::type;
};

const Dictionary* WordAccumulatorTranslator::getDictionary(){
	return this->dictionary;
};

uint64_t WordAccumulatorTranslator::getValue() const {
	return this->value;
};

WordAccumulatorTranslator::~WordAccumulatorTranslator(){
	if(this->getNextLink() != NULL) delete this->getNextLink();
};

UnityTranslator::UnityTranslator(const Dictionary* dictionary): final_value(0), next_link(NULL), word_accumulator(1, dictionary){};

void UnityTranslator::chainValue(std::stack<std::string>& new_words) {
	while(new_words.size() != 0) {
		auto word = new_words.top();
		new_words.pop();
		auto dictionary = this->word_accumulator.getDictionary();
		auto translated_word = dictionary->translateWord(word);
		if(translated_word->getType() == WORDTYPE::SINGLE) final_value += translated_word->getValue();
		else {
			this->setNextLink(translated_word);
			translated_word->chainValue(new_words);
		}
	}
};

uint64_t UnityTranslator::collapse() const {
	uint64_t inherit_value = 0;
	if(this->getNextLink() != NULL) inherit_value = this->next_link->collapse();
	//std::cout<<"Value: "<< this->final_value + inherit_value<<std::endl;
	return this->final_value + inherit_value;
};

WORDTYPE UnityTranslator::getType() const {
	return this->word_accumulator.getType();
};

uint64_t UnityTranslator::getValue() const{
	return this->word_accumulator.getValue();
};

UnityTranslator::~UnityTranslator(){
	if(this->getNextLink() != NULL) delete this->getNextLink();
};

uint64_t WordSingleTranslator::collapse() const{
	return this->getValue();
};

WordSingleTranslator::WordSingleTranslator(uint64_t value, WORDTYPE type): type(type), value(value){};

void WordSingleTranslator::chainValue(std::stack<std::string>& new_word) {
	throw std::runtime_error("Unable to chain value on Single Value");
};

WORDTYPE WordSingleTranslator::getType() const {
	return this->type;
};

uint64_t WordSingleTranslator::getValue() const{
	return this->value;
};


NumberTranslator::NumberTranslator(const Dictionary* dictionary):
		dictionary(dictionary),
		value(0),
		word_root(NULL){};

NumberTranslator::~NumberTranslator(){
	delete word_root;
};

uint64_t NumberTranslator::toNumber(std::stack<std::string>& values){
	if(this->word_root) delete word_root;
	this->word_root = new UnityTranslator(this->dictionary);
	this->createTree(values);
	return this->calculateValues();
};

std::string NumberTranslator::getText(){
	return this->text;
};

/*
 * collapse will go link by link adding values and getting the final value
 */
uint64_t NumberTranslator::calculateValues() {
	return this->word_root->collapse();
};

void NumberTranslator::createTree(std::stack<std::string>& word_vector){
	this->word_root->chainValue(word_vector);
};


SentenceTranslator::~SentenceTranslator(){};

void SentenceTranslator::setDictionary(const Dictionary* dictionary) {
	this->dictionary = dictionary;
};

std::string SentenceTranslator::translate(const std::string& string_to_translate) {
	auto words = SentenceTranslator::split(string_to_translate, ' ');
	while(words.size() != 0) {
		auto word = words.front();
		if(!this->dictionary->hasWord(word)) {
			*final_sentence << word << " ";
			words.pop();
		}
		else *final_sentence << this->translateNumber(words) << " ";
	}
	return final_sentence->str();
};

std::queue<std::string>& SentenceTranslator::split(std::string str_to_split, char delimeter) {
	std::queue<std::string>* sentence_words = new std::queue<std::string>();
	std::stringstream ss(str_to_split);
	std::string item;
	while (std::getline(ss, item, delimeter)) {
		sentence_words->push(item);
	}
	return *sentence_words;
};

SentenceTranslator::SentenceTranslator(LANGUAGES language){
	this->dictionary = new MemoryDictionary(language);
	this->final_sentence = new std::stringstream;
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
};

std::string SentenceTranslator::translateNumber(std::queue<std::string>& words) {
	std::stack<std::string> numbers;
	auto word = words.front();
	words.pop();
	WordTranslator* translated_word = this->dictionary->translateWord(word);
	if(translated_word->getType() == WORDTYPE::TEXT_IN_NUMBER) return word;
	else numbers.push(word);
	bool out = false;
	while(!out) {
		auto word = words.front();
		if(this->dictionary->hasWord(word)) {
			if(!(translated_word->getType() == WORDTYPE::TEXT_IN_NUMBER)) {
				numbers.push(word);
			}
			words.pop();
		}
		else out = true;
	}
	NumberTranslator number_translator(this->dictionary);
	uint64_t value = number_translator.toNumber(numbers);
	return printInteger(value);
};
