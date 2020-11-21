#include "gtest/gtest.h"
#include "lib.h"

TEST(getTranslitedText, noChangesExpected) {
int count = 0;
char message[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 .!?*%;@^:()-+=<>";
char expected[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 .!?*%;@^:()-+=<>";
char* result = getTranslitedText(message, &count);
ASSERT_STREQ(expected, result);
delete [] result;
}

TEST(getTranslitedText, lowerLettersTransliterationExpected) {
int count = 0;
char message[1000] = "а б в г д е ё ж з и й к л м н о п р с т у ф х ц ч ш щ ы э ю я";
char expected[1000] = "a b v g d e yo zh z i j k l m n o p r s t u f h ts ch sh sc i e yu ya";
char* result = getTranslitedText(message, &count);
ASSERT_STREQ(expected, result);
delete [] result;
}

TEST(getTranslitedText, higherLettersTransliterationExpected) {
int count = 0;
char message[] = "А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ы Э Ю Я";
char expected[] = "A B V G D E Yo Zh Z I J K L M N O P R S T U F H Ts Ch Sh Sc I E Yu Ya";
char* result = getTranslitedText(message, &count);
ASSERT_STREQ(expected, result);
delete [] result;
}


TEST(getTranslitedText, noTransliterationExpected) {
    int count = 0;
char message[] = "ьъЬЪ";
char expected[] = "";
char* result = getTranslitedText(message, &count);
ASSERT_STREQ(expected, result);
delete [] result;
}


TEST(getTranslitedText, clippedTransliterationExpected) {
int count = 0;
char message[] = "Привет!";
char expected[] = "Privet!";
char* result = getTranslitedText(message, &count);
ASSERT_STREQ(expected, result);
delete [] result;
}

TEST(getTranslitedText, correctTransliterationExpected) {
int count = 0;
char message[] = "Съешь ещё этих мягких французских булок да выпей чаю!";
char expected[] = "S esh  escyo etih myagkih frantsuzskih bulok da vipej chayu!";
//ъ,ь
expected[1] = '\000';
expected[5] = '\000';
char* result = getTranslitedText(message, &count);
//ASSERT_STREQ сравнивает до '\000' поэтому пришлось написать свою проверку
    for (int i = 0; i <= count; ++i) {
        if (expected[i] != result[i])
            FAIL();
    }
    SUCCEED();
delete [] result;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

