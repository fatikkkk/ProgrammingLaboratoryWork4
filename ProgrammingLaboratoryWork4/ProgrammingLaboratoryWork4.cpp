#include <iostream>

using namespace std;
const int countWord = 50, countSymbol = 10;

void removePunctuation(char* input, char* output) {
    int inputIndex = 0, outputIndex = 0, counterDot = 0;
    while (input[inputIndex] != '\0')
    {
        output[outputIndex] = input[inputIndex];

        if (input[inputIndex] == ' ' || input[inputIndex] == ',' || input[inputIndex] == ':' || input[inputIndex] == '"')
        {
            while (input[inputIndex + 1] == ' ' || input[inputIndex + 1] == ',' || input[inputIndex + 1] == ':' || input[inputIndex + 1] == '"')
                inputIndex++;
        }

        /*else if (input[inputIndex] == '.')
        {
            if (input[inputIndex + 1] == '.' && input[inputIndex + 2] == '.')
            {
                return;
            }
            else
                while (input[inputIndex + 1] == ' ' || input[inputIndex + 1] == ',' || input[inputIndex + 1] == ':' || input[inputIndex + 1] == '"')
                    inputIndex++;
        }*/
        outputIndex++;
        inputIndex++;
    }
    output[outputIndex] = '\0';
}

void removeSpaces(char* input, char* output) {
    int inputIndex = 0, outputIndex = 0;
    while (input[inputIndex] != '\0')
    {
        output[outputIndex] = input[inputIndex];

        if (input[inputIndex] == ' ')
        {
            while (input[inputIndex + 1] == ' ')
                inputIndex++;
        }
        outputIndex++;
        inputIndex++;
    }
    output[outputIndex] = '\0';
}

void changeRegister(char* input, char* output) {
    //int inputIndex = 0, outputIndex = 0;

    for (int i = 0; i < 500; i++)
    {
        if (i == 0)
            toupper(input[i]);
        else
            tolower(input[i]);
    }

    //output[outputIndex] = '\0';
}

//void filLWords(char* input, char* words[]) {
//    int valueMin = 0, valueMax = 0, count = 0, difference = 0;
//    char supportWord[10] = { 0 };
//    for (int i = 0; i < 500; i++)
//    {
//        if (input[i] == 32 || input[i] == 46) {
//
//            valueMax = i;
//            difference = valueMax - valueMin;
//            if (difference > 10) cout << "Error\n";
//            else {
//                for (int j = 0; j < difference; j++)
//                {
//                    if (valueMin < valueMax)
//                    {
//                        supportWord[j] = input[valueMin];
//                        //cout << supportWord[j] << " " << str[valueMin] << "\n";
//                        valueMin++;
//                    }
//                }
//            }
//            valueMin++;
//
//            //for (int j = 0; j < countSymbol; j++)
//            //{
//            //    cout << supportWord[j] << " ";
//            //}
//
//            for (int j = 0; j <= difference; j++)
//            {
//                words[count][j] = supportWord[j];
//            }
//            cout << "\n";
//            cout << words[count];
//            for (int j = 0; j < countSymbol; j++)
//            {
//                supportWord[j] = 0;
//            }
//            count++;
//        }
//    }
//
//}

void displayOnlyNumber(char* word) {
    int count = 0;
    if (word[0] != 0)
    {
        for (int j = 0; j < 10; j++)
        {
            if (word[j] >= '0' && word[j] <= '9')
                count++;
        }
        if (count == strlen(word))
            cout << word << "\n";
    }
}

void displayOnlySymbol(char* word) {
    int count = 0;
    if (word[0] != 0)
    {
        for (int j = 0; j < 10; j++)
        {
            if (word[j] >= 'A' && word[j] <= 'z')
                count++;
        }
        if (count == strlen(word))
            cout << word << "\n";
    }
}

void displayMixed(char* word) {
    int count = 0;
    bool isSymbol = false, isNumber = false;
    if (word[0] != 0)
    {
        for (int j = 0; j < 10; j++)
        {
            if (word[j] >= 'A' && word[j] < 'z')
            {
                count++;
                isSymbol = true;
            }

            else if (word[j] >= '0' && word[j] <= '9')
            {
                count++;
                isNumber = true;
            }
        }
        if (count == strlen(word) && isSymbol && isNumber)
            cout << word << "\n";
    }
}

void moveNumber(char* word) {
    char result[countSymbol] = { 0 };
    int j = 0;
    for (int i = 0; i < countSymbol; i++)
        if (word[i] < '0' || word[i] > '9')
            result[j++] = word[i];

    if (j == countSymbol || j == 0)
        return;

    for (int i = 0; i < countSymbol; i++)
        if (word[i] >= '0' && word[i] <= '9')
            result[j++] = word[i];

    memcpy(word, result, sizeof(result));
}

void linearSearch(char* text, char* pattern) {
    int sizeText = strlen(text);
    int sizePat = strlen(pattern);

    for (int i = 0; i <= sizeText - sizePat; i++)
    {
        int j;
        for (j = 0; j < sizePat; j++)
            if (text[i + j] != pattern[j])
                break;

        if (j == sizePat)
            cout << "Pattern found at Index " << i << "\n";
    }
}

void calcLongSuffix(char* pattern, int sizePattern, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < sizePattern)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpSearch(char* text, char* pattern) {
    int sizeText = strlen(text);
    int sizePat = strlen(pattern);

    int* longSuffix = new int[sizePat];
    calcLongSuffix(pattern, sizePat, longSuffix);

    int i = 0;
    int j = 0;
    while (i < sizeText)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }

        if (j == sizePat)
        {
            cout << "Pattern found at Index " << i - j << "\n";
            j = longSuffix[j - 1];
        }
        else if (i < sizeText && pattern[j] != text[i])
        {
            if (j != 0)
                j = longSuffix[j - 1];
            else
                i++;
        }
    }


}

void printArray(char* input, int size) {
    if (input[0] != 0)
    {
        for (int i = 0; i < size; i++)
            cout << input[i];
        cout << "\n";
    }
}


int main()
{

    char words[countWord][countSymbol] = { 0 };

    char str[500];

    char outputText[500] = { 0 };

    int valueMin = 0, valueMax = 0, count = 0, difference = 0;

    char supportWord[10] = { 0 };

    cin.getline(str, 500);

    removeSpaces(str, outputText);
    cout << outputText << "\n";

    for (int i = 0; i < 500; i++)
    {
        if (outputText[i] == ' ' || outputText[i] == '.') {
            valueMax = i;
            difference = valueMax - valueMin;
            if (difference > 10) cout << "Error\n";
            else {
                for (int j = 0; j < difference; j++)
                {
                    if (valueMin < valueMax)
                    {
                        supportWord[j] = outputText[valueMin];
                        //cout << supportWord[j] << " " << str[valueMin] << "\n";
                        valueMin++;
                    }
                }
            }
            valueMin++;

            //for (int j = 0; j < countSymbol; j++)
            //{
            //    cout << supportWord[j] << " ";
            //}

            for (int j = 0; j <= difference; j++)
            {
                words[count][j] = supportWord[j];
            }
            count++;
            //cout << words[count];
            for (int j = 0; j < countSymbol; j++)
            {
                supportWord[j] = 0;
            }
        }
    }
    
    cout << "\n=========Only Number========\n";

    for (int i = 0; i < countWord; i++)
    {
        displayOnlyNumber(words[i]);
    }

    cout << "\n=========Only Symbol========\n";
    for (int i = 0; i < countWord; i++)
    {
        displayOnlySymbol(words[i]);
    }

    cout << "\n========= Mixed ========\n";
    for (int i = 0; i < countWord; i++)
    {
        displayMixed(words[i]);
    }

    //for (int i = 0; i < countWord; i++)
    //{
    //    if (words[i][0] != 0)
    //    {
    //        moveNumber(words[i], countSymbol);
    //    }
    //}

    char someText[] = "hello";
    linearSearch(outputText, someText);
    cout << "\n";
    kmpSearch(outputText, someText);

    for (int i = 0; i < countWord; i++)
    {
        if (words[i][0] != 0)
            moveNumber(words[i]);
    }

    cout << "\n";
    for (int i = 0; i < countWord; i++)
    {
        printArray(words[i], countSymbol);
    }

}
