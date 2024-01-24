#pragma once
#include "std_lib_inc.h"

class tag {
public:
    int TagID;
    string name;
};

class author {
public:
    int authorID;
    string vorname;
    string nachname;
};

class book {
public:
    string titel;
    string ISBN;
    int authorID;
    int bookID;
    vector<int> tags;
};

class user {
public:
    int userID;
    string vorname;
    string nachname;
};

class leiheintrag {
public:
    int userID;
    int bookID;
};

extern vector<user> userList;
extern vector<author> authorList;
extern vector<tag> tagList;
extern vector<book> bookList;
extern vector<leiheintrag> ausleihListe;

//Constants für ID_Genearation und Aufruf von Funktionen
extern const string kBook;
extern const string kTag;
extern const string kAuthor;
extern const string kUser;