#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int n =3000;//количество строк
int all = 3000;
int m = 6;
int iter = 0;
int* table = new int[n];
int itern = 0;
string render()
{
    int a = 0;
    string s1 = "      ";
    for (int i = 0; i < s1.length(); i++)
    {
        
        if (i != 3)
        {
            s1[i] = '0' + rand() % ('9' - '0');
        }
        if (i == 3)
        {
            s1[i] = 'A' + rand() % ('Z' - 'A');
        }
    }
    return s1;
}
int hash_number(string q1)
{
    int heshik = 0;
    char num;
    for (int i = 0; i < m; i++) {
        num = q1[i];
        heshik += pow(int(num) * (i + 1), 2);
    }
    return heshik%n;
}
void blunder(string*& a, string l)
{
    int hesh = 0;
    int i = 0;
    int c = 3;
    int d = 7;
    iter = 0;
    while (iter<25)
    {
        iter++;
        hesh = hash_number(l) + c * i + d * i*i;
        hesh %= n;
        if ((a[hesh] == " ")||(a[hesh]=="DEL")) {
            a[hesh] = l;
            break;
        }
        else i++;
    }
    itern = hesh;
}
void deletik(string*& a, int fin)
{
    a[fin] = "DEL";
    all--;
}
int find(string *&a, string l)
{

    int hesh = 0;
    int i = 0;
    int c = 3;
    int d = 7;
    while (i < 25)
    {
        hesh = hash_number(l) + c * i + d * i * i;
        hesh %= n;
        if (a[hesh] == l) {
            return hesh;
        }
        if (a[hesh] == " ") return -1;
        else i++;
    }
    return -1;
}
void find_col(string*& a, string h)
{
    cout << "Элементы, вызвавшие коллизию с данным" << endl;
    int hesh = hash_number(h);
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        if ((a[i] == " ") || (a[i] == " DEL")) continue;
        if ((hash_number(a[i]) == hesh) && (a[i] != h))
        {
            cout << a[i] << endl;
            t++;
        }
    }
    if (t == 0)
    {
        cout << "Коллизий у данного элемента нет" << endl;
    }
}
int check(string t)
{
    if (t.length() != 6)
    {
        cout << "Неправильный код" << endl;
        return -1;
    }
    for (int i = 0; i < 6; i++)
    {
        if (i == 3)
        {
            if ((t[i] < 'A') || (t[i] > 'Z'))
            {
                cout << "Неправильный код" << endl;
                return -1;
            }
        }
        else
        {
            if ((t[i] < '0') || (t[i] > '9'))
            {
                cout << "Неправильный код" << endl;
                return-1;
            }
        }
    }
    return 0;
}

int main()
{
    int hesh = 0;
    setlocale(LC_ALL, "RUS");
    string* ss = new string[n];
    string* for_col = new string[n];
    string k;
    srand(time(0));
    int q = 0;
    string key;
    int find_result = 0;
    int x=0;
    int ent=1;
    string add;
    for (int i = 0; i < n; i++)
    {
        ss[i] = " ";
        for_col[i] = " ";
        table[i] = 0;
    }
    while (ent != 0) {
        cout << "Вот меню программы, введите цифру в качестве действия" << endl;
        cout << "1. Заполнить полностью таблицу" << endl;
        cout << "2. Добавить элементы в хеш-таблицу" << endl;
        cout << "3. Просмотреть хеш-таблицу" << endl;
        cout << "4. Поиск элемента в хеш-таблице" << endl;
        cout << "5. Сохранить хеш таблицу в файл" << endl;
        cout << "0. Выход" << endl;
        cout << " Введите ваш выбор: ";
        cin >> ent;

        if (ent == 1) {
            for (int i = 0; i < n; i++)
            {
                k = render();
                hesh = hash_number(k);
                if (ss[hesh] == " ") ss[hesh] = k;

                else {
                    table[hesh]++;
                    for_col[q] = k;
                    q++;
                }
            }
            for (int i = 0; i < q; i++)
            {
                k = for_col[i];
                blunder(ss, k);
            }
            cout << "Сделано" << endl;
            cout << endl;
        }

        if (ent == 2) {
            all = n;
            iter = 0;
            for (int i = 0; i < n; i++)
            {
                if ((ss[i] == " ") || (ss[i] == "DEL"))
                {
                    all--;;
                }
            }
            if (all == n) cout << "Все ячейки заняты, не получится добавить элемент" << endl;
            else {
                cout << "Введите ключ: ";
                while (!(cin >> add) || (check(add) != 0))
                {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Ошибка, неправильный формат: " << endl << "Введите элемент для нахождения в формате 000А00: ";
                }
                blunder(ss, add);
                if (iter == 25) cout << "Увы, элемент не удалось записать, мы сделали много итераций, но что-то не получилось" << endl;
                else {
                    cout << "Мы записали ваш элемент" << endl;
                    cout << "Номер вашего элемента "<<itern << endl;
                }
            }
            cout << endl;
        }

        if (ent == 3) {
            for (int i = 0; i < n; i++)
            {
                cout << "Номер: " << i << " Ключ: ";
                if (ss[i] != "DEL")
                    cout << ss[i] << endl;
                else cout << endl;
            }
            cout << endl;
        }

        if (ent == 4) {
            cout << "Введите элемент, который хотите найти. Для этого введите ключ" << endl;
            while (!(cin >> key) || (check(key)!=0))
            {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Ошибка, неправильный формат: " << endl << "Введите элемент для нахождения в формате 000А00: ";
            }
            find_result = find(ss, key);
            if (find_result == -1) cout << "Элемент не найден:" << endl;
            else{ 
                cout<<"Элемент найден:"<< find_result << " И он действительно равен: " << ss[find_result] << endl;
                cout << "Введите 0, если хотите удалить" << endl;
                cin >> x;
                if (x == 0) {
                    find_col(ss, ss[find_result]);
                    deletik(ss, find_result);
                    cout << "Элемент удалён";
                }
                else cout << "Хорошо, элемент удалён не будет" << endl;
                cout << endl;
            }
        }

        if (ent == 5) {
            cout << "Файл сохранён" << endl;
            ofstream fout("out.txt");
                for (int i = 0; i < n; i++)
                {
                    fout << i << " " << table[i] << endl;
                }
                fout.close();
                cout << endl;
        }
        if(ent==0)
        {
            cout << "Спасибо, что воспользовались данной программой, с вами приятно иметь дело" << endl;
        }
    }
    delete[]ss;
}