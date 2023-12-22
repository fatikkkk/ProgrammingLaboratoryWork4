#include <iostream>
#include <fstream>

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

void changeRegister(char* input) {
    for (int i = 0; i < countWord * countSymbol; i++)
    {
        if (input[i] != 0)
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
                input[i] += 32;
        }
    }

    if (input[0] >= 'a' && input[0] <= 'z')
        input[0] -= 32;
}

void displayOnlyNumber(char* word) {
    int count = 0;
    if (word[0] != 0)
    {
        for (int j = 0; j < 10; j++)
            if (word[j] >= '0' && word[j] <= '9')
                count++;

        if (count == strlen(word))
            cout << word << "\n";
    }
}

void displayOnlySymbol(char* word) {
    int count = 0;
    if (word[0] != 0)
    {
        for (int j = 0; j < 10; j++)
            if (word[j] >= 'A' && word[j] <= 'z')
                count++;

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
    char str[countWord * countSymbol];
    char str1[countWord * countSymbol];
    char outputText[countWord * countSymbol] = { 0 };
    
    char substring[countSymbol];
    
    int valueMin = 0, valueMax = 0, count = 0, difference = 0;
    char supportWord[countSymbol] = { 0 };
    ifstream fs("textfile.txt");
    
    int selectReadUser, chooseUser;

    cout << "Please, select a text input method:\n";
    cout << "\t1 - from the keyboard\n";
    cout << "\t2 - from the file txt\n";

    cin >> selectReadUser;
    switch (selectReadUser)
    {
    case 1:
        cin.ignore();
        cout << "You select write from the keyboard. Please, type text here for work with it: \n";
        cin.getline(str, countWord * countSymbol);

        break;

    case 2:
        cout << "You selected open and read file and write text to char array\n";

        if (fs.is_open())
        {
            cout << "This is OK\n";
            fs.getline(str, countWord * countSymbol, '.');
        }
        else
            cout << "This is not OK\n";

        break;
    default:
        break;
    }


    cout << "Contains text:\n";
    cout << str << "\n";

    

    
    
    removePunctuation(str, outputText);
    cout << "After removing extra characters: \n";
    cout << outputText << "\n"; 
    
    
    
    changeRegister(outputText);
    cout << "After correct register: \n";
    cout << outputText << "\n";

    // Add in array words
    for (int i = 0; i < 500; i++)
    {
        if (outputText[i] == ' ' || outputText[i] == '.' || outputText[i] == ',' || outputText[i] == ':' || outputText[i] == '"') {
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

    bool isLive = true;
    while (isLive)
    {
        cout << "Please, choose a number for char Array:\n";
        cout << "\t 1 - Display all words containing only letters, then only numbers and then borh letters and numbers\n";
        cout << "\t 2 - Display all words with moving all number to the end\n";
        cout << "\t 3 - Linear search\n";
        cout << "\t 4 - KMP search\n";
        cout << "Number: ";
        cin >> chooseUser;

        switch (chooseUser)
        {
        case 1:
            cout << "\n=========Only Number========\n";
            for (int i = 0; i < countWord; i++)
                displayOnlyNumber(words[i]);

            cout << "\n=========Only Symbol========\n";
            for (int i = 0; i < countWord; i++)
                displayOnlySymbol(words[i]);

            cout << "\n========= Mixed ========\n";
            for (int i = 0; i < countWord; i++)
                displayMixed(words[i]);
            
            cout << "\n";
            break;

        case 2:
            for (int i = 0; i < countWord; i++)
                if (words[i][0] != 0)
                    moveNumber(words[i]);

            cout << "\nDisplay all words with number moving to the end!\n";
            for (int i = 0; i < countWord; i++)
                printArray(words[i], countSymbol);

            cout << "\n";
            break;

        case 3:
            cout << "Please, type pattern (substring) for Linear searching less 10 symbols: \n";
            cin.ignore();
            cin.getline(substring, countSymbol);
            linearSearch(outputText, substring);
            cout << "\n";
            break;
        case 4:
            cout << "Please, type pattern (substring) for KMP searching less 10 symbols: \n";
            cin.ignore();
            cin.getline(substring, countSymbol);
            kmpSearch(outputText, substring);
            cout << "\n";
            break;

        default:
            break;
        }

    }
    

    


    

}
