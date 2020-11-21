#include "lib.h"

//Проверка на 'Ё'
bool CheckYo(char a, char b){
    if (((int)a == int(char(208))) && ((int)b == int(char(129))))
        return true;
    else return false;
}

//Проверка на кирилицу
bool isCirilic(char a, char b){
    if ((((int)a == int(char(208))) && ((int)b >= int(char(144))) && ((int)b <= int(char(191)))) ||
        (((int)a == int(char(209))) && (((int)b >= int(char(128))) && ((int)b <= int(char(143))))) ||
        ((CheckYo(a, b)) || //Ё
         ((int)a == int(char(209))) && ((int)b == int(char(145)))))     //ё
        return true;
    else false;
}

//Проверка на заглавную букву
bool CapitalWord(char a, char b){
    if ((CheckYo(a, b)) ||
        (((int)a == (char)208) && ((int)b >= (char)144) && ((int)b <= (char)175)))
        return true;
    else return false;
}

//Преобразование строчной латинской буквы в заглавную
char UpperWord(char a){
    return a - 32;
}

//Проверка на длину выходного символа
bool isCount(int a){
    if ((a == 6) || ((a >= 22) && (a <= 25)) || ((a >= 30) && (a <= 31)) || (a == 33))
        return true;
    else return false;
}

//Получение выходного сообщения
char* getTranslitedText(char* message, int* Count){
    //кодировка
    char translit[][4]{
            "a",  //а
            "b",  //б
            "v",  //в
            "g",  //г
            "d",  //д
            "e",  //е
            "zh", //ж
            "z",  //з
            "i",  //и
            "j",  //й
            "k",  //к
            "l",  //л
            "m",  //м
            "n",  //н
            "o",  //о
            "p",  //п
            "r",  //р
            "s",  //с
            "t",  //т
            "u",  //у
            "f",  //ф
            "h",  //х
            "ts", //ц
            "ch", //ч
            "sh", //ш
            "sc",//щ
            "",   //ъ
            "i",  //ы
            "",   //ь
            "e",  //э
            "yu", //ю
            "ya",  //я
            "",    //пустой символ(костыль для 'ё')
            "yo" //ё
    };

    int count = *Count;
    int i = 0;
    int j = 0;
    int countTranslit;
    while (message[i] != '\0'){
        j = i + 1;
        //A..Z a..z 1234567890 .!?*%;@^:()-+=<>
        if ((message[i] >= (char)0) && (message[i] <= (char)127)) {
            message[count] = message[i];
            i += 1;
            count += 1;
        }
        else {
            //кирилица
            if (isCirilic(message[i], message[j])) {
                if (!(CapitalWord(message[i], message[j]))){
                    if (int(message[j]) >= int(char(176))) {
                        if (isCount(int(message[j]) - int(char(176)))) {
                            countTranslit = 2;
                        } else
                            countTranslit = 1;
                            for (int k = 0; k < countTranslit; ++k) {
                                message[count] = translit[int(message[j]) - int(char(176))][k];
                                count += 1;
                            }
                    } else {
                        if (isCount(int(message[j]) - int(char(128)) + 16)) {
                            countTranslit = 2;
                        } else
                            countTranslit = 1;
                        for (int k = 0; k < countTranslit; ++k) {
                            message[count] = translit[int(message[j]) - int(char(128)) + 16][k];
                            count += 1;
                        }
                    }
                    i += 2;
                }
                else {
                    //запись Ё заглавное
                    if (CheckYo(message[i], message[j])) {
                        message[count] = UpperWord(translit[33][0]);
                        count += 1;
                        message[count] = translit[33][1];
                        count += 1;
                        i += 2;
                        //запись остальных заглавных букв
                    } else {
                        message[count] = UpperWord(*translit[int(message[j]) - int(char(144))]);
                        count += 1;
                        i +=2;
                        if (isCount(int(message[j]) - int(char(144)))) {
                            message[count] = translit[int(message[j]) - int(char(144))][1];
                            count += 1;
                        }
                    }
                }
            }
        }
    }
    //запись в новый char*
    char* new_message = new char[count];
    for (int k = 0; k < count; ++k){
        new_message[k] = message[k];
    }
    new_message[count] = '\0';
    *Count = count;
    return new_message;
}