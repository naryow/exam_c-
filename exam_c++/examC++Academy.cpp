#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Класс для управления комнатами
class Room {
private:
    int vip;      // ВИП номера
    int econom;   // Эконом номера
    int oneRoom;  // Одноместные номера
    int twoRoom;  // Двухместные номера
    int price;    // Стоимость номера за день
    int number;   // Номер комнаты
    int days;     // Количество дней проживания

public:
    Room(int vip, int econom, int oneRoom, int twoRoom)
        : vip(vip), econom(econom), oneRoom(oneRoom), twoRoom(twoRoom), days(0) {}

    // Метод для заселения
    void checkIn(int roomType) {
        if (roomType == 1 && econom > 0) {
            econom--;
            cout << "Заселение в эконом номер. Осталось эконом номеров: " << econom << endl;
        }
        else if (roomType == 2 && vip > 0) {
            vip--;
            cout << "Заселение в ВИП номер. Осталось ВИП номеров: " << vip << endl;
        }
        else {
            cout << "Номера этого типа закончились." << endl;
        }
    }

    // Метод для продления пребывания
    void entention(int extraDays) {
        days += extraDays;
        cout << "Продление номера на " << extraDays << " дней. Всего дней: " << days << endl;
    }

    // Метод для выселения и расчёта стоимости проживания
    int checkOut(int roomType, int roomNumber, int pricePerDay) {
        int totalCost = days * pricePerDay;

        if (roomType == 1) {
            econom++; // добавление свободных номеров
        }
        else if (roomType == 2) {
            vip++;    // добавление свободных номеров
        }

        cout << "Гость выселился из номера #" << roomNumber << ". Общая стоимость проживания: " << totalCost << " рублей." << endl;
        return totalCost;
    }

    // Метод для записи данных о выселении в файл
    void logCheckOut(int roomType, int roomNumber, int totalCost) {
        ofstream outfile("journal.txt", ios::app); 
        if (outfile.is_open()) {
            outfile << roomType << "," << roomNumber << "," << totalCost << endl;
            outfile.close();
        }
        else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }
};

// Класс отеля, который управляет комнатами
class Hotel {
private:
    Room room;  
    int priceEconom = 1200;   // Цена за эконом номер в день
    int priceVip = 4000;      // Цена за ВИП номер в день

public:
    Hotel(Room r) : room(r) {}

    // Заселение в номер
    void guestCheckIn(int roomType) {
        room.checkIn(roomType);
    }

    // Продление пребывания
    void extendStay(int days) {
        room.entention(days);
    }

    // Выселение из номера
    void guestCheckOut(int roomType, int roomNumber) {
        int pricePerDay = (roomType == 1) ? priceEconom : priceVip;
        int totalCost = room.checkOut(roomType, roomNumber, pricePerDay);
        room.logCheckOut(roomType, roomNumber, totalCost); 
    }
};

// Класс журнала для записи операций (заселение, выселение)
class Journal {
private:
    vector<string> logs;  // Хранение записей
public:
    // Добавление записи в журнал
    void addLog(const string& log) {
        logs.push_back(log);
    }

    // Вывод всех записей журнала
    void showLogs() {
        cout << "Журнал событий:" << endl;
        for (const auto& log : logs) {
            cout << log << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");

    Room room(2, 3, 1, 2);   // Создание объекта Room (ВИП - 2, эконом - 3, одноместные - 1, двухместные - 2)
    Hotel hotel(room);       
    Journal journal;          

    hotel.guestCheckIn(1);    // Заселение в эконом номер
    journal.addLog("Гость заселён в эконом номер.");

    hotel.extendStay(3);      // Продление на 3 дня
    journal.addLog("Пребывание продлено на 3 дня.");

    hotel.guestCheckOut(1, 1);  // Выселение из эконом номера
    journal.addLog("Гость выселился из эконом номера.");

    hotel.guestCheckIn(2);    // Заселение в ВИП номер
    journal.addLog("Гость заселён в ВИП номер.");

    hotel.extendStay(2);      // Продление на 2 дня
    journal.addLog("Пребывание продлено на 2 дня.");

    hotel.guestCheckOut(2, 2);  // Выселение из ВИП номера
    journal.addLog("Гость выселился из ВИП номера.");

    journal.showLogs();       // Показать журнал событий

    return 0;
}
