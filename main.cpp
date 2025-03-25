#include <iostream>
#include<fstream>
using namespace std;
struct book
{
    string bookName;
    string authorName;
    int num_of_pages;
};
book books[1001];
int num_of_books;
int max_num_of_books=1000;
void mainMenu();
void addBook( string book_name, string author_name,int numOfPages);
void displayBooks();
void sreachBook(string book_name);
void deleteBook(string book_name);
bool bookExists(string book_name);
void editBookData(string new_book_name,string new_author_name,int new_num_of_pages);
void loadFromFile();
void saveToFile();
int main()
{
    loadFromFile();
    mainMenu();

    return 0;
}

void mainMenu()
{
    int option;
    do
    {
        cout<<"----- The library system ----- \n";
        cout<<"please, enter number 1 if you want to add new book \n";
        cout<<"please, enter number 2 if you want to see books data \n";
        cout<<"please, enter number 3 if you want to search about any book \n";
        cout<<"please, enter number 4 if you want to delete any book \n";
        cout<<"please, enter number 5 if you want to change data for any book \n";
        cin>>option;
        if(option==1)
        {
            string book_name;
            string author_name;
            cout<<"please, enter book name : "<<endl;
            cin>>book_name;
            cout<<"please, enter author name : "<<endl;
            cin>>author_name;
            int numofPages;
            cout<<"please, number of book pages : "<<endl;
            cin>>numofPages;
            if(numofPages<=0)
            {
                cout<<"Invalid number of pages \n";
                return;
            }
            addBook( book_name,author_name,numofPages);
        }
        else if (option==2)
        {
           displayBooks();
        }
        else if(option==3)
        {
            string book_name;
            cout<<"please, enter the  book name : "<<endl;
            cin>>book_name;
            sreachBook(book_name);
        }
        else if (option==4)
        {
            string book_name;
            cout<<"please, enter the  book name : "<<endl;
            cin>>book_name;
            deleteBook(book_name);
        }
        else if(option==5)
        {
            string newBookName,newAuthorName;
            cout<<"please, enter new book name : \n";
            cin>>newBookName;
            cout<<"please, enter new author name : \n";
            cin>>newAuthorName;
            int newNumOfPages;
            cout<<"please, enter new number of pages : \n";
            cin>>newNumOfPages;
            editBookData(newBookName,newAuthorName,newNumOfPages);
        }
        else
        {
            cout<<"Incorrect option, try again\n ";
        }
    }while(option>0 && option<=5);
}

bool bookExists(string book_name)
{
    for(int i=0;i<num_of_books;i++)
    {
        if(books[i].bookName==book_name)
        {
            return true;
        }
    }
     return false;
}

void addBook( string book_name, string author_name, int numofPages)
{
    if(num_of_books>=max_num_of_books)
    {
        cout<<"Cannot add more books . \n";
        return;
    }
    if(!bookExists(book_name))
    {
        books[num_of_books].bookName=book_name;
        books[num_of_books].authorName=author_name;
        books[num_of_books].num_of_pages=numofPages;
        num_of_books++;
        saveToFile();
    }
    else
    {
        cout<<"book already exists . \n";
        return;
    }
}

void displayBooks()
{
    if(num_of_books==0)
    {
        cout<<"No books added yet \n";
    }
    else
    {
        cout <<"List of books : \n";
    for(int i=0;i<num_of_books;i++)
    {
        cout<<"the name of book : " <<books[i].bookName<<endl;
        cout<<"the author name : "<<books[i].authorName<<endl;
        cout<<"number of book pages : "<<books[i].num_of_pages<<endl;
    }
    }
}

void sreachBook(string book_name)
{
    for(int i=0;i<num_of_books;i++)
    {
        if(book_name==books[i].bookName)
        {
            cout<<"book founded , and the author name is : "<<books[i].authorName<<endl;
            break;
        }
        else
        {
            cout<<"book not founded"<<endl;
        }
    }
}

void deleteBook(string book_name)
{
    bool found=false;
    for(int i=0;i<num_of_books;i++)
    {
        if(book_name==books[i].bookName)
        {
            found=true;
            num_of_books--;
            saveToFile();
            cout<<"Removed successfully \n";
            break;
        }
        if(! found)
        {
            cout<<"book not founded. \n";
        }
    }
}

void editBookData(string new_book_name,string new_author_name,int new_num_of_pages)
{
    bool found=false;
    for(int i=0;i<num_of_books;i++)
    {
        if(new_book_name==books[i].bookName)
        {
            books[i].bookName=new_book_name;
            books[i].authorName=new_author_name;
            books[i].num_of_pages=new_num_of_pages;
            found=true;
            saveToFile();
            cout<<"the data has been successfully modified \n";
            break;
        }
        if(! found)
        {
            cout<<"book not founded \n";
        }
    }
}

void loadFromFile()
{
    ifstream file("Books.txt");
    if(! file)
    {
        cout<<"No previous data found. \n";
        return;
    }
    num_of_books=0;
    while(getline(file, books[num_of_books].bookName)&& getline(file,books[num_of_books].authorName)&&(file>> books[num_of_books].num_of_pages))
    {
        file.ignore();
        num_of_books++;
    }
    file.close();
    cout<<"Data loaded successfully \n";
}

void saveToFile()
{
    ofstream file("Books.txt");
    if(! file.is_open())
    {
        cout<< "Error: unable to open file for saving. \n";
        return;
    }
    for(int i=0;i<num_of_books;i++)
    {
        file<<books[i].bookName<<endl;
        file<<books[i].authorName<<endl;
        file<<books[i].num_of_pages<<endl;
    }
    file.close();
}

