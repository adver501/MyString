#include <cstring> 
#include <iostream>

using namespace std;

class Mystring {



    friend Mystring operator+( 
        const Mystring& lhs, 
        const Mystring& rhs);
    public:
        char* str;
        char* str_;
        char* temp;

        Mystring();

        // Constructor with 1 arguments 
        Mystring(char* val);

        // Copy Constructor 
        Mystring(Mystring& source);

        void concat(Mystring& str1, Mystring& str2);
        
        void findchar(Mystring& str1, char chr);

        void findstr(Mystring& str1, Mystring& str2);

        void replace(int pos, int len, Mystring& str1, Mystring& str2);

        Mystring& operator=( 
            const Mystring& rhs);
    //// Destructor 
    //~Mystring() { delete str; }
};



// with no arguments
Mystring::Mystring()
    : str{ nullptr }
{
    str = new char[1];
    str[0] = '\0';
}

// with one arguments 
Mystring::Mystring(char* val)
{
    if (val == nullptr) {
        str = new char[1];
        str[0] = '\0';
    }

    else {

        str = new char[strlen(val) + 1];

        //std::strcpy(str, val);
        str = val;

        cout << "The string passed is: " << str << endl;
    }
}

// Overloading assignment
Mystring& Mystring::operator=( 
    const Mystring& rhs) 
{ 
    if (this == &rhs) 
        return *this; 
    delete[] str; 
    str = new char[strlen(rhs.str) + 1]; 
    strcpy(str, rhs.str); 
    return *this; 
}

// Overloading + operator
Mystring operator+(const Mystring& lhs, 
                   const Mystring& rhs) 
{ 
    int length = strlen(lhs.str) 
                 + strlen(rhs.str); 
  
    char* buff = new char[length + 1]; 
  
    // Copy the strings to buff[] 
    strcpy(buff, lhs.str); 
    strcat(buff, rhs.str); 
  
    // String temp  |**| initialize and then print
    Mystring temp{ buff }; 
  
    // delete the buff[] 
    delete[] buff; 
  
    // Return the concatenated string 
    return temp; 
}

// Copy Constructor
Mystring::Mystring(Mystring& source)
{
    str = new char[strlen(source.str) + 1];
    //std::strcpy(str, source.str);
    str = source.str;
}

void Mystring::concat(Mystring& str1, Mystring& str2) {
    str = new char[strlen(str1.str)];
    str_ = new char[strlen(str2.str) + 1];

    str = str1.str;
    str_ = str2.str;
    temp = new char[strlen(str) + strlen(str_)];

    for (int i = 0; i < strlen(str); i++)
        temp[i] = str[i];
    for (int i = strlen(str); i < (strlen(str) + strlen(str_)); i++) {
        temp[i] = str_[i - strlen(str)];
        //cout << temp[i] << endl;
    }
    temp[strlen(temp)] = '\0';

    cout <<"Concat: "<< temp << endl;
    //cout << "size: "<< strlen(temp) << endl;

}

void Mystring::findchar(Mystring& str1, char chr) {
    str = new char[strlen(str1.str) + 1];
    str = str1.str;
    
    str[strlen(str)] = '\0';
    
    bool found = 0;
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == chr) {
            found = 1;
            break;
        }
    }
    if (found)
        cout << "Character found in: " << i << endl;
    if (!found)
        cout << "Character not found!" << endl;
}

void Mystring::findstr(Mystring& str1, Mystring& str2) {
    str = new char[strlen(str1.str) + 1];
    str_ = new char[strlen(str2.str) + 1];
    
    str = str1.str;
    str_ = str2.str;
    str[strlen(str)] = '\0';
    str_[strlen(str_)] = '\0';

    bool found = 0;
    int pos;
    for (int i = 0; i < strlen(str); i++) {
        if(str[i] == str_[0]) {
            for (int j = i+1; j < (strlen(str_) + i); j++) {
                    //cout << "Done! " << i << "j: " << j << endl;
                if (str[j] != str_[j-i]) {
                    break;
                }
                if ((j-i) == (strlen(str_) - 1)) {
                    found = 1;
                    pos = i;
                }
            }
        }
    }
    if (found)

        cout << "String found in: " << pos << endl;
    if (!found)
        cout << "String not found!" << endl;
    
}

void Mystring::replace(int pos, int len, Mystring& str1, Mystring& str2) {
    if (pos >= strlen(str1.str)) {
        cout << "Position out of bound!";
        return;
    }
    if (strlen(str2.str) - len > 0) {
        str = new char[strlen(str1.str) + 1 + strlen(str2.str) - len];
        temp = new char[strlen(str1.str) + 1 + strlen(str2.str) - len - (pos + len)];
    }
    else {
        str = new char[strlen(str1.str) + 1];
        temp = new char[strlen(str1.str) + 1 - (pos + len)];
    }

    str_ = new char[strlen(str2.str) + 1];
    
    str = str1.str;
    str_ = str2.str;

    for (int i = pos + len; i < strlen(str); i++)
    {
        temp[i - (pos + len)] = str[i];
    }
    for (int i = pos; i < (strlen(str_) + pos); i++) {
        str[i] = str_[i - pos];
    }
    for (int i = (strlen(str_) + pos); i < strlen(str); i++) {
        str[i] = temp[i - (pos + len)];
    }
    str[strlen(str)] = '\0';
    
    cout << "Replace: " << str << endl;
    //cout << "STR: " << str[21] << endl;

}


int main()
{
    // Constructor with no arguments
    Mystring a;

    Mystring r;


    // Convert string to char 
    char temp[] = "Hello World IRAN test test";
    char temp2[] = "IRAN";

    Mystring b{ temp };
    Mystring f{ temp2 };

    //r.concat(b, f);
    //r.replace(3, 4, b, f);
    r.findstr(b, f);
    r.findchar(b, 't');


    //copy
    Mystring c{ b };

    cout << "c is: "<< c.str << endl;

    Mystring d;
    d = b + b; 



}
