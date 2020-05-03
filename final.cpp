#include <Windows.h>
#include <algorithm>
#include <climits>
#include <conio.h>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
int tnt[100];
int total = 0, modified_total = 0;
class order
{
public:
    char name[30], size[30], category[30], subcat[30], buffer[150], ordNo[5],
        price1[5], qunt[5];

    int orderno = 0, quantity, price;
} o;

// Create a hash table of size 5 rows representing 5 orders and 7 fields.
vector<vector<string>> hashTable;

/*The hash function takes in the User name as it's argument and computes the
index as the summation of product of the ASCII value of the characters in the ID
and the position at which the character is present in the string.*/

int hashFunc(char *ordNo)
{
    int sum = 0, index;
    for (int i = 0; i < strlen(ordNo); i++)
        sum += ((int)ordNo[i] * (i + 1));
    index = sum % 48;
    return index;
}

void openfile(fstream &file, const char *filename, ios_base::openmode mode)
{
    file.open(filename, mode);
    if (!file.is_open())
    {
        cout << "Unable to open the file" << '\n';
        exit(1);
    }
}

// The unpack function is used to read records from the file and store them
// dynamically in the hash table.
void unpack()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            hashTable[i][j] = "-";
        }
    }
    fstream f3, f4;
    int index, i, j;
    openfile(f3, "output.txt", ios::in);
    openfile(f4, "hashfile.txt", ios::out);
    while (!f3.eof())
    {
        f3.getline(o.name, 30, '|');
        f3.getline(o.ordNo, 5, '|');
        f3.getline(o.category, 30, '|');
        f3.getline(o.subcat, 30, '|');
        f3.getline(o.size, 30, '|');
        f3.getline(o.qunt, 5, '|');
        f3.getline(o.price1, 5, '\n');

        index = hashFunc(o.ordNo);

        // Linear Probing
        /*When the current index at which the record is to be stored is already
        occupied by another record, the collision algorithm computes the next
        available index location. If the index crosses 50, the search for an
        empty index is wrapped around to the start.*/
        while (hashTable[index][2] != o.ordNo && hashTable[index][1] != "-")
            index = (index + 1) % 5;

        hashTable[index][1] = o.name;
        hashTable[index][2] = o.ordNo;
        hashTable[index][3] = o.category;
        hashTable[index][4] = o.subcat;
        hashTable[index][5] = o.size;
        hashTable[index][6] = o.qunt;
        hashTable[index][7] = o.price1;
        if (strlen(o.name) == 0)
        {
            continue;
        }
        f4 << index << "|" << o.name << "|" << o.ordNo << "|" << o.category
           << "|" << o.subcat << "|" << o.size << "|" << o.qunt << "|"
           << o.price1 << "\n";
    }
    f3.close();
    f4.close();
    system(CLEAR);
}

void write(int x)
{
    system(CLEAR);
    fstream f1;
    openfile(f1, "output.txt", ios::app | ios::out);
    order o;

    cout << "Enter your name:";
    cin >> o.name;
    string ordNo = to_string(x);
    cout << "\nHello " << o.name << " \nwhat would you like to order?\n\n";
orderlist:
    cout << "-----------------------MENU----------------------\n\n";
    cout << "Pizza\n"
         << "Burgers\n"
         << "Sandwich\n";
    cout << "\nEnter your choice:";
    cin >> o.category;
    char p[] = "pizza";
    char b[] = "burger";
    char s[] = "sandwich";
    char s1[] = "small";
    char s2[] = "large";
    if (strcmp(o.category, p) == 0)
    {
        cout << "1)Margherita\n2)Deluxe_Veggie\n3)Veg_Extravaganza\n\n";
        cout << "Enter the choice: ";
        cin >> o.subcat;
        cout << "\n1) Small Rs.250\n"
             << "3) Large Rs.500\n";
        cout << "\n\nEnter the size:";
        cin >> o.size;
        if (strcmp(o.size, s1) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 150;
        }
        else if (strcmp(o.size, s2) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 300;
        }
        else
        {
            cout << "Please enter a valid option!\n\n";
            goto orderlist;
        }
    }
    else if (strcmp(o.category, b) == 0)
    {
        cout << "1)Veggie_burger\n2)Cheeseburger";
        cout << "\n\nEnter the choice: ";
        cin >> o.subcat;
        cout << "\n1) Small Rs.80\n"
             << "3) Large Rs.120\n";
        cout << "\n\nEnter the size:";
        cin >> o.size;
        if (strcmp(o.size, s1) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 60;
        }
        else if (strcmp(o.size, s2) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 120;
        }
        else
        {
            cout << "Please enter a valid order!\n\n";
            goto orderlist;
        }
    }
    else if (strcmp(o.category, s) == 0)
    {
        cout << "1)Cheese_Sandwich\n2)Grilled_Cheese_Sandwich\n3)Chicken_"
                "Sandwich";
        cout << "\n\nEnter the choice: ";
        cin >> o.subcat;
        cout << "\n1) Small Rs.80\n"
             << "3) Large Rs.120\n";
        cout << "\n\nEnter the size:";
        cin >> o.size;
        if (strcmp(o.size, s1) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 80;
        }
        else if (strcmp(o.size, s2) == 0)
        {
            cout << "\n\nEnter the quantity:";
            cin >> o.quantity;
            o.price = o.quantity * 120;
        }
        else
        {
            cout << "Please enter a valid !\n\n";
            goto orderlist;
        }
    }
    else
    {
        cout << "Please enter a valid option!\n\n";
        goto orderlist;
    }

    string q = to_string(o.quantity);
    string price1 = to_string(o.price);
    strcpy(o.buffer, o.name);
    strcat(o.buffer, "|");
    strcat(o.buffer, ordNo.c_str());
    strcat(o.buffer, "|");
    strcat(o.buffer, o.category);
    strcat(o.buffer, "|");
    strcat(o.buffer, o.subcat);
    strcat(o.buffer, "|");
    strcat(o.buffer, o.size);
    strcat(o.buffer, "|");
    strcat(o.buffer, q.c_str());
    strcat(o.buffer, "|");
    strcat(o.buffer, price1.c_str());
    strcat(o.buffer, "\n");
    f1 << o.buffer;
    f1.close();
    system(CLEAR);
    return;
}

void display()
{
    system(CLEAR);
    cout << "Your Orders are:";
    cout << "\n";
    for (int i = 1; i <= 5; i++)
    {
        // if (hashTable[i][1] == "-")
        // {
        //     continue;
        // }
        cout << "\n------------------------------------------------------------"
                "--------------------------------------------------------------"
                "-----------------------\n";
        cout << "\nIndex= " << i << "\n";
        cout << "\nCustomer Name= " << hashTable[i][1];
        cout << "\norder number= " << hashTable[i][2];
        cout << "\ncategory= " << hashTable[i][3];
        cout << "\nitem ordered= " << hashTable[i][4];
        cout << "\nSize= " << hashTable[i][5];
        cout << "\nquantity= " << hashTable[i][6];
        cout << "\nprice= " << hashTable[i][7];

        cout << "\n------------------------------------------------------------"
                "--------------------------------------------------------------"
                "-----------------------\n";
    }

    getch();
    return;
}
// Delete records by matching the orderno of the record to be deleted.
void deletion()
{
    system(CLEAR);
    fstream f7, f8;
    int flag = 0;
    char id[10];
    order obj1[50];
    int i = 0;
    openfile(f7, "output.txt", ios::in);
    cout << "Delete records\n";
    cout << "\nEnter the ID of the record you wish to delete: ";
    cin >> id;

    while (!f7.eof())
    {
        f7.getline(obj1[i].name, 30, '|');
        f7.getline(obj1[i].ordNo, 5, '|');
        f7.getline(obj1[i].category, 30, '|');
        f7.getline(obj1[i].subcat, 30, '|');
        f7.getline(obj1[i].size, 30, '|');
        f7.getline(obj1[i].qunt, 5, '|');
        f7.getline(obj1[i].price1, 5, '\n');

        if (strcmp(obj1[i].ordNo, id) == 0)
        {
            flag = 1;
            continue;
        }
        i++;
    }
    f7.close();

    if (flag == 1)
    {
        fstream out1;

        out1.open("output.txt", ios::out | ios::trunc);
        for (int j = 0; j < i - 1; j++)
        {
            out1 << obj1[j].name << "|" << obj1[j].ordNo << "|"
                 << obj1[j].category << "|" << obj1[j].subcat << "|"
                 << obj1[j].size << "|" << obj1[j].qunt << "|" << obj1[j].price1
                 << "\n";
        }
        out1.close();

        out1.open("hashfile.txt", ios::out | ios::trunc);
        for (int j = 0; j < i - 1; j++)
        {
            out1 << obj1[j].name << "|" << obj1[j].ordNo << "|"
                 << obj1[j].category << "|" << obj1[j].subcat << "|"
                 << obj1[j].size << "|" << obj1[j].qunt << "|" << obj1[j].price1
                 << "\n";
        }
        out1.close();
        cout << "Record Deleted";
    }
    else
    {

        cout << "Invalid order number";
    }

    getch();
    return;
}
int append_digits(int i1, int i2)
{
    int i2_copy = i2;
    while (i2_copy)
    {
        i1 *= 10;
        i2_copy /= 10;
    }
    return i1 + i2;
}
int totalprice()
{
    int t;
    fstream f3;
    int app = 0, sum = 0;
    int index, i, j;
    openfile(f3, "output.txt", ios::in);
    i = 0;
    while (!f3.eof())
    {
        f3.getline(o.name, 30, '|');
        f3.getline(o.ordNo, 5, '|');
        f3.getline(o.category, 30, '|');
        f3.getline(o.subcat, 30, '|');
        f3.getline(o.size, 30, '|');
        f3.getline(o.qunt, 5, '|');
        f3.getline(o.price1, 5, '\n');

        for (int k = 0; k < strlen(o.price1); k++)
        {
            if (o.price1[k] == '0')
            {
                app = app * 10;
            }
            else
            {
                app = append_digits(app, o.price1[k] - '0');
            }
        }

        sum = sum + app;
        app = 0;

        i++;
    }
    f3.close();
    return sum;
}
// Searching for records in the hash table by computing the index obtained by
// feeding the User ID as the input.
void search()
{
    system(CLEAR);
    char id[5];
    cout << "Search for orders";
    cout << "Enter the orderno you wish to search: ";
    cin >> id;
    int index = hashFunc(id);

    // Linear probing.
    while (hashTable[index][2] != id && hashTable[index][1] != "-")
        index = (index + 1) % 5;

    if (hashTable[index][1] != "-")
    {
        cout << "Record found." << endl;
        cout << "\n------------------------------------------------------------"
                "--------------------------------------------------------------"
                "-----------------------\n";
        cout << "\nCustomer Name= " << hashTable[index][1];
        cout << "\norder number= " << hashTable[index][2];
        cout << "\ncategory= " << hashTable[index][3];
        cout << "\nitem ordered= " << hashTable[index][4];
        cout << "\nSize= " << hashTable[index][5];
        cout << "\nquantity= " << hashTable[index][6];
        cout << "\nprice= " << hashTable[index][7];
        cout << "\n------------------------------------------------------------"
                "--------------------------------------------------------------"
                "-----------------------\n";
    }
    else
    {

        cout << "Record not found." << endl;
    }
    getch();
    return;
}

// Modify the contents of the record if present, by the orderNo as the
// parameter.
void modify()
{
    system(CLEAR);
    order obj[50];
    int pp[50];
    fstream f3, out1;
    char id[10];
    int i, j;
    openfile(f3, "output.txt", ios::in);
    cout << "\nModify your orders";
    cout << "\nEnter the orderno to be modified: ";
    cin >> id;
    int price = 0;
    int qt = 0;
    i = 0;
    char p[] = "pizza";
    char b[] = "burger";
    char s[] = "sandwich";
    char s1[] = "small";
    char s2[] = "large";
    while (!f3.eof())
    {
        f3.getline(obj[i].name, 30, '|');
        f3.getline(obj[i].ordNo, 5, '|');
        f3.getline(obj[i].category, 30, '|');
        f3.getline(obj[i].subcat, 30, '|');
        f3.getline(obj[i].size, 30, '|');
        f3.getline(obj[i].qunt, 5, '|');
        f3.getline(obj[i].price1, 5, '\n');
        i++;
    }
    for (j = 0; j < i; j++)
    {
        if (strcmp(id, obj[j].ordNo) == 0)
        {
            cout << "Record Found" << endl;
            cout << "\n--------------------------------------------------------"
                    "----------------------------------------------------------"
                    "-------------------------------\n";
            cout << "\n\nThe old values of the order with orderno " << id
                 << " are\n";
            cout << "\nCustomer name= " << obj[j].name;
            cout << "\norder number= " << obj[j].ordNo;
            cout << "\ncategory= " << obj[j].category;
            cout << "\nsub category= " << obj[j].subcat;
            cout << "\nsize= " << obj[j].size;
            cout << "\nQuantity= " << obj[j].qunt;
            cout << "\nPrice= " << obj[j].price1;
            cout << "\n--------------------------------------------------------"
                    "----------------------------------------------------------"
                    "-------------------------------\n";
        take:
            cout << "Enter new values for order with orderno " << id << "\n";
            cout << "\nsize= ";
            cin >> obj[j].size;
            cout << "\nQuantity= ";
            cin >> qt;
            *obj[j].qunt = char('0' + qt);
            if (strcmp(obj[j].category, p) == 0)
            {
                if (strcmp(obj[j].size, s1) == 0)
                {
                    price = qt * 150;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else if (strcmp(obj[j].size, s2) == 0)
                {
                    price = qt * 300;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else
                {
                    cout << "Size entered is invalid!!\n\n";
                    goto take;
                }
            }
            else if (strcmp(obj[j].category, b) == 0)
            {
                if (strcmp(obj[j].size, s1) == 0)
                {
                    price = qt * 60;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else if (strcmp(obj[j].size, s2) == 0)
                {
                    price = qt * 120;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else
                {
                    cout << "Size entered is invalid!!\n\n";
                    goto take;
                }
            }
            else
            {
                if (strcmp(obj[j].size, s1) == 0)
                {
                    price = qt * 80;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else if (strcmp(obj[j].size, s2) == 0)
                {
                    price = qt * 120;
                    string s = to_string(price);
                    char cstr[s.size() + 1];
                    for (int i = 0; i < s.size() + 1; i++)
                        cstr[i] = s[i];
                    cstr[s.size()] = '\0';
                    strcpy(obj[j].price1, cstr);
                }
                else
                {
                    cout << "Size entered is invalid!!\n\n";
                    goto take;
                }
            }

            break;
        }
    }
    if (j == i)
    {
        cout << "The order with orderno " << id << " is not present";
        goto la;
    }
    f3.close();
    out1.open("output.txt", ios::out | ios::trunc);
    for (j = 0; j < i; j++)
    {
        if (strlen(obj[j].name) == 0)
        {
            continue;
        }
        out1 << obj[j].name << "|" << obj[j].ordNo << "|" << obj[j].category
             << "|" << obj[j].subcat << "|" << obj[j].size << "|" << obj[j].qunt
             << "|" << obj[j].price1 << "\n";
    }
    out1.close();
la:
    cout << "\n\nPress Enter";
    getch();
    return;
}

int main()
{
    char ch;
    int choice, total = 0;
    hashTable.resize(6, vector<string>(8, "-"));

begin:
    for (;;)
    {
        system(CLEAR);
        cout << "-----------WELCOME TO VIVA FAST FOOD---------------\n\n";
        cout << "\n\n";
        cout << "1)PLACE ORDERS\n";
        cout << "2)MODIFY ORDERS\n";
        cout << "3)SEARCH ORDERS\n";
        cout << "4)DELETE ORDERS\n";
        cout << "5)DISPLAY ORDERS\n";
        cout << "6)CONFIRM ORDERS\n";
        cout << "\n\n Please enter your choice :";
        cin >> choice;
        int k;
        switch (choice)
        {

        case 1:
            o.orderno = o.orderno + 1;
            if (o.orderno > 5)
            {
                cout << "You cannot place more than 5 orders";
                for (int i = 0; i <= 10000000000; i++)
                    i++;
                goto begin;
            }
            system(CLEAR);
            write(o.orderno);
            break;
        case 2:
            modify();
            system(CLEAR);
            break;
        case 3:
            unpack();
            search();
            system(CLEAR);
            break;
        case 4:
            deletion();
            system(CLEAR);
            break;
        case 5:
            unpack();
            display();
            system(CLEAR);
            break;
        case 6:
            total = totalprice();
            cout << "\n\nConfirm order[Y/N]:";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << "\n\nTotal price= " << total << "\n\n";
                goto last;
            }
            else
            {
                goto begin;
            }
            break;
        }
    }
last:
    cout << "\n\nThankyou for ordering !!"
         << "\n your order will be deliverd in 10 minutes\n";

    return 0;
}
