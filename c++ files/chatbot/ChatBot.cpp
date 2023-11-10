#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <time.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main()
{
    unordered_map<string,string> memory;
    string user_input;

    transform(user_input.begin(), user_input.end(), user_input.begin(),::tolower);

    cout << "Welcome User, I am ChatBot\n";
    system("color 4A");

    //our char functions
    while(true)
    {
        //getting user input
        getline(cin,user_input);

        transform(user_input.begin(), user_input.end(), user_input.begin(),::tolower);

        if(user_input == "hi" || user_input == "hello" || user_input=="hey"){
            string phrase = "Hello user how can i help you ?";
            string command = "espeak \"" + phrase + "\"";
            const char *charCommand = command.c_str();
            system(charCommand);
            cout << "Hello user how can i help you ?\n";
        }
        else if(user_input == "how are you" || user_input == "are you ok"){
            string phrase = "As a ChatBot i have no emotional states";
            string command = "espeak \"" + phrase + "\"";
            const char *charCommand = command.c_str();
            system(charCommand);
            cout << "As a ChatBot i have no emotional states\n";
        }
        else if(user_input == "what's my name" || user_input == "do you know my name" || user_input == "do you know my name?" || user_input == "do you know me" || user_input == "who am i"){
            if(memory.find("name") != memory.end()){
                cout << "Your name is " << memory["name"] << "\n";

            }
            else{
                cout << "Sorry you didn't tell me your name yet. Tell me your name\nWrite your name as : my name is[name]\n";
            }
        }
        else if(user_input.find("my name is") != string::npos){
            size_t pos = user_input.find("my name is");
            string name = user_input.substr(pos+11);
            memory["name"] = name;
            string phrase = "Nice to meet you";
            string command = "espeak \"" + phrase + "\"";
            const char *charCommand = command.c_str();
            system(charCommand);

            cout << "Nice to meet you " << name << "\n";
        }
        else if(user_input == "bye" || user_input == "see you later" || user_input == "later"){
            cout << "Bye";
            break;
        }
        else if(user_input == "clear the screen" || user_input == "clear" || user_input == "cls"){
            system("cls");
        }
        else if(user_input == "date" || user_input == "what's the date" || user_input == "what is the day today" || user_input == "what is the date" || user_input == "what is today")
        {
            struct tm* ptr;
            time_t t;
            t = time(NULL);
            ptr = localtime(&t);
            printf("%s", asctime(ptr));
        }
        else if(user_input == "local time" || user_input == "time" || user_input == "time?")
        {
            time_t rawtime;
            struct tm* timeinfo;

            // Used to store the time
            // returned by localetime() function
            char buffer[80];

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buffer, 80,"Time is %I:%M%p.",timeinfo);

            // strftime() function stores the
            // current time as Hours : Minutes
            //%I %M and %p-> format specifier
            // of Hours minutes and am/pm respectively*/

            // prints the formatted time
            puts(buffer);
        }
        else if(user_input == "open google" || user_input == "google" || user_input == "web" || user_input == "open web")
        {
            cout << "Opening Google. Please wait\n";
            string phrase = "opening Google. Please wait";
            string command = "espeak \"" + phrase + "\"";
            const char *charCommand = command.c_str();
            system(charCommand);
            char url[100] = "www.google.com";
            ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
        }
        else if(user_input == "close web" || user_input == "close google" || user_input == "please close google" || user_input == "please close web")
        {
            cout << "Closing Google\n";
            system("TASKKILL /IM chrome.exe /F");
            string phrase = "Closing Google";
            string command = "espeak \"" + phrase + "\"";
            const char *charCommand = command.c_str();
            system(charCommand);


        }
        else{
            cout << "I didn't get that, sorry\n";
        }

    }
    return 0;
}
