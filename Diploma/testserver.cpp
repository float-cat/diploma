#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "core/Asker/serverproto.hpp"

using namespace std;

int main()
{
    ServerProto Server(10001, 100);
    Server.MainProcess();
    
    return EXIT_SUCCESS;
}

