#include "parameter_reader.h"
#include "ID_Generation.h"
#include "Classes.h"
#include "GetData.h"
#include "SaveData.h"
#include "CommandHandler.h"
#include "Sorter.h"

int main(int argc, char** argv)
{
    GetData();
    Sort();
    stringstream arguments = make_string_stream(argc, argv);
    HandleCommand(arguments);
    SaveData();

    return 0;
}