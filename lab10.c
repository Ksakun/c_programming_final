#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define _ID 10
#define _PUBLISHER 11
#define _AUTHOR 12
#define _BOOK 13
#define BY_ID 14
#define BY_NAME 15 

struct DATE
{
	int day;
	int month;
	int year;
}typedef DATE;
struct AUTHOR
{
	int ID;
	char authorName[20];
	char emailAddress[30];
}typedef AUTHOR;

struct PUBLISHER
{
	int ID;
	char publisherName[20];
	char publisherPhoneNumber[12];
}typedef PUBLISHER;

struct BOOK
{
	int bookID;
	char bookName[20];
	DATE publicationDate;
	int authorID;
	int publisherID;
}typedef BOOK;
struct DATABASE
{
	BOOK bookArray[MAX];
	PUBLISHER publisherArray[MAX];
	AUTHOR authorArray[MAX];
}typedef DATABASE;

void _add(DATABASE* database, int TYPE);
void _update(DATABASE* database, int TYPE);
int _delete(DATABASE* database, int TYPE);
int _search(DATABASE* database, int TYPE, int SEARCH_TYPE, int, char*);
void list_author(DATABASE* database, char*);
void list_publisher(DATABASE* database, char*);
void SelectionSort(DATABASE* database, int TYPE, int SORT_TYPE);
void swap(DATABASE* database, int TYPE, int*, int*);
void print_data(DATABASE* database, int TYPE, int*);
void print_all(DATABASE* database, int TYPE);



int current = 0;
int publisher_current = 0;
int author_current = 0;




//
//void ADD(int id, char* name, char* val)
//{
//	PUBLISHER newPub;
//	AUTHOR newAut;
//	newPub.ID = id;
//	strcpy(newPub.publisherName, name);
//	strcpy(newPub.publisherPhoneNumber, val);
//
//	newAut.ID = id;
//	strcpy(newAut.authorName, name);
//	strcpy(newAut.emailAddress, val);
//
//
//	publisherArray[publisher_current++] = newPub;
//	authorArray[author_current++] = newAut;
//}

int main()
{
	DATABASE DB;
	DATABASE* database = &DB;

	while (1)
	{
		printf("\n1. Add information\n2. Update information\n\
3. Delete information\n4. Search information\n\
5. Display a list of book(s) published by an author\n\
6. Display a list of book(s) published by a publisher\n\
7. Display a list of all book\n");

		int command;
		scanf("%d", &command);

		switch (command)
		{
		case 1: // add information
		{
			int TYPE;

			while (1)
			{
				printf("ADD (1. BOOK. 2. PUBLISHER 3. AUTHOR)\n");
				scanf("%d", &TYPE);

				if (TYPE == 1) { TYPE = _BOOK; break; }
				else if (TYPE == 2) { TYPE = _PUBLISHER; break; }
				else if (TYPE == 3) { TYPE = _AUTHOR; break; }
				else printf("wrong number!\n");
			}
			_add(database, TYPE);
			break;
		}
		case 2: // update
		{
			int TYPE;

			while (1)
			{
				printf("UPDATE (1. BOOK. 2. PUBLISHER 3. AUTHOR)\n");
				scanf("%d", &TYPE);

				if (TYPE == 1) { TYPE = _BOOK; break; }
				else if (TYPE == 2) { TYPE = _PUBLISHER; break; }
				else if (TYPE == 3) { TYPE = _AUTHOR; break; }
				else printf("wrong number!\n");
			}
			_update(database, TYPE);
			break;
		}
		case 3: // delete
		{
			int TYPE;
			printf("DELETE (1. BOOK. 2. PUBLISHER 3. AUTHOR)\n");
			scanf("%d", &TYPE);
			while (1)
			{
				if (TYPE == 1) { TYPE = _BOOK; break; }
				else if (TYPE == 2) { TYPE = _PUBLISHER; break; }
				else if (TYPE == 3) { TYPE = _AUTHOR; break; }
				else printf("wrong number!\n");
			}
			_delete(database, TYPE);
			break;
		}
		case 4: // search
		{
			int TYPE;
			int SEARCH_TYPE;
			int s_id = 0;
			char s_name[20] = { 0, };

			while (1)
			{
				printf("SEARCH (1. BOOK. 2. PUBLISHER 3. AUTHOR)\n");
				scanf("%d", &TYPE);
				if (TYPE == 1) { TYPE = _BOOK; break; }
				else if (TYPE == 2) { TYPE = _PUBLISHER; break; }
				else if (TYPE == 3) { TYPE = _AUTHOR; break; }
				else printf("wrong number!\n");
			}

			while (1)
			{
				printf("SEARCH (1. byID 2 byName)\n");
				scanf("%d", &SEARCH_TYPE);

				if (SEARCH_TYPE == 1)
				{
					SEARCH_TYPE = BY_ID;
					printf("Enter ID to find: ");
					scanf("%d", &s_id);
					break;
				}
				else if (SEARCH_TYPE == 2)
				{
					SEARCH_TYPE = BY_NAME;
					printf("Enter Name to find: ");
					scanf("%s", s_name);
					break;
				}
				else printf("wrong number!\n");
			}


			int foundIndex = _search(database, TYPE, SEARCH_TYPE, s_id, s_name);
			if (foundIndex == -1)
			{
				printf("cannot find!\n");
			}
			else
			{
				printf("I found!\n");
				print_data(database, TYPE, &foundIndex);
			}
			break;

		}
		case 5: // display by author
		{
			char author[20];

			printf("Enter author to display: ");
			scanf("%s", author);

			list_author(database, author);


			break;
		}
		case 6:
		{
			char publisherName[20];

			printf("Enter publisherName to display: ");
			scanf("%s", publisherName);

			list_publisher(database, publisherName);

			break;
		}
		case 7:
		{
			int TYPE;
			printf("DISPLAY (1. BOOK. 2. PUBLISHER 3. AUTHOR)\n");
			scanf("%d", &TYPE);
			while (1)
			{
				if (TYPE == 1) { TYPE = _BOOK; break; }
				else if (TYPE == 2) { TYPE = _PUBLISHER; break; }
				else if (TYPE == 3) { TYPE = _AUTHOR; break; }
				else printf("wrong number!\n");
			}
			print_all(database, TYPE);
			break;
		}
		default:
			break;
		}
	}

}

void swap(DATABASE* database, int TYPE, int* ptrIndex1, int* ptrIndex2)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;

	switch (TYPE)
	{
	case _BOOK:
	{
		BOOK temp;
		temp = bookArray[(*ptrIndex1)];
		bookArray[(*ptrIndex1)] = bookArray[(*ptrIndex2)];
		bookArray[(*ptrIndex2)] = temp;
		break;
	}
	case _PUBLISHER:
	{
		PUBLISHER temp;
		temp = publisherArray[(*ptrIndex1)];
		publisherArray[(*ptrIndex1)] = publisherArray[(*ptrIndex2)];
		publisherArray[(*ptrIndex2)] = temp;
		break;
	}
	case _AUTHOR:
	{
		AUTHOR temp;
		temp = authorArray[(*ptrIndex1)];
		authorArray[(*ptrIndex1)] = authorArray[(*ptrIndex2)];
		authorArray[(*ptrIndex2)] = temp;
		break;
	}
	}
}

void SelectionSort(DATABASE* database, int TYPE, int SORT_TYPE)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	switch (TYPE)
	{
	case _BOOK:
	{
		if (SORT_TYPE == BY_ID)
		{
			for (int i = 0; i < current; i++)
			{
				int minIndex = i;
				int minVal = bookArray[i].bookID;
				for (int j = i; j < current; j++)
				{
					if (minVal > bookArray[j].bookID)
					{
						minIndex = j;
						minVal = bookArray[j].bookID;
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		else if (SORT_TYPE == BY_NAME)
		{
			for (int i = 0; i < current; i++)
			{
				int minIndex = i;
				char minVal[20];
				strcpy(minVal, bookArray[i].bookName);
				for (int j = i; j < current; j++)
				{

					if (strcmp(minVal, bookArray[j].bookName) > 0)
					{
						minIndex = j;
						strcpy(minVal, bookArray[j].bookName);
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		break;
	}
	case _PUBLISHER:
	{
		if (SORT_TYPE == BY_ID)
		{
			for (int i = 0; i < publisher_current; i++)
			{
				int minIndex = i;
				int minVal = publisherArray[i].ID;
				for (int j = i; j < publisher_current; j++)
				{
					if (minVal > publisherArray[j].ID)
					{
						minIndex = j;
						minVal = publisherArray[j].ID;
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		else if (SORT_TYPE == BY_NAME)
		{
			for (int i = 0; i < publisher_current; i++)
			{
				int minIndex = i;
				char minVal[20];
				strcpy(minVal, publisherArray[i].publisherName);

				for (int j = i; j < publisher_current; j++)
				{

					if (strcmp(minVal, publisherArray[j].publisherName) > 0)
					{
						minIndex = j;
						strcpy(minVal, publisherArray[j].publisherName);
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		break;
	}
	case _AUTHOR:
	{
		if (SORT_TYPE == BY_ID)
		{
			for (int i = 0; i < author_current; i++)
			{
				int minIndex = i;
				int minVal = authorArray[i].ID;
				for (int j = i; j < author_current; j++)
				{
					if (minVal > authorArray[j].ID)
					{
						minIndex = j;
						minVal = authorArray[j].ID;
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		else if (SORT_TYPE == BY_NAME)
		{
			for (int i = 0; i < author_current; i++)
			{
				int minIndex = i;
				char minVal[20];
				strcpy(minVal, authorArray[i].authorName);

				for (int j = i; j < author_current; j++)
				{

					if (strcmp(minVal, authorArray[j].authorName) > 0)
					{
						minIndex = j;
						strcpy(minVal, authorArray[j].authorName);
					}
				}
				swap(database, TYPE, &i, &minIndex);
			}
		}
		break;
	}
	}
}

void _add(DATABASE* database, int TYPE)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	switch (TYPE)
	{
	case _BOOK:
	{
		BOOK newBook;
		char dummy;
		int flag = 0;

		do
		{
			flag = 0;

			printf("Enter Book ID: ");
			scanf("%d", &newBook.bookID);
			if (newBook.bookID < 0) // check negative number
			{
				printf("book id is negative number.\n");
				flag = 1;
				continue;
			}
			for (int i = 0; i < current; i++) // check duplicate
			{
				if (newBook.bookID == bookArray[i].bookID)
				{
					printf("this is duplicate book id.\n");
					flag = 1;
					break;
				}
			}
		} while (flag);

		printf("Enter Book Name: ");
		scanf("%s", newBook.bookName);
		printf("Enter publicationDate: enter ex> day.month.year: ");
		scanf("%d%c%d%c%d", &newBook.publicationDate.day, &dummy, \
			& newBook.publicationDate.month, &dummy, &newBook.publicationDate.year);


		// get publisher info

		printf("\n");
		print_all(database, _PUBLISHER);
		while (1)
		{
			int select;
			printf("Select publisher by ID: ");
			scanf("%d", &select);
			int index = _search(database, _PUBLISHER, BY_ID, select, NULL);
			if (index == -1) printf("Cannot Find!\n");
			else
			{
				newBook.publisherID = select;
				break;
			}
		}

		printf("\n");
		print_all(database, _AUTHOR);
		while (1)
		{
			int select;
			printf("Select author by ID: ");
			scanf("%d", &select);
			int index = _search(database, _AUTHOR, BY_ID, select, NULL);
			if (index == -1) printf("Cannot Find!\n");
			else
			{
				newBook.authorID = select;
				break;
			}
		}

		bookArray[current++] = newBook;
		break;
	}
	case _PUBLISHER:
	{
		PUBLISHER newPub;
		int flag = 0;
		do
		{
			flag = 0;

			printf("Enter pub ID: ");
			scanf("%d", &newPub.ID);
			if (newPub.ID < 0) // check negative number
			{
				printf("book id is negative number.\n");
				flag = 1;
				continue;
			}
			for (int i = 0; i < publisher_current; i++) // check duplicate
			{
				if (newPub.ID == publisherArray[i].ID)
				{
					printf("this is duplicate id.\n");
					flag = 1;
					break;
				}
			}
		} while (flag);

		printf("Enter publisher Name: ");
		scanf("%s", newPub.publisherName);
		printf("Enter publisher phone Number : ");
		scanf("%s", newPub.publisherPhoneNumber);

		publisherArray[publisher_current++] = newPub;
		break;
	}
	case _AUTHOR:
	{
		AUTHOR newAuthor;
		int flag = 0;
		do
		{
			flag = 0;

			printf("Enter author ID: ");
			scanf("%d", &newAuthor.ID);
			if (newAuthor.ID < 0) // check negative number
			{
				printf("book id is negative number.\n");
				flag = 1;
				continue;
			}
			for (int i = 0; i < author_current; i++) // check duplicate
			{
				if (newAuthor.ID == authorArray[i].ID)
				{
					printf("this is duplicate id.\n");
					flag = 1;
					break;
				}
			}
		} while (flag);

		printf("Enter author Name: ");
		scanf("%s", newAuthor.authorName);
		printf("Enter author email address : ");
		scanf("%s", newAuthor.emailAddress);

		authorArray[author_current++] = newAuthor;
		break;
	}
	}
}

void _update(DATABASE* database, int TYPE)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	char dummy;
	switch (TYPE)
	{
	case _BOOK:
	{
		BOOK newBook;
		int oldIndex = 0;
		printf("Enter Book ID to update: ");
		scanf("%d", &newBook.bookID);
		oldIndex = _search(database, _BOOK, BY_ID, newBook.bookID, NULL);
		if (oldIndex == -1) { printf("cannot find!\n"); break; }

		int c_id = 0x0001, c_name = 0x0002, c_date = 0x0004, pub_id = 0x0008, auth_id = 0x0010;
		int choice = 0;
		printf("What do you want to change?\n1. Book id\n2. Book name\n3. Book date\n4. publisher ID\n5. author ID");
		scanf("%d", &choice);
		if ((c_id >> (choice - 1)) & 0x01)
		{
			int flag = 0;
			do
			{
				flag = 0;

				printf("Enter Book ID: ");
				scanf("%d", &newBook.bookID);
				if (newBook.bookID < 0) // check negative number
				{
					printf("book id is negative number.\n");
					flag = 1;
					continue;
				}
				for (int i = 0; i < current; i++) // check duplicate
				{
					if (newBook.bookID == bookArray[i].bookID && oldIndex != i)
					{
						printf("this is duplicate book id.\n");
						flag = 1;
						break;
					}
				}
			} while (flag);

			bookArray[oldIndex].bookID = newBook.bookID;
		}
		if ((c_name >> (choice - 1)) & 0x01)
		{
			printf("Enter Book Name: ");
			scanf("%s", newBook.bookName);
			for (int i = 0; i < 20; i++)
				bookArray[oldIndex].bookName[i] = newBook.bookName[i];
		}
		if ((c_date >> (choice - 1)) & 0x01)
		{
			printf("Enter publicationDate: enter ex> day.month.year: ");
			scanf("%d%c%d%c%d", &newBook.publicationDate.day, &dummy, \
				& newBook.publicationDate.month, &dummy, &newBook.publicationDate.year);

			bookArray[oldIndex].publicationDate.day = newBook.publicationDate.day;
			bookArray[oldIndex].publicationDate.month = newBook.publicationDate.month;
			bookArray[oldIndex].publicationDate.year = newBook.publicationDate.year;
		}
		if ((pub_id >> (choice - 1)) & 0x01)
		{
			printf("Enter publisher ID: ");
			scanf("%d", &newBook.publisherID);
		}
		if ((auth_id >> (choice - 1)) & 0x01)
		{
			printf("Enter author ID: ");
			scanf("%d", &newBook.authorID);
		}

		printf("update Finished!\n");
		break;
	}
	case _PUBLISHER:
	{
		PUBLISHER newPub;
		int oldIndex = 0;
		print_all(database, _PUBLISHER);
		printf("Enter publisher ID to update: ");
		scanf("%d", &newPub.ID);
		oldIndex = _search(database, _PUBLISHER, BY_ID, newPub.ID, NULL);
		if (oldIndex == -1) { printf("cannot find!\n"); break; }

		int c_id = 0x0001, c_name = 0x0002, c_pnum = 0x0004;
		int choice = 0;
		printf("What do you want to change?\n1. publisher id\n2. publisher name\n3. publisher phone number\n:");
		scanf("%d", &choice);
		if ((c_id >> (choice - 1)) & 0x01)
		{
			int flag = 0;
			do
			{
				flag = 0;

				printf("Enter publisher ID: ");
				scanf("%d", &newPub.ID);
				if (newPub.ID < 0) // check negative number
				{
					printf("book id is negative number.\n");
					flag = 1;
				}
				if (_search(database, _PUBLISHER, BY_ID, newPub.ID, NULL) == oldIndex)
				{
					printf("this is duplicate publisher id.\n");
					flag = 1;
				}
			} while (flag);

			publisherArray[oldIndex].ID = newPub.ID;

		}
		if ((c_name >> (choice - 1)) & 0x01)
		{
			printf("Enter name: ");
			scanf("%s", newPub.publisherName);
		}
		if ((c_pnum >> (choice - 1)) & 0x01)
		{
			printf("Enter phone number: ");
			scanf("%s", newPub.publisherPhoneNumber);
		}
		break;
	}
	case _AUTHOR:
	{
		AUTHOR newAuthor;
		int oldIndex = 0;
		print_all(database, _AUTHOR);
		printf("Enter author ID to update: ");
		scanf("%d", &newAuthor.ID);
		oldIndex = _search(database, _AUTHOR, BY_ID, newAuthor.ID, NULL);
		if (oldIndex == -1) { printf("cannot find!\n"); break; }

		int c_id = 0x0001, c_name = 0x0002, c_email = 0x0004;
		int choice = 0;
		printf("What do you want to change?\n1. author id\n2. author name\n3. author email\n: ");
		scanf("%d", &choice);
		if ((c_id >> (choice - 1)) & 0x01)
		{
			int flag = 0;
			do
			{
				flag = 0;

				printf("Enter publisher ID: ");
				scanf("%d", &newAuthor.ID);
				if (newAuthor.ID < 0) // check negative number
				{
					printf("author id is negative number.\n");
					flag = 1;
				}
				if (_search(database, _AUTHOR, BY_ID, newAuthor.ID, NULL) == oldIndex)
				{
					printf("this is duplicate author id.\n");
					flag = 1;
				}
			} while (flag);

			authorArray[oldIndex].ID = newAuthor.ID;

		}
		if ((c_name >> (choice - 1)) & 0x01)
		{
			printf("Enter name: ");
			scanf("%s", newAuthor.authorName);
		}
		if ((c_email >> (choice - 1)) & 0x01)
		{
			printf("Enter email: ");
			scanf("%s", newAuthor.emailAddress);
		}
		break;
	}
	}
}

int _delete(DATABASE* database, int TYPE)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	int toDelID;
	int toDelIndex;

	print_all(database, TYPE);
	printf("Select id to Delete:");
	scanf("%d", &toDelID);

	toDelIndex = _search(database, TYPE, BY_NAME, toDelID, NULL);
	if (toDelIndex == -1)
	{
		printf("Cannot find ID\n");
		return -1;
	}
	switch (TYPE)
	{
	case _BOOK:
	{
		for (int i = toDelIndex; i < current; i++) bookArray[i] = bookArray[i + 1];
		current--;
		break;
	}
	case _PUBLISHER:
	{
		for (int i = toDelIndex; i < publisher_current; i++) publisherArray[i] = publisherArray[i + 1];
		publisher_current--;
		break;
	}
	case _AUTHOR:
	{
		for (int i = toDelIndex; i < author_current; i++) authorArray[i] = authorArray[i + 1];
		author_current--;
		break;
	}
	}
}

int _search(DATABASE* database, int TYPE, int SEARCH_TYPE, int toDelID, char* toDelName)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;

	SelectionSort(database, TYPE, SEARCH_TYPE);

	switch (TYPE)
	{
	case _BOOK:
	{
		if (SEARCH_TYPE == BY_ID)
		{
			int start = 0;
			int end = current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;
				if (bookArray[mid].bookID == toDelID) return mid;
				else if (bookArray[mid].bookID < toDelID) start = mid + 1;
				else if (bookArray[mid].bookID > toDelID) end = mid - 1;
			}
			return -1;
		}
		else if (SEARCH_TYPE == BY_NAME)
		{
			int start = 0;
			int end = current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;

				if (strcmp(bookArray[mid].bookName, toDelName) == 0) return mid;
				else if (strcmp(bookArray[mid].bookName, toDelName) < 0) start = mid + 1;
				else if (strcmp(bookArray[mid].bookName, toDelName) > 0) end = mid - 1;
			}
			return -1;
		}
	}
	case _PUBLISHER:
	{
		if (SEARCH_TYPE == BY_ID)
		{
			int start = 0;
			int end = publisher_current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;
				if (publisherArray[mid].ID == toDelID) return mid;
				else if (publisherArray[mid].ID < toDelID) start = mid + 1;
				else if (publisherArray[mid].ID > toDelID) end = mid - 1;
			}
			return -1;
		}
		else if (SEARCH_TYPE == BY_NAME)
		{
			int start = 0;
			int end = publisher_current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;

				if (strcmp(publisherArray[mid].publisherName, toDelName) == 0) return mid;
				else if (strcmp(publisherArray[mid].publisherName, toDelName) < 0) start = mid + 1;
				else if (strcmp(publisherArray[mid].publisherName, toDelName) > 0) end = mid - 1;
			}
			return -1;
		}
	}
	case _AUTHOR:
	{
		if (SEARCH_TYPE == BY_ID)
		{
			int start = 0;
			int end = author_current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;
				if (authorArray[mid].ID == toDelID) return mid;
				else if (authorArray[mid].ID < toDelID) start = mid + 1;
				else if (authorArray[mid].ID > toDelID) end = mid - 1;
			}
			return -1;
		}
		else if (SEARCH_TYPE == BY_NAME)
		{
			int start = 0;
			int end = author_current;
			int mid;
			while (start <= end)
			{
				mid = (start + end) / 2;

				if (strcmp(authorArray[mid].authorName, toDelName) == 0) return mid;
				else if (strcmp(authorArray[mid].authorName, toDelName) < 0) start = mid + 1;
				else if (strcmp(authorArray[mid].authorName, toDelName) > 0) end = mid - 1;
			}
			return -1;
		}
	}
	}
}


void print_data(DATABASE* database, int TYPE, int* ptrIndex)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	switch (TYPE)
	{

	case _BOOK:
	{
		int publisherIndex = _search(database, _PUBLISHER, BY_ID, bookArray[(*ptrIndex)].publisherID, NULL);
		int authorIndex = _search(database, _AUTHOR, BY_ID, bookArray[(*ptrIndex)].authorID, NULL);

		printf("update result:\n");
		printf("Book bookID : %d\n", bookArray[(*ptrIndex)].bookID);
		printf("Book bookName : %s\n", bookArray[(*ptrIndex)].bookName);
		printf("Book publicationDate : %d.%d.%d\n", bookArray[(*ptrIndex)].publicationDate.day, \
			bookArray[(*ptrIndex)].publicationDate.month, bookArray[(*ptrIndex)].publicationDate.year);
		print_data(database, _PUBLISHER, &publisherIndex);
		print_data(database, _AUTHOR, &authorIndex);
		break;
	}
	case _PUBLISHER:
	{
		printf("Book publisherID : %d\n", publisherArray[(*ptrIndex)].ID);
		printf("Book publisherName : %s\n", publisherArray[(*ptrIndex)].publisherName);
		printf("Book publisherPhoneNumber : %s\n", publisherArray[(*ptrIndex)].publisherPhoneNumber);
		break;
	}
	case _AUTHOR:
	{
		printf("Book authorID : %d\n", publisherArray[(*ptrIndex)].ID);
		printf("Book author : %s\n", authorArray[(*ptrIndex)].authorName);
		printf("Book emailAddress : %s\n", authorArray[(*ptrIndex)].emailAddress);
		break;
	}
	}

}

void print_all(DATABASE* database, int TYPE)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	switch (TYPE)
	{
	case _BOOK:
	{
		for (int i = 0; i < current; i++)
		{
			print_data(database, _BOOK, &i);
		}
		break;
	}
	case _PUBLISHER:
	{
		for (int i = 0; i < publisher_current; i++)
		{
			print_data(database, _PUBLISHER, &i);
		}
		break;
	}
	case _AUTHOR:
	{
		for (int i = 0; i < author_current; i++)
		{
			print_data(database, _AUTHOR, &i);
		}
		break;
	}
	}
}

void list_author(DATABASE* database, char* author)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;
	int authorID = _search(database, _AUTHOR, BY_NAME, 0, author);

	for (int i = 0; i < current; i++)
	{
		if (bookArray[i].authorID == authorID)
		{
			printf("search result:\n");
			print_data(database, _BOOK, &i);
		}
	}
}
void list_publisher(DATABASE* database, char* publisherName)
{
	BOOK* bookArray = database->bookArray;
	PUBLISHER* publisherArray = database->publisherArray;
	AUTHOR* authorArray = database->authorArray;

	int publisherID = _search(database, _PUBLISHER, BY_NAME, 0, publisherName);

	for (int i = 0; i < current; i++)
	{
		if (bookArray[i].publisherID == publisherID)
		{
			printf("search result:\n");
			print_data(database, _BOOK, &i);
		}
	}
}

//
