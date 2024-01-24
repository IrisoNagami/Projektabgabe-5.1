#pragma once
#include "ID_Generation.h"

extern vector<user> userList;
extern vector<author> authorList;
extern vector<tag> tagList;
extern vector<book> bookList;
extern vector<leiheintrag> ausleihListe;

extern const string kBook;
extern const string kTag;
extern const string kAuthor;
extern const string kUser;

void HandleCommand(stringstream& inputCommand);

bool ObjExists(string Klasse, int ID);

bool IsBorrowed(int ID);

void CMDlist(stringstream& inputCommand);

void CMDadd(stringstream& inputCommand);

void CMDdelete(stringstream& inputCommand);

void CMDshow(stringstream& inputCommmand);

void CMDborrow(stringstream& inputCommand);

void CMDreturn(stringstream& inputCommand);

void CMDstatus(stringstream& inputCommand);

void CMDsearch(stringstream& inputCommand);