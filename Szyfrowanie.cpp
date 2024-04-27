#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void szyfr_cezara(int& klucz, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2);
void szyfr_podstawieniowy(string& plik_klucz, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2);
void szyfr_vigenera(string& klucz_vig, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2);
void otwarcie_pliku(int& opcja, int& metoda, string& plik_klucz, string& wejscie, vector <char>& tekst_jawny, vector <string>& tekst1);
void wyswietlanie(int& opcja, string& wyjscie, vector <string>& tekst1, vector <string>& tekst2);

int main()
{
    int metoda, opcja, klucz;
    string wejscie, wyjscie, plik_klucz, klucz_vig;
    vector <char> tekst_jawny, szyfr;
    vector <string> tekst1, tekst2;

    cout << "MENU:" << endl;
    cout << "1. Szyfr Cezara" << endl;
    cout << "2. Szyfr Podstawieniowy" << endl;
    cout << "3. Szyfr Vigenere'a" << endl;
    cout << "\nWybierz metode szyfrowania: ";
    cin >> metoda;

    system("cls");

    switch (metoda)
    {
    case 1:
    {
        cout << "Podaj nazwe pliku wejsciowego: ";
        cin >> wejscie;
        cout << "Podaj nazwe pliku wyjsciowego: ";
        cin >> wyjscie;
        cout << "Podaj klucz: ";
        cin >> klucz;

        while (!cin.good())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Niepoprawny klucz, sprobuj ponownie: ";
            cin >> klucz;
        }

        otwarcie_pliku(opcja, metoda, plik_klucz, wejscie, tekst_jawny, tekst1);
        szyfr_cezara(klucz, opcja, wyjscie, tekst_jawny, szyfr, tekst1, tekst2);
    }
    case 2:
    {
        cout << "Podaj nazwe pliku wejsciowego: ";
        cin >> wejscie;
        cout << "Podaj nazwe pliku wyjsciowego: ";
        cin >> wyjscie;
        cout << "Podaj nazwe pliku z kluczem: ";
        cin >> plik_klucz;

        otwarcie_pliku(opcja, metoda, plik_klucz, wejscie, tekst_jawny, tekst1);
        szyfr_podstawieniowy(plik_klucz, opcja, wyjscie, tekst_jawny, szyfr, tekst1, tekst2);
    }
    case 3:
    {
        cout << "Podaj nazwe pliku wejsciowego: ";
        cin >> wejscie;
        cout << "Podaj nazwe pliku wyjsciowego: ";
        cin >> wyjscie;
        cout << "Podaj klucz: ";
        cin >> klucz_vig;

        otwarcie_pliku(opcja, metoda, plik_klucz, wejscie, tekst_jawny, tekst1);
        szyfr_vigenera(klucz_vig, opcja, wyjscie, tekst_jawny, szyfr, tekst1, tekst2);
    }
    default:
        break;
    }
}

void szyfr_cezara(int& klucz, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2)
{
    int skok;

    if (opcja == 1 && klucz < 0)
    {
        klucz = abs(klucz);
        opcja = 2;
    }
    else if (opcja == 2 && klucz < 0)
    {
        klucz = abs(klucz);
        opcja = 1;
    }

    if (opcja == 1)
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                skok = tekst_jawny[i] - 'a';
                skok = (skok + klucz) % 26;
                szyfr.push_back('a' + skok);
            }
            else if (isupper(tekst_jawny[i]))
            {
                skok = tekst_jawny[i] - 'A';
                skok = (skok + klucz) % 26;
                szyfr.push_back('A' + skok);
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }
        }
    }
    else if (opcja == 2)
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                skok = 'z' - tekst_jawny[i];
                skok = (skok + klucz) % 26;
                szyfr.push_back('z' - skok);
            }
            else if (isupper(tekst_jawny[i]))
            {
                skok = 'Z' - tekst_jawny[i];
                skok = (skok + klucz) % 26;
                szyfr.push_back('Z' - skok);
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }
        }
    }

    system("cls");

    ofstream plik(wyjscie);

    for (int i = 0; i < szyfr.size(); i++)
    {
        plik << szyfr[i];
    }

    plik.close();

    wyswietlanie(opcja, wyjscie, tekst1, tekst2);
};

void szyfr_podstawieniowy(string& plik_klucz, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2)
{
    char znak, klucz_podst[26];


    ifstream plik_z_kluczem(plik_klucz);

    for (int i = 0; i < 26; i++)
    {
        plik_z_kluczem.get(znak);
        klucz_podst[i] = znak;

        cout << klucz_podst[i] << endl;
    }

    if (opcja == 1)         //szyfrowanie
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                for (int j = 97; j <= 122; j++)
                {
                    if (tekst_jawny[i] == char(j))
                    {
                        szyfr.push_back(klucz_podst[j - 97]);
                    }
                }
            }
            else if (isupper(tekst_jawny[i]))
            {
                for (int j = 65; j <= 90; j++)
                {
                    if (tekst_jawny[i] == char(j))
                    {
                        szyfr.push_back(toupper(klucz_podst[j - 65]));
                    }
                }
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }
        }
    }
    else if (opcja == 2)        //deszyfrowanie
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                for (int j = 0; j <= 25; j++)
                {
                    if (tekst_jawny[i] == klucz_podst[j])
                    {
                        szyfr.push_back(char(j + 97));
                    }
                }
            }
            else if (isupper(tekst_jawny[i]))
            {
                for (int j = 0; j <= 25; j++)
                {
                    if (tekst_jawny[i] == toupper(klucz_podst[j]))
                    {
                        szyfr.push_back(char(j + 65));
                    }
                }
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }
        }
    }

    system("cls");

    ofstream plik(wyjscie);

    for (int i = 0; i < szyfr.size(); i++)
    {
        plik << szyfr[i];
    }

    plik.close();

    wyswietlanie(opcja, wyjscie, tekst1, tekst2);

}

void szyfr_vigenera(string& klucz_vig, int& opcja, string& wyjscie, vector <char>& tekst_jawny, vector <char>& szyfr, vector <string>& tekst1, vector <string>& tekst2)
{
    int skok, skok_vig, j = 0;

    if (opcja == 1)
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                skok = tekst_jawny[i] - 'a';
                skok_vig = klucz_vig[j] - 'a';
                skok = (skok + skok_vig) % 26;
                szyfr.push_back('a' + skok);
                j++;
            }
            else if (isupper(tekst_jawny[i]))
            {
                skok = tekst_jawny[i] - 'A';
                skok_vig = klucz_vig[j] - 'a';
                skok = (skok + skok_vig) % 26;
                szyfr.push_back('A' + skok);
                j++;
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }

            if (j == klucz_vig.size())
            {
                j = 0;
            }
        }
    }
    else if (opcja == 2)
    {
        for (int i = 0; i < tekst_jawny.size(); i++)
        {
            if (islower(tekst_jawny[i]))
            {
                skok = 'z' - tekst_jawny[i];
                skok_vig = klucz_vig[j] - 'a';
                skok = (skok + skok_vig) % 26;
                szyfr.push_back('z' - skok);
                j++;
            }
            else if (isupper(tekst_jawny[i]))
            {
                skok = 'Z' - tekst_jawny[i];
                skok_vig = klucz_vig[j] - 'a';
                skok = (skok + skok_vig) % 26;
                szyfr.push_back('Z' - skok);
                j++;
            }
            else
            {
                szyfr.push_back(tekst_jawny[i]);
            }

            if (j == klucz_vig.size())
            {
                j = 0;
            }
        }
    }

    system("cls");

    ofstream plik(wyjscie);

    for (int i = 0; i < szyfr.size(); i++)
    {
        plik << szyfr[i];
    }

    plik.close();

    wyswietlanie(opcja, wyjscie, tekst1, tekst2);
}

void otwarcie_pliku(int& opcja, int& metoda, string& plik_klucz, string& wejscie, vector <char>& tekst_jawny, vector <string>& tekst1)
{
    string linia;
    char znak;

    ifstream plik(wejscie);

    if (!plik)
    {
        system("cls");
        cout << "Nie udalo sie otworzyc pliku :((" << endl;
        exit(EXIT_FAILURE);
    }

    while (plik.get(znak))
    {
        tekst_jawny.push_back(znak);
    }

    plik.close();

    if (metoda == 2)
    {
        plik.open(plik_klucz);

        if (!plik)
        {
            system("cls");
            cout << "Nie udalo sie otworzyc pliku z kluczem :((" << endl;
            exit(EXIT_FAILURE);
        }

        plik.close();
    }

    plik.open(wejscie);

    while (getline(plik, linia))
    {
        tekst1.push_back(linia);
    }

    plik.close();

    system("cls");

    cout << "1. Szyfrowanie" << endl;
    cout << "2. Deszyfrowanie" << endl;
    cout << "\nWybierz co chcesz zrobic:" << endl;
    cin >> opcja;

};

void wyswietlanie(int& opcja, string& wyjscie, vector <string>& tekst1, vector <string>& tekst2)
{
    string linia;
    int n = 0, a = 1, ktory_tekst = 1, ile_wierszy = 7;
    char komenda;

    ifstream plik2(wyjscie);

    while (getline(plik2, linia))
    {
        tekst2.push_back(linia);
    }

    while (a == 1)
    {
        int m = n + ile_wierszy;
        system("cls");

        if (m >= tekst2.size())
        {
            for (int i = n; i < tekst2.size(); i++)
            {
                if (ktory_tekst % 2 == 0)
                {
                    cout << tekst1[i] << endl;
                }
                else
                {
                    cout << tekst2[i] << endl;
                }
            }
        }
        else
        {
            for (int i = n; i < m; i++)
            {
                if (ktory_tekst % 2 == 0)
                {
                    cout << tekst1[i] << endl;
                }
                else
                {
                    cout << tekst2[i] << endl;
                }
            }
        }

        if (n == 0)
        {
            if (ktory_tekst % 2 == 0)
            {
                if (opcja == 1)
                {
                    cout << "\nn - nastepna strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\nn - nastepna strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
            }
            else
            {
                if (opcja == 1)
                {
                    cout << "\nn - nastepna strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\nn - nastepna strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
            }

        }
        else if (m >= tekst2.size())
        {
            if (ktory_tekst % 2 == 0)
            {
                if (opcja == 1)
                {
                    cout << "\np - poprzednia strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\np - poprzednia strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
            }
            else
            {
                if (opcja == 1)
                {
                    cout << "\np - poprzednia strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\np - poprzednia strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
            }

        }
        else
        {
            if (ktory_tekst % 2 == 0)
            {
                if (opcja == 1)
                {
                    cout << "\np - poprzednia strona, n - nastepna strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\np - poprzednia strona, n - nastepna strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
            }
            else
            {
                if (opcja == 1)
                {
                    cout << "\np - poprzednia strona, n - nastepna strona, s - tekst odszyfrowany, q - wyjscie: ";
                }
                else if (opcja == 2)
                {
                    cout << "\np - poprzednia strona, n - nastepna strona, s - tekst zaszyfrowany, q - wyjscie: ";
                }
            }
        }
        cin >> komenda;

        if (komenda == 'n')
        {
            if (m < tekst2.size())
            {
                n = n + ile_wierszy;
            }
        }
        else if (komenda == 'p')
        {
            if (n != 0)
            {
                n = n - ile_wierszy;
            }
        }
        else if (komenda == 'q')
        {
            a = 0;

            exit(EXIT_FAILURE);
        }
        else if (komenda == 's')
        {
            ktory_tekst++;
        }

    }
}