#include "CommandHandler.h"
extern vector<user> userList;
extern vector<author> authorList;
extern vector<tag> tagList;
extern vector<book> bookList;
extern vector<leiheintrag> ausleihListe;

extern const string kBook;
extern const string kTag;
extern const string kAuthor;
extern const string kUser;

void HandleCommand(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "help")
	{
		cout << "->list [books/tags/authors/users] zeigt jeweils alle Objekte des Typs an\n";
		cout << "->add [book/author/tag/user] fügt jeweiliges Objekt hinzu\n";
		cout << "->delete [book/author/tag/user] löscht das jeweilige Objekt\n";
		cout << "->show [book/author/tag/user] zeigt IDs der Objekte in der Klasse an\n";
		cout << "->borrow [user] [book] leiht das Buch aus sofern es nicht schon ausgeliehen ist\n";
		cout << "->return [user] [book] gibt das Buch zurück, sofern der User dieses ausgeliehen hat\n";
		cout << "->status [book/user] gibt aus ob das Buch ausgeliehen ist oder welche Bücher vom User ausgeliehen werden\n";
		cout << "->search [author/tag] gibt IDs der Bücher mit demjeweiligen Tag/Autor zurück\n";
		return;
	}
	else if (temp == "list")
	{
		CMDlist(inputCommand);
		return;
	}
	else if (temp == "add")
	{
		CMDadd(inputCommand);
		return;
	}
	else if (temp == "delete")
	{
		CMDdelete(inputCommand);
		return;
	}
	else if (temp == "show")
	{
		CMDshow(inputCommand);
		return;
	}
	else if (temp == "borrow")
	{
		CMDborrow(inputCommand);
		return;
	}
	else if (temp == "return")
	{
		CMDreturn(inputCommand);
		return;
	}
	else if (temp == "status")
	{
		CMDstatus(inputCommand);
		return;
	}
	else if (temp == "search")
	{
		CMDsearch(inputCommand);
	}
	else
	{
		//101 Befehl ist unbekannt
		cout << "101 Befehl ist unbekannt\n";
		return;
	}
}

bool ObjExists(string Klasse, int ID)
{
	if (Klasse == kAuthor)
	{
		for (author a : authorList)
		{
			if (ID == a.authorID)
			{
				return true;
			}
		}
	}
	else if (Klasse == kBook)
	{
		for (book bk : bookList)
		{
			if (ID == bk.bookID)
			{
				return true;
			}
		}
	}
	else if (Klasse == kTag)
	{
		for (tag t : tagList)
		{
			if (t.TagID == ID)
			{
				return true;
			}
		}
	}
	else if (Klasse == kUser)
	{
		for (user u : userList)
		{
			if (u.userID == ID)
			{
				return true;
			}
		}
	}
	return false;
}

bool IsBorrowed(int ID)
{
	for (leiheintrag l : ausleihListe)
	{
		if (ID == l.bookID)
		{
			return true;
		}
	}
	return false;
}

void CMDlist(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "books")
	{
		for (book b : bookList)
		{
			cout << b.bookID << " " << b.authorID << " " << b.titel << " " << b.ISBN;
			for (int i : b.tags)
			{
				cout << " " << i;
			}
			cout << '\n';
		}
		return;
	}
	else if (temp == "authors")
	{
		for (author a : authorList)
		{
			cout << a.authorID << " " << a.vorname << " " << a.nachname << '\n';
		}
		return;
	}
	else if (temp == "tags")
	{
		for (tag t : tagList)
		{
			cout << t.TagID << " " << t.name << '\n';
		}
		return;
	}
	else if (temp == "users")
	{
		for (user u : userList)
		{
			cout << u.userID << " " << u.vorname << " " << u.nachname << '\n';
		}
		return;
	}
	else
	{
		//102 Kategorie konnte nicht gelesen werden
		cout << "102 Befehl ist bekannt, aber Kategorie ist unbekannt.\n";
		return;
	}
}

void CMDadd(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;

	if (temp == "author")
	{
		author tempAuthor;
		inputCommand >> tempAuthor.vorname >> tempAuthor.nachname;
		if (tempAuthor.vorname.empty() || tempAuthor.nachname.empty())
		{
			//106? Autor-Eintrag konnte nicht gelesen werden
			cout << "106 Autor Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//ID generieren und in Liste einfügen
		tempAuthor.authorID = idGeneration(kAuthor);
		authorList.push_back(tempAuthor);

		//100, hat funktioniert
		cout << "100 Befehl erfolgreich ausgeführt\n";
		return;
	}
	else if (temp == "user")
	{
		user tempUser;
		inputCommand >> tempUser.vorname >> tempUser.nachname;
		if (tempUser.vorname.empty() || tempUser.nachname.empty())
		{
			//105? User-Eintrag konnte nicht gelesen werden
			cout << "105 User Eintrag konnte nicht gelesen werden\n";
			return;
		}
		// ID generieren und in Liste einfügen
		tempUser.userID = idGeneration(kUser);
		userList.push_back(tempUser);

		//100, hat funktioniert
		cout << "100 Befehl erfolgreich ausgeführt\n";
		return;
	}
	else if (temp == "tag")
	{
		tag tempTag;
		inputCommand >> tempTag.name;
		if (tempTag.name.empty())
		{
			// 107? Tag-Eintrag konnte nicht gelesen werden
			cout << "107 Tag Eintrag konnte nicht gelesen werden\n";
			return;
		}
		//ID generieren und in Liste einfügen
		tempTag.TagID = idGeneration(kTag);
		tagList.push_back(tempTag);

		//100, hat funktioniert
		cout << "100 Befehl erfolgreich ausgeführt\n";
		return;
	}
	else if (temp == "book")
	{
		book tempBook;
		inputCommand >> temp;
		try
		{
			tempBook.authorID = stoi(temp);
		}
		catch (...)
		{
			cout << "106 Autor Eintrag konnte nicht gelesen werden\n";
		}
		//Falls der Autor nicht existiert
		if (!ObjExists(kAuthor, tempBook.authorID))
		{
			//106, Autor-Eintrag konnte nicht gelesen werden
			cout << "106 Autor Eintrag konnte nicht gelesen werden\n";
			return;
		}
		//Name startet mit %
		bool startsRight = false;
		//Name endet mit %
		bool endsRight = false;
		while (inputCommand >> temp)
		{
			if (temp.front() == '%')
			{
				startsRight = true;
				tempBook.titel = temp;
				if (temp.back() == '%')
				{
					break;
				}
			}
			else if (temp.back() == '%')
			{
				endsRight = true;
				tempBook.titel += " ";
				tempBook.titel += temp;
				break;
			}
			else
			{
				tempBook.titel += " ";
				tempBook.titel += temp;
			}
		}
		if (!startsRight || !endsRight)
		{
			//104 Bucheintrag konnte nicht gelesen werden
			cout << "104 Buch Eintrag konnte nicht gelesen werden\n";
			return;
		}
		try
		{
			inputCommand >> tempBook.ISBN;
		}
		catch (...)
		{
			// Es gibt keine Fehlermeldung für falsche ISBN Nummern
			return;
		}
		tag tempTag;
		while (inputCommand >> tempTag.TagID)
		{
			//Wenn der Tag nicht exisitiert
			if (!ObjExists(kTag, tempTag.TagID))
			{
				//107 Tag-Eintrag konnte nicht gelesen werden
				cout << "107 Tag Eintrag konnte nicht gelesen werden\n";
				return;
			}
			//Sonst speichern
			else
			{
				tempBook.tags.push_back(tempTag.TagID);
			}
		}

		//Wenn alles funktioniert hat, dann
		//ID generieren und Buch hinzufügen
		tempBook.bookID = idGeneration(kBook);
		bookList.push_back(tempBook);
		//100 erfolgreich abgeschlossen
		cout << "100 Befehl erfolgreich ausgeführt\n";
		return;
	}
	else
	{
		cout << "102 Befehl bekannt, aber Kategorie ist unbekannt\n";
		return;
	}
}

void CMDdelete(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "book")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "104 Buch Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Falls das Buch nicht existiert
		if (!ObjExists(kBook, tempID))
		{
			cout << "402 Buch nicht gefunden\n";
			return;
		}

		//Wenn das Buch schon ausgeliehen wird
		if (IsBorrowed(tempID))
		{
			cout << "204 Buch kann nicht gelöscht werden, da es ausgeliehen wird\n";
			return;
		}
		//Buch löschen
		for (int i = 0; i < bookList.size(); ++i)
		{
			if (tempID == bookList[i].bookID)
			{
				bookList.erase(bookList.begin() + i);
				cout << "100 Befehl erfolgreich ausgeführt\n";
				return;
			}
		}
	}
	else if (temp == "author")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "106 Autor Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Wenn der Autor nicht existiert
		if (!ObjExists(kAuthor, tempID))
		{
			cout << "403 AutorIn nicht gefunden\n";
			return;
		}

		//Hat der Autor ein Buch ?
		for (book b : bookList)
		{
			if (b.authorID == tempID)
			{
				cout << "202 AutorIn kann nicht gelöscht werden, da mindestens ein Buch diese/n AutorIn hat\n";
				return;
			}
		}

		//Autor löschen
		for (int i = 0; i < authorList.size(); ++i)
		{
			if (tempID == authorList[i].authorID)
			{
				authorList.erase(authorList.begin() + i);
				cout << "100 Befehl erfolgreich ausgeführt\n";
				return;
			}
		}
	}
	else if (temp == "tag")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "107 Tag Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Wenn der Tag nicht existiert
		if (!ObjExists(kTag, tempID))
		{
			cout << "401 Tag/Schlagwort nicht gefunden\n";
			return;
		}
		//Hat ein Buch den Tag ?
		for (book b : bookList)
		{
			for (int i : b.tags)
			{
				if (tempID == i)
				{
					cout << "201 Tag kann nicht gelöscht werden, da mindestens ein Buch dieses Tag besitzt\n";
					return;
				}
			}
		}

		//Tag löschen
		for (int i = 0; i < tagList.size(); ++i)
		{
			if (tempID == tagList[i].TagID)
			{
				tagList.erase(tagList.begin() + i);
				cout << "100 Befehl erfolgreich ausgeführt\n";
				return;
			}
		}
	}
	else if (temp == "user")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "105 User Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Wenn der User nicht existiert
		if (!ObjExists(kUser, tempID))
		{
			cout << "404 User nicht gefunden\n";
			return;
		}

		//Leiht der User was aus?
		for (leiheintrag l : ausleihListe)
		{
			if (l.userID == tempID)
			{
				cout << "203 User kann nicht gelöscht werden, da diese/r mindestens ein Buch ausleiht\n";
				return;
			}
		}
		//User löschen
		for (int i = 0; i < userList.size(); ++i)
		{
			if (tempID == userList[i].userID)
			{
				userList.erase(userList.begin() + i);
				cout << "100 Befehl erfolgreich ausgeführt\n";
				return;
			}
		}
	}
	else
	{
		cout << "102 Befehl ist bekannt, aber Kategorie ist unbekannt\n";
		return;
	}
}

void CMDshow(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "book")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "104 Buch Eintrag konnte nicht gelesen werden\n";
		}
		//Buch finden und ausgeben
		for (book b : bookList)
		{
			if (b.bookID == tempID)
			{
				cout << b.authorID << " " << b.titel << " " << b.ISBN;
				for (int i : b.tags)
				{
					cout << " " << i;
				}
				cout << '\n';
				return;
			}
		}
		//Wenn kein Buch gefunden wurde
		cout << "402 Buch nicht gefunden\n";
		return;

	}
	else if (temp == "author")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "106 AutorInnen Eintrag konnte nicht gelesen werden\n";
			return;
		}
		//Autor finden und ausgeben
		for (author a : authorList)
		{
			if (a.authorID == tempID)
			{
				cout << a.vorname << " " << a.nachname << '\n';
				return;
			}
		}
		//Wenn kein Autor gefunden wurde
		cout << "403 Autor nicht gefunden\n";
		return;
	}
	else if (temp == "tag")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "107 Tag Eintrag konnte nicht gelesen werden\n";
			return;
		}
		//Tag finden und ausgeben
		for (tag t : tagList)
		{
			if (t.TagID == tempID)
			{
				cout << t.name << '\n';
				return;
			}
		}
		//Wenn kein Tag gefunden wurde
		cout << "401 Tag/Schlagwort nicht gefunden\n";
		return;
	}
	else if (temp == "user")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "105 User Eintrag konnte nicht gelesen werden\n";
			return;
		}
		//User finden und ausgeben
		for (user u : userList)
		{
			if (u.userID == tempID)
			{
				cout << u.vorname << " " << u.nachname << '\n';
				return;
			}
		}
		// Wenn kein User gefunden wurde
		cout << "404 User nicht gefunden\n";
		return;
	}
	else
	{
		cout << "102 Befehl ist zwar bekannt, aber die Kategorie ist unbekannt\n";
		return;
	}
}

void CMDborrow(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	int tempUserID;
	try
	{
		//string in int konvertieren für suche nach BookID
		tempUserID = stoi(temp);
		//Fehler wird ausgeworfen, wenn UserID nicht gelesen werden konnte
	}
	catch (...)
	{
		// Sollte 105 sein mit User-Eintrag konnte nicht gelesen werden
		cout << "105 User Eintrag konnte nicht gelesen werden\n";
		return;
	}
	inputCommand >> temp;
	int tempBookID;
	try
	{
		//string in int konvertieren für suche nach BookID
		tempBookID = stoi(temp);
		//Fehler wird ausgeworfen, wenn BookID nicht gelesen werden konnte
	}
	catch (...)
	{
		// Sollte 104 sein mit Buch-Eintrag konnte nicht gelesen werden
		cout << "104 Buch Eintrag konnte nicht gelesen werden\n";
		return;
	}
	//Wenn Buch nicht existiert
	if (!ObjExists(kBook, tempBookID))
	{
		//402 Buch nicht gefunden
		cout << "402 Buch konnte nicht gelesen werden\n";
		return;
	}
	//Wenn User nicht existiert
	if (!ObjExists(kUser, tempUserID))
	{
		//404 User nicht gefunden
		cout << "404 User nicht gefunden\n";
		return;
	}
	//Wenn Buch schon ausgeliehen ist
	if (IsBorrowed(tempBookID))
	{
		//301 Buch wird gerade ausgeliehen
		cout << "301 Buch wird gerade ausgeliehen\n";
		return;
	}
	//wenn Buch nicht ausgeliehen, ausleihen
	leiheintrag tempBorrowed = { tempUserID, tempBookID };
	ausleihListe.push_back(tempBorrowed);

	//100, hat funktioniert
	cout << "100 Befehl erfolgreich ausgeführt\n";
	return;
}

void CMDreturn(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	int tempUserID;

	//Überprüfung, ob eingabe korrektes Format war für buch und user ID
	try
	{
		//string in int konvertieren für suche nach BookID
		tempUserID = stoi(temp);
	}
	catch (...)
	{
		// Sollte 105 sein mit User-Eintrag konnte nicht gelesen werden
		cout << "105 User Eintrag konnte nicht gelesen werden\n";
		return;
	}
	inputCommand >> temp;
	int tempBookID;
	try
	{
		//string in int konvertieren für suche nach BookID
		tempBookID = stoi(temp);
	}
	catch (...)
	{
		// Sollte 104 sein mit Buch-Eintrag konnte nicht gelesen werden
		cout << "104 Buch Eintrag konnte nicht gelesen werden\n";
		return;
	}

	//Ist das Buch überhaupt vom angegebenen User ausgeliehen
	bool tempIsBorrowed = false;
	bool tempCorrectUser = false;
	for (leiheintrag l : ausleihListe)
	{
		if (l.bookID == tempBookID && l.userID == tempUserID)
		{
			tempIsBorrowed = true;
			tempCorrectUser = true;
			break;
		}
	}
	// Buch wird nicht vom angegebenen User ausgeliehen
	if (!tempIsBorrowed || !tempCorrectUser)
	{
		//Sollte 304 sein mit der Leiheintrag existiert nicht
		cout << "304 Leiheintrag existiert nicht\n";
		//und beenden
		return;
	}
	//Buch ist vom User ausgeliehen
	else if (tempIsBorrowed && tempCorrectUser)
	{
		for (int i = 0; i < ausleihListe.size(); ++i)
		{
			if (ausleihListe[i].bookID == tempBookID && ausleihListe[i].userID == tempUserID)
			{
				//Leiheintrag aus der Liste löschen
				ausleihListe.erase(ausleihListe.begin() + i);
				//100, Befehl erfolgreich ausgeführt
				cout << "100 Befehl erfolgreich ausgeführt\n";
				return;
			}
		}

	}
}

void CMDstatus(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "book")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			//103 ID erwartet, konnte aber nicht gelesen werden
			cout << "103 ID erwartet, konnte aber nicht gelesen werden\n";
			return;
		}

		//Falls das Buch nicht existiert
		if (!ObjExists(kBook, tempID))
		{
			//402 Buch nicht gefunden
			cout << "402 Buch nicht gefunden\n";
			return;
		}

		if (IsBorrowed(tempID))
		{
			//301 Buch ist bereits ausgeliehen
			cout << "301 Buch ist bereits ausgeliehen\n";
			return;
		}
		else
		{
			//300 Buch kann ausgeliehen werden
			cout << "300 Buch kann ausgeliehen werden\n";
			return;
		}
	}
	else if (temp == "user")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			//103 ID erwartet, konnte jedoch nicht gelesen werden
			cout << "103 ID erwartet, konnte jedoch nicht gelesen werden\n";
			return;
		}

		//Wenn der User nicht existiert
		if (!ObjExists(kUser, tempID))
		{
			//404 User konnte nicht gefunden werden
			cout << "404 User konnte nicht gefunden werden\n";
			//beenden
			return;
		}
		bool userBorrows = false;
		for (leiheintrag l : ausleihListe)
		{
			if (l.userID == tempID)
			{
				// Ausgabe der Buch ID
				cout << l.bookID << '\n';
				userBorrows = true;
			}
		}
		if (!userBorrows)
		{
			//302 Benutzer leiht momentan keine Bücher
			cout << "302 Benutzer leiht momentan keine Buecher\n";
			return;
		}
	}
	else
	{
		//102 Befehl bekannt aber Kategorie nicht
		cout << "102 Befehl bekannt, aber Kategorie nicht\n";
		return;
	}
}

void CMDsearch(stringstream& inputCommand)
{
	string temp;
	inputCommand >> temp;
	if (temp == "author")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "106 AutorInnen Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Falls der Autor nicht existiert
		if (!ObjExists(kAuthor, tempID))
		{
			cout << "403 Autor nicht gefunden\n";
			return;
		}
		//Hat der Autor ein Buch?
		bool hasBook = false;
		for (book b : bookList)
		{
			if (b.authorID == tempID)
			{
				cout << b.bookID << '\n';
				hasBook = true;
			}
		}
		//Wenn AutorIn kein Buch hat
		if (!hasBook)
		{
			cout << "405 Suche ergab keine Ergebnisse\n";
			return;
		}
		return;
	}
	else if (temp == "tag")
	{
		inputCommand >> temp;
		int tempID;
		try
		{
			tempID = stoi(temp);
		}
		catch (...)
		{
			cout << "107 Tag Eintrag konnte nicht gelesen werden\n";
			return;
		}

		//Wenn der Tag nicht existiert
		if (!ObjExists(kTag, tempID))
		{
			cout << "401 Tag/Schlagwort nicht gefunden\n";
			return;
		}

		//Buch besitzt Tag
		bool hasBook = false;
		for (book b : bookList)
		{
			for (int i : b.tags)
			{
				if (i == tempID)
				{
					hasBook = true;
					cout << b.bookID << '\n';
				}
			}
		}
		//Wenn Tag zu keinem Buch gehört
		if (!hasBook)
		{
			cout << "403 Suche ergab keine Ergebnisse\n";
			return;
		}
		return;
	}
	else
	{
		cout << "102 Befehl zwar bekannt, aber die Kategorie ist unbekannt\n";
		return;
	}
}