#include <string>
#include <iostream>
#include "flag.h"
using namespace std;
int main(){
    
   string one = "-u \"bob the builder\"";
   Flag args(one);
   string toPrint;
   args.getAsString((string)"u",toPrint,(string)"didnt get it");

   cout << "DEBUG: " << toPrint << endl;
    
    
    
    
    
return 0;    
}
