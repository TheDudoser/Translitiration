#include <iostream>
#include "lib.h"

using namespace std;

int main() {
int count = 0;
char* message = new char[1000];
cout << "Введите сообщение на русском языке" << endl;
cin.getline(message, 1000);
message = getTranslitedText(message, &count);

    for (int k = 0; k < count; ++k) {
        cout << message[k];
    }
     delete[] message;

    return 0;
}
