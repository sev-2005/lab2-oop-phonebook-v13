#include "textprocessor.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <cctype>

TextProcessor::TextProcessor() : filename(nullptr)
{
	std::cout << "Вызван конструктор по умолчанию для объекта TextProcessor" << std::endl;
}

TextProcessor::TextProcessor(const char *filename)
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не может быть пустым");
	}

	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);

	std::cout << "Вызван конструктор с параметрами для объекта TextProcessor: " << filename << std::endl;
}

TextProcessor::TextProcessor(const TextProcessor &other)
{
	if (other.filename)
	{
		filename = new char[strlen(other.filename) + 1];
		strcpy(filename, other.filename);
	}
	else
	{
		filename = nullptr;
	}

	std::cout << "Вызван конструктор копирования для объекта TextProcessor" << std::endl;
}

TextProcessor::~TextProcessor()
{
	std::cout << "Вызван деструктор для объекта TextProcessor" << std::endl;
	delete[] filename;
}

TextProcessor &TextProcessor::operator=(const TextProcessor &other)
{
	if (this != &other)
	{
		delete[] filename;

		if (other.filename)
		{
			filename = new char[strlen(other.filename) + 1];
			strcpy(filename, other.filename);
		}
		else
		{
			filename = nullptr;
		}
	}
	return *this;
}

bool TextProcessor::isVowel(char c) const
{
	char lower = std::tolower(c);
	return lower == 'a' || lower == 'e' || lower == 'i' ||
		   lower == 'o' || lower == 'u' || lower == 'y';
}

bool TextProcessor::isWordSeparator(char c) const
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
		   c == '.' || c == ',' || c == '!' || c == '?' ||
		   c == ';' || c == ':' || c == '(' || c == ')' ||
		   c == '[' || c == ']' || c == '{' || c == '}' ||
		   c == '\"' || c == '\'';
}

char TextProcessor::toUpperCase(char c) const
{
	if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 'A';
	}
	return c;
}

void TextProcessor::setFilename(const char *filename)
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не может быть пустым");
	}

	delete[] this->filename;
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);
}

const char *TextProcessor::getFilename() const
{
	return filename;
}

void TextProcessor::processEnglishText()
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не установлено");
	}

	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw FileNotFoundException();
	}

	std::cout << "\n=== ОБРАБОТАННЫЙ АНГЛИЙСКИЙ ТЕКСТ ===" << std::endl;
	std::cout << "Файл: " << filename << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	char line[1000];
	bool inWord = false;
	bool newWord = true;

	while (file.getline(line, sizeof(line)))
	{
		if (file.fail() && !file.eof())
		{
			throw FileReadException();
		}

		for (int i = 0; line[i] != '\0'; i++)
		{
			if (isWordSeparator(line[i]))
			{
				// Конец слова или разделитель
				if (inWord)
				{
					inWord = false;
					newWord = true;
				}
				std::cout << line[i];
			}
			else
			{
				// Начало нового слова
				if (newWord)
				{
					if (isVowel(line[i]))
					{
						// Слово начинается с гласной - делаем первую букву прописной
						std::cout << toUpperCase(line[i]);
					}
					else
					{
						std::cout << line[i];
					}
					newWord = false;
					inWord = true;
				}
				else
				{
					// Продолжение слова
					std::cout << line[i];
				}
			}
		}
		std::cout << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Текст успешно обработан!" << std::endl;

	file.close();
}