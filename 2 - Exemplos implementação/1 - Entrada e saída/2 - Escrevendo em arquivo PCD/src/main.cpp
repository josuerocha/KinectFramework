///STANDARD INCLUDES
#include <iostream>
#include <string>

///CUSTOM INCLUDES
#include "IO.h"
#include "CustomStructures.h"

using namespace std;

int main(){
    IO<PXYZRGBA> io;
    XYZRGBACloud_ptr cloud(new XYZRGBACloud);

    string path;

    cout<<"Informe o caminho para o arquivo:" << endl;
    cin>>path;

    io.readFromPCD(path, cloud);

    string newPath = "Copy" + path;
    io.writeToPCD(newPath,cloud);

    return 0;
}
