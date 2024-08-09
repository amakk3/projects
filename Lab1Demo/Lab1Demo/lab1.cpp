#include <iostream>
#include <string>
using namespace std;

int doSomething(){

   string inputString;
   string wordOne;
   string wordTwo;
   string comma = ",";
   int commaLoc = 0;
   unsigned int i = 0;
   
   while (inputString != "q") {
      cout << "Enter input string:" << endl;
      getline(cin, inputString);
      
      while (inputString.find(comma) == string::npos && inputString != "q") {
         cout << "Error: No comma in string." << endl << endl;
         cout << "Enter input string:" << endl;
         getline(cin, inputString);
      }
      
      if (inputString == "q") {
         return 1;
      }

      commaLoc = inputString.find(comma);
      wordOne = inputString.substr(0, commaLoc);
      wordTwo = inputString.substr(commaLoc + 1);
      
      cout << "First word: ";
      for (i = 0; i < wordOne.size(); ++i) {
         if (!isspace(wordOne.at(i))) {
            cout << wordOne.at(i);
         }
      }
      cout << endl;
      
      cout << "Second word: ";
      for (i = 0; i < wordTwo.size(); ++i) {
         if (!isspace(wordTwo.at(i))) {
            cout << wordTwo.at(i);
         }
      }
      cout << endl << endl;
   }
  
   return 0;

}
int main() {
   doSomething();
}
