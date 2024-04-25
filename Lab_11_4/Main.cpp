#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Note
{
    string surname;
    string name;
    string number;
    int birthDay;
    int birthMonth;
    int birthYear;
};

void create(Note* S, const int N);
void print(Note* S, const int N);
void sortByBirthDate(Note* S, const int N);
void searchBySurname(Note* S, const int N, const string f_surname);
void saveToFile(Note* S, const int N, const string& filename);
void loadFromFile(Note*& S, int& N, string& filename);

int main()
{
    int N;
    cout << "Enter the number of users: ";
    cin >> N;

    Note* S = new Note[N];

    string filename;
    string f_surname;

    int menuItem;

    while (true)
    {
        cout << "Choose an action:" << endl;
        cout << "[1] - Enter user information" << endl;
        cout << "[2] - Display user information" << endl;
        cout << "[3] - Sort by dates of birth" << endl;
        cout << "[4] - Search for a person by surname" << endl;
        cout << "[5] - Save data to file" << endl;
        cout << "[6] - Load data from file" << endl;
        cout << "[0] - Exit the program" << endl;
        cout << "Enter: ";
        cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            create(S, N);
            break;
        case 2:
            print(S, N);
            break;
        case 3:
            sortByBirthDate(S, N);
            print(S, N);
            break;
        case 4:
            cout << "Enter search criteria: ";
            cout << "Surname";
            cin.get();
            cin.sync();
            getline(cin, f_surname);
            searchBySurname(S, N, f_surname);
            break;
        case 5:
            cout << "Enter the filename to save data: ";
            cin >> filename;
            saveToFile(S, N, filename);
            break;
        case 6:
            loadFromFile(S, N, filename);
            break;
        case 0:
            delete[] S;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}

void create(Note* S, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        cout << "User number: " << i + 1 << endl;
        cin.ignore();
        cout << "Surname: ";
        getline(cin, S[i].surname);
        cout << "Name: ";
        getline(cin, S[i].name);
        cout << "Number: ";
        getline(cin, S[i].number);
        cout << "Enter day of birth: ";
        cin >> S[i].birthDay;
        cout << "Enter month of birth: ";
        cin >> S[i].birthMonth;
        cout << "Enter year of birth: ";
        cin >> S[i].birthYear;
        cout << endl;
    }
}

void print(Note* S, const int N)
{
    cout << "=========================================================================" << endl;
    cout << "|  ¹  |   Surname    |  Name  |  Note  sign  |  Day   | Month  |  Year  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; ++i)
    {
        cout << "|" << setw(4) << right << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].name;
        cout << "|" << setw(14) << left << S[i].number;
        cout << "|" << setw(8) << left << S[i].birthDay;
        cout << "|" << setw(7) << left << S[i].birthMonth;
        cout << "|" << setw(7) << left << S[i].birthYear;
        cout << setw(6) << "|" << endl;
    }
    cout << "=========================================================================" << endl << endl;
}

void sortByBirthDate(Note* S, const int N)
{
    for (int i = 0; i < N - 1; ++i)
        for (int j = 0; j < N - i - 1; ++j)
            if (S[j].birthYear > S[j + 1].birthYear ||
                (S[j].birthYear == S[j + 1].birthYear && S[j].birthMonth > S[j + 1].birthMonth) ||
                (S[j].birthYear == S[j + 1].birthYear && S[j].birthMonth == S[j + 1].birthMonth && S[j].birthDay > S[j + 1].birthDay))
                swap(S[j], S[j + 1]);
}

void searchBySurname(Note* S, const int N, const string f_surname)
{
    bool found = false;
    for (int i = 0; i < N; ++i)
    {
        if (S[i].surname == f_surname)
        {
            found = true;
            cout << "=========================================================================" << endl;
            cout << "|  ¹  |   Surname    |  Name  |  Note  sign  |  Day   | Month  |  Year  |" << endl;
            cout << "-------------------------------------------------------------------------" << endl;
            cout << "|" << setw(4) << right << i + 1 << " ";
            cout << "|" << setw(14) << left << S[i].surname;
            cout << "|" << setw(8) << left << S[i].name;
            cout << "|" << setw(14) << left << S[i].number;
            cout << "|" << setw(8) << left << S[i].birthDay;
            cout << "|" << setw(7) << left << S[i].birthMonth;
            cout << "|" << setw(7) << left << S[i].birthYear;
            cout << setw(6) << "|" << endl;
            cout << "=========================================================================" << endl << endl;
        }
    }
    if (!found)
        cout << "User not found." << endl;
}

void saveToFile(Note* S, const int N, const string& filename)
{
    ofstream fout(filename, ios::binary);
    if (!fout)
    {
        cout << "Error opening file." << endl;
        return;
    }
    fout.write((char*)&N, sizeof(N));
    fout.write((char*)S, sizeof(Note) * N);
    fout.close();
    cout << "Data saved to file successfully." << endl;
}

void loadFromFile(Note*& S, int& N, string& filename)
{
    delete[] S;

    cout << "Enter the filename to load data: ";
    cin >> filename;

    ifstream fin(filename, ios::binary);
    if (!fin)
    {
        cout << "Error opening file." << endl;
        return;
    }
    fin.read((char*)&N, sizeof(N));
    S = new Note[N];
    fin.read((char*)S, sizeof(Note) * N);
    fin.close();
    cout << "Data loaded from file successfully." << endl;
}
