#include "Extras.h"

Extras::Extras()
{
    //ctor
}

Extras::~Extras()
{
    //dtor
}

void Extras::Display(){//handles the display of the first screen
    system("cls");
    fflush(stdin);
    cout << "What services can we help you with: " << endl;
    cout << "1. Go to your profile" << endl;
    cout << "2. Perform a transaction" << endl;
    cout << "3. Exit application" << endl;

    int option = man.intRestrictor();
    if(option>0 & option<4){
        if(option == 1){
            person.run();
        }else if(option == 2){
            operate.run();
        }else if(option == 3){
            exit(1);
        }
        Decide();
    }else{
        cout << "Wrong option, please select again" << endl;
        Display();
    }
}

void Extras::Decide(){//decide the users input of exiting or continuing using the app
    system("cls");
    char decision;
    cout << "Do want to do another transaction(y/n): ";
    cin >> decision;
    if(decision == 'y' | decision == 'n'){
        if(decision == 'y'){
            Display();
        }else{
            system("cls");
            cout << "\n\t\t\tGoodbye and thanks for banking with us" << endl;
            exit(1);
        }
    }else{
        cout << "Wrong input" << endl;
        return Decide();
    }
}
