#include <iostream>
#include "note.h"
#include "phonebook.h" // ДОБАВЛЯЕМ новый заголовочный файл

// УБИРАЕМ старый класс PhoneBook (он теперь в отдельных файлах)
// ОСТАВЛЯЕМ прототипы функций из первого коммита и ДОБАВЛЯЕМ новые

PhoneBook book; // Глобальная телефонная книга

void displayMainMenu()
{
	std::cout << "\n=== ЗАПИСНАЯ КНИГА (Вариант 13) ===" << std::endl;
	std::cout << "1. Добавить контакт" << std::endl;
	std::cout << "2. Удалить контакт" << std::endl;
	std::cout << "3. Редактировать контакт" << std::endl;
	std::cout << "4. Поиск по месяцу рождения" << std::endl;
	std::cout << "5. Показать все контакты" << std::endl;
	std::cout << "6. Обработать английский текст" << std::endl;
	std::cout << "7. Информация о книге" << std::endl;
	std::cout << "0. Выход" << std::endl;
	std::cout << "Выберите действие: ";
}

void displayAddMenu()
{
	std::cout << "\n=== ДОБАВЛЕНИЕ КОНТАКТА ===" << std::endl;
	std::cout << "1. Базовый контакт" << std::endl;
	std::cout << "2. Рабочий контакт" << std::endl;
	std::cout << "0. Назад" << std::endl;
	std::cout << "Выберите тип контакта: ";
}

// ЗАМЕНА старых заглушек на реальную реализацию
void addBasicContact(PhoneBook &book)
{
	try
	{
		NOTE *newContact = new NOTE();
		std::cout << "\n--- Создание базового контакта ---" << std::endl;
		std::cin >> *newContact;

		int position;
		std::cout << "Введите позицию для добавления (-1 для конца): ";
		std::cin >> position;

		book.addContact(newContact, position);
		std::cout << "✅ Базовый контакт успешно добавлен!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при добавлении: " << e.what() << std::endl;
	}
}

void addWorkContact(PhoneBook &book)
{
	try
	{
		char name[100], phone[20], company[100], position[100];
		int day, month, year;

		std::cout << "\n--- Создание рабочего контакта ---" << std::endl;
		std::cout << "Введите ФИО: ";
		std::cin.ignore();
		std::cin.getline(name, 100);

		std::cout << "Введите телефон: ";
		std::cin.getline(phone, 20);

		std::cout << "Введите день рождения (день месяц год): ";
		std::cin >> day >> month >> year;

		std::cout << "Введите компанию: ";
		std::cin.ignore();
		std::cin.getline(company, 100);

		std::cout << "Введите должность: ";
		std::cin.getline(position, 100);

		WorkNote *newContact = new WorkNote(name, phone, day, month, year, company, position);

		int pos;
		std::cout << "Введите позицию для добавления (-1 для конца): ";
		std::cin >> pos;

		book.addContact(newContact, pos);
		std::cout << "✅ Рабочий контакт успешно добавлен!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при добавлении: " << e.what() << std::endl;
	}
}

void deleteContact(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	std::cout << "\n=== УДАЛЕНИЕ КОНТАКТА ===" << std::endl;
	std::cout << "1. Удалить по индексу" << std::endl;
	std::cout << "2. Удалить по номеру телефона" << std::endl;
	std::cout << "0. Назад" << std::endl;
	std::cout << "Выберите способ: ";

	int choice;
	std::cin >> choice;

	try
	{
		switch (choice)
		{
		case 1:
		{
			int index;
			std::cout << "Введите индекс контакта (1-" << book.getSize() << "): ";
			std::cin >> index;
			book.removeContact(index - 1);
			std::cout << "✅ Контакт успешно удален!" << std::endl;
			break;
		}
		case 2:
		{
			char phone[20];
			std::cout << "Введите номер телефона: ";
			std::cin >> phone;
			book.removeContactByPhone(phone);
			std::cout << "✅ Контакт успешно удален!" << std::endl;
			break;
		}
		case 0:
			return;
		default:
			std::cout << "❌ Неверный выбор!" << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при удалении: " << e.what() << std::endl;
	}
}

void editContact(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	std::cout << "\n=== РЕДАКТИРОВАНИЕ КОНТАКТА ===" << std::endl;
	book.displayAllContacts();

	int index;
	std::cout << "Введите индекс контакта для редактирования (1-" << book.getSize() << "): ";
	std::cin >> index;

	try
	{
		book.editContact(index - 1);
		std::cout << "✅ Контакт успешно отредактирован!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при редактировании: " << e.what() << std::endl;
	}
}

void searchByBirthMonth(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	int month;
	std::cout << "\n=== ПОИСК ПО МЕСЯЦУ РОЖДЕНИЯ ===" << std::endl;
	std::cout << "Введите номер месяца (1-12): ";
	std::cin >> month;

	try
	{
		book.findContactsByBirthMonth(month);
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при поиске: " << e.what() << std::endl;
	}
}

void displayAllContacts(PhoneBook &book)
{
	book.displayAllContacts();
}

void processEnglishText()
{
	std::cout << "\n[ЗАГЛУШКА] Обработка английского текста будет реализована в коммите 3" << std::endl;
}

// НОВАЯ функция для демонстрации функциональности
void demonstratePhoneBookFunctionality()
{
	std::cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ЗАПИСНОЙ КНИГИ ===" << std::endl;

	try
	{
		// Добавление тестовых контактов в разном алфавитном порядке
		NOTE *contact1 = new NOTE("Петров Петр", "+79123456789", 15, 5, 1990);
		NOTE *contact2 = new NOTE("Алексеев Алексей", "+79987654321", 20, 10, 1985);
		WorkNote *contact3 = new WorkNote("Сидорова Мария", "+79551234567", 10, 3, 1988, "ООО Ромашка", "Директор");
		NOTE *contact4 = new NOTE("Иванов Иван", "+79031234567", 25, 5, 1992); // Тот же месяц, что и Петров

		book.addContact(contact1);
		book.addContact(contact2);
		book.addContact(contact3);
		book.addContact(contact4);

		std::cout << "\n--- Все контакты после добавления (отсортированы по алфавиту) ---" << std::endl;
		book.displayAllContacts();

		std::cout << "\n--- Поиск по месяцу рождения (май - месяц 5) ---" << std::endl;
		book.findContactsByBirthMonth(5);

		std::cout << "\n--- Поиск по несуществующему месяцу (13) ---" << std::endl;
		try
		{
			book.findContactsByBirthMonth(13);
		}
		catch (const std::exception &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}

// СУЩЕСТВУЮЩАЯ функция из первого коммита (НЕ ТРОГАЕМ)
void demonstrateClasses()
{
	std::cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССОВ ===" << std::endl;

	try
	{
		// Демонстрация базового класса
		NOTE note1("Иванов Иван", "+79123456789", 15, 5, 1990);
		note1.printInfo();

		std::cout << "\n--- Демонстрация наследования ---" << std::endl;
		WorkNote workNote1("Петров Петр", "+79987654321", 20, 10, 1985, "ООО Ромашка", "Менеджер");
		workNote1.printInfo();

		std::cout << "\n--- Демонстрация исключений ---" << std::endl;
		try
		{
			NOTE invalidNote("", "+79123456789", 15, 5, 1990);
		}
		catch (const EmptyFieldException &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}

		try
		{
			NOTE invalidDateNote("Сидоров Алексей", "+79123456789", 32, 13, 1990);
		}
		catch (const InvalidDateException &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}

		std::cout << "\n--- Демонстрация сравнения по алфавиту ---" << std::endl;
		NOTE note2("Алексеев Алексей", "+79234567890", 10, 3, 1988);
		std::cout << "note1 < note2: " << (note1 < note2 ? "true" : "false") << std::endl;
		std::cout << "note2 < note1: " << (note2 < note1 ? "true" : "false") << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}

int main()
{
	std::cout << "ЛАБОРАТОРНАЯ РАБОТА №2 - КОММИТ 2 (Вариант 13)" << std::endl;
	std::cout << "Полная функциональность записной книги" << std::endl;

	// Демонстрация из первого коммита
	demonstrateClasses();

	// Новая демонстрация для второго коммита
	demonstratePhoneBookFunctionality();

	// Основное меню (обновленное)
	int choice;
	do
	{
		displayMainMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int addChoice;
			do
			{
				displayAddMenu();
				std::cin >> addChoice;
				switch (addChoice)
				{
				case 1:
					addBasicContact(book);
					break;
				case 2:
					addWorkContact(book);
					break;
				case 0:
					break;
				default:
					std::cout << "❌ Неверный выбор!" << std::endl;
				}
			} while (addChoice != 0);
			break;
		}
		case 2:
			deleteContact(book);
			break;
		case 3:
			editContact(book);
			break;
		case 4:
			searchByBirthMonth(book);
			break;
		case 5:
			displayAllContacts(book);
			break;
		case 6:
			processEnglishText();
			break;
		case 7:
			std::cout << "📊 Информация о телефонной книге:" << std::endl;
			std::cout << "Количество контактов: " << book.getSize() << std::endl;
			std::cout << "Состояние: " << (book.isEmpty() ? "пуста" : "есть контакты") << std::endl;
			break;
		case 0:
			std::cout << "Выход из программы..." << std::endl;
			break;
		default:
			std::cout << "❌ Неверный выбор!" << std::endl;
		}
	} while (choice != 0);

	return 0;
}