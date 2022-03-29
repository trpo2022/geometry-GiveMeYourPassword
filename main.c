#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

string toCorrect(string str);
int isCircle(string str);
int checkErrors(string str);

int main() {
   string filename;
   cout << "Input file name: ";
   cin >> filename;
   fstream in(filename, ios::in);

   if (!in.good()) {
      cout << "Couldn't open file.\n";
      exit(1);
   }

   string buffer;
   while (getline(in, buffer)) {
      buffer = toCorrect(buffer);
      if (!buffer.empty() && checkErrors(buffer)) {
          cout << buffer << endl;
      }
   }

   in.close();
   return 0;
}

string toCorrect(string str) {
   while (isspace(str[0]))
      str.erase(0,1);
   while (str.find("  ", 0) != -1)
      str.replace(str.find("  ", 0), 2, " ");
   while (isspace(str[str.size() - 1]))
      str.erase(str.size() - 1,1);

   for (int i = 0; i < str.size(); i++)
      str[i] = tolower(str[i]);
   
   return str;
}

int isCircle(string str) {
   return (str.find("circle") == 0 && !isalpha(str[6])) ? 1 : 0;
}

int checkErrors(string str) {
   if (!isCircle(str)) {
      cout << str << endl;
      cout << "^" << endl << "Error at column 0: " <<
            "expected 'circle'" << endl << endl;
      return 0;
   }

   if (str.find(")", 0) == -1) {
      cout << str << endl;
      for (int i = 0; i < str.size() - 1; i++)
         cout << " ";
      cout << "^" << endl << "Error at column " << str.size() - 1 <<
            ": expected ')'" << endl << endl;
      return 0;
   }

   if (str[str.size() - 1] != ')') {
      cout << str << endl;
      for (int i = 0; i <= str.find(")") + 1; i++)
         cout << " ";
      cout << "^" << endl << "Error at column " << str.find(")") + 2 <<
            ": unexpected token" << endl << endl;
      return 0;
   }

   for (int i = str.find("(") + 1; i < str.find(")"); i++)
      if (!isdigit(str[i]) && str[i] != '.' && str[i] != ',' && str[i] != ' ' && str[i] != '-') {
         cout << str << endl;
         for (int j = 0; j < i; j++)
            cout << " ";
         cout << "^" << endl << "Error at column " << i <<
               ": expected '<double>'" << endl << endl;
         return 0;
      }

   return 1;
}