#include "ID_Generation.h"
extern vector<author> authorList;
extern vector<book> bookList;
extern vector<user> userList;
extern vector<tag> tagList;

extern const string kBook;
extern const string kTag;
extern const string kAuthor;
extern const string kUser;

int idGeneration(const string Klasse)
{
	if (Klasse == kUser)
	{
		if (!userList.empty())
		{
			user tempUser = userList[userList.size() - 1];

			//M�glich, da Sorted nach ID
			return tempUser.userID + 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Klasse == kAuthor)
	{
		if (!authorList.empty())
		{
			author tempAuthor = authorList[authorList.size() - 1];

			//M�glich, da sorted nach ID
			return tempAuthor.authorID + 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Klasse == kTag)
	{
		if (!tagList.empty())
		{
			tag tempTag = tagList[tagList.size() - 1];

			//M�glich, da sorted nach ID
			return tempTag.TagID + 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Klasse == kBook)
	{
		if (!bookList.empty())
		{
			book tempBook = bookList[bookList.size() - 1];

			//M�glich, da sorted nach ID
			return tempBook.bookID + 1;
		}
		else
		{
			return 0;
		}
	}
}