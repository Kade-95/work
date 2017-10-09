#include "header.h"
#include "Extras.h"

Extras extra;

void start(){
    cout << "\n\t\t\t   Welcome to Our Bank" << endl;
    for(;;){
        extra.Display();//display on the screen
    }
}
int main(){
    start();
    return 0;
}

