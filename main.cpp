#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Note {
    string title;
    string text;
};

// Функция для создания заметки
void addNote(vector<Note>& notes) {
    Note note;
    cout << "Введите заголовок заметки: ";
    getline(cin >> ws, note.title);
    cout << "Введите текст заметки: ";
    getline(cin >> ws, note.text);
    notes.push_back(note);
}

// Функция для просмотра заметок
void viewNotes(vector<Note>& notes) {
    if (notes.empty()) {
        cout << "Заметок нет\n";
    } else {
        for (int i = 0; i < notes.size(); i++) {
            cout << "Заметка #" << i+1 << "\n"
                 << "Заголовок: " << notes[i].title << "\n"
                 << "Текст: " << notes[i].text << "\n";
        }
    }
}

// Функция для редактирования заметки
void editNote(vector<Note>& notes) {
    if (notes.empty()) {
        cout << "Заметок нет\n";
        return;
    }

    cout << "Выберите заметку, которую хотите отредактировать:\n";
    for (int i = 0; i < notes.size(); i++) {
        cout << i+1 << ". " << notes[i].title << "\n";
    }

    int choice;
    cin >> choice;

    if (choice < 1 || choice > notes.size()) {
        cout << "Некорректный выбор\n";
        return;
    }

    Note& note = notes[choice-1];
    cout << "Введите новый заголовок заметки: ";
    getline(cin >> ws, note.title);
    cout << "Введите новый текст заметки: ";
    getline(cin >> ws, note.text);
    cout << "Заметка успешно отредактирована\n";
}

// Функция для удаления заметки
void deleteNote(vector<Note>& notes) {
    if (notes.empty()) {
        cout << "Заметок нет\n";
        return;
    }

    cout << "Выберите заметку, которую хотите удалить:\n";
    for (int i = 0; i < notes.size(); i++) {
        cout << i+1 << ". " << notes[i].title << "\n";
    }

    int choice;
    cin >> choice;

    if (choice < 1 || choice > notes.size()) {
        cout << "Некорректный выбор\n";
        return;
    }

    notes.erase(notes.begin() + choice-1);
    cout << "Заметка успешно удалена\n";
}

// Функция для сохранения заметки
void saveNotesToFile(const vector<Note>& notes, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Ошибка открытия файла\n";
        return;
    }
    for (const auto& note : notes) {
        fout << note.title << endl << note.text << endl;
    }
    fout.close();
    cout << "Заметки сохранены в файл " << filename << endl;
}

// Функция для импорта заметки
vector<Note> loadNotesFromFile(const string& filename) {
    vector<Note> notes;
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка открытия файла\n";
        return notes;
    }
    Note note;
    while (getline(fin >> ws, note.title) && getline(fin >> ws, note.text)) {
        notes.push_back(note);
    }
    fin.close();
    cout << "Заметки загружены из файла " << filename << endl;
    return notes;
}


int main() {
    setlocale(LC_ALL, "Russian");
    vector<Note> notes; // создаем вектор заметок
    // Создаём дефолтную заметку
    Note note {"aboba", "abobus"};
    notes.push_back(note);
    while (true) {
        // выводим меню
        cout << "Выберите действие:\n"
             << "1. Добавить заметку\n"
             << "2. Просмотреть все заметки\n"
             << "3. Редактировать заметку\n"
             << "4. Удалить заметку\n"
             << "5. Сохранить заметки в файл\n"
             << "6. Загрузить заметки из файла\n"
             << "7. Выйти из приложения\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                addNote(notes);
                break;
            }
            case 2: {
                viewNotes(notes);
                break;
            }
            case 3: {
                editNote(notes);
                break;
            }
            case 4: {
                deleteNote(notes);
                break;
            }
            case 5: {
                cout << "Введите расположение файла:\n";
                string filename;
                cin >> filename;
                saveNotesToFile(notes, filename);
                break;
            }
            case 6: {
                cout << "Введите расположение файла:\n";
                string filename;
                cin >> filename;
                notes = loadNotesFromFile(filename);
                break;
            }
            case 7: {
                return 0; // завершаем приложение
            }
            default: {
                cout << "Некорректный выбор\n";
                break;
            }
        }
    }

    return 0;
}