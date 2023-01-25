#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

// Klasa Book predstavlja knjigu u biblioteci
class Book {
public:
  string title;
  string author;
  int pages;
  int shelf;
  string genre;
  string key;

  Book(string title, string author, int pages, int shelf, string genre) :
    title(title), author(author), pages(pages), shelf(shelf), genre(genre) {
      // Generate a unique key for the book
      this->key = genre[0] + to_string(rand() % 10000);
    }
};

// Klasa library predstavlja kolekciju knjiga
class Library {
private:
  vector<Book> books;

public:
  // Dodaje knjigu
  void addBook(Book book) {
    books.push_back(book);
  }

  // Uklanja knjigu
  void removeBook(string title) {
    vector<Book>::iterator it;
    for (it = books.begin(); it != books.end(); it++) {
      if (it->title == title) {
        books.erase(it);
        return;
      }
    }
    cout << "Knjiga nije nadena" << endl;
  }

  // Pretraga knjige po naslovu
  Book searchByTitle(string title) {
    for (int i = 0; i < books.size(); i++) {
      if (books[i].title == title) {
        return books[i];
      }
    }
    return Book("", "", 0, 0, 0);
  }

  // Pretraga knjige po autoru
  vector<Book> searchByAuthor(string author) {
    vector<Book> results;
    for (int i = 0; i < books.size(); i++) {
      if (books[i].author == author) {
        results.push_back(books[i]);
      }
    }
    return results;
  }

  // Pretraga knjige po policama
  vector<Book> searchByShelf(int shelf) {
    vector<Book> results;
    for (int i = 0; i < books.size(); i++) {
      if (books[i].shelf == shelf) {
        results.push_back(books[i]);
      }
    }
    return results;
  }

    // Ispis svih knjiga u biblioteci
  void listBooks() {
    if (books.size() == 0) {
      cout << "Nema knjiga u biblioteci" << endl;
    } else {
      for (int i = 0; i < books.size(); i++) {
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "Pages: " << books[i].pages << endl;
        cout << "Genre: " << books[i].genre << endl;
        cout << "Shelf: " << books[i].shelf << endl;
      }
    }
  }

  void listBooksOnShelf(int shelf) {
    bool found = false;
    for (int i = 0; i < books.size(); i++) {
      if (books[i].shelf == shelf) {
        cout << "Naslov: " << books[i].title << endl;
        cout << "Autor: " << books[i].author << endl;
        cout << "Stranice: " << books[i].pages << endl;
        cout << "Zanr: " << books[i].genre << endl;
        cout << "Polica: " << books[i].shelf << endl;
        found = true;
      }
    }
    if (!found) {
      cout << "Nema knjiga na polici " << shelf << endl;
    }
  }

    // Ispis svih polica u biblioteci
  void listShelves() {
    set<int> shelves;
    for (int i = 0; i < books.size(); i++) {
      shelves.insert(books[i].shelf);
    }
    cout << "Police:";
    for (set<int>::iterator it = shelves.begin(); it != shelves.end(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
  }


};

// Klasa student predstavlja studenta u biblioteci
class Student {
private:
  string name;
  vector<Book> borrowedBooks;

public:
  //Student(string name) : name(name) {}

  // Posudi knjigu iz biblioteke
  void borrowBook(Library& library, string title) {
    Book book = library.searchByTitle(title);
    if (book.title == "") {
      cout << "Knjiga nije nadena" << endl;
    } else {
      borrowedBooks.push_back(book);
      library.removeBook(title);
      cout << "Knjiga uspjesno posudena" << endl;
    }
  }

  // Vrati knjigu u biblioteku
  void returnBook(Library& library, string title) {
    for (int i = 0; i < borrowedBooks.size(); i++) {
      if (borrowedBooks[i].title == title) {
        library.addBook(borrowedBooks[i]);
        borrowedBooks.erase(borrowedBooks.begin() + i);
        cout << "Knjiga uspjesno vracena" << endl;
        return;
      }
    }
    cout << "Knjiga nije pronadena" << endl;
  }

    // Student menu
    // Student menu
  void menu(Library& library) {
    while (true) {
      cout << "Student Menu" << endl;
      cout << "------------" << endl;
      cout << "1. Posudi knjigu" << endl;
      cout << "2. Vrati knjigu" << endl;
      cout << "3. Pretraga po naslovu" << endl;
      cout << "4. Pretraga po autoru" << endl;
      cout << "5. Pretraga po policama" << endl;
      cout << "6. Ispis svih knjiga" << endl;
      cout << "7. Izlaz" << endl;
      cout << "Unos: ";

      int choice;
      cin >> choice;
      cin.ignore();

      switch (choice) {
        case 1: {
          // Posudi knjigu
          cout << "Unesite naslov knjige koju zelite posuditi: ";
          string title;
          getline(cin, title);
          borrowBook(library, title);
          break;
        }
        case 2: {
          // Vrati knjigu
          cout << "Unesite naslov knjige koju zelite vratiti: ";
          string title;
          getline(cin, title);
          returnBook(library, title);
          break;
        }
        case 3: {
          // Pretraga knjiga po naslovu
          cout << "Unesite naslov knjige: ";
          string title;
          getline(cin, title);
          Book book = library.searchByTitle(title);
          if (book.title == "") {
            cout << "Knjiga nije nadena" << endl;
          } else {
            cout << "Naslov: " << book.title << endl;
            cout << "Autor: " << book.author << endl;
            cout << "Stranice: " << book.pages << endl;
            cout << "Zanr: " << book.genre << endl;
            cout << "Polica: " << book.shelf << endl;
          }
          break;
        }
        case 4: {
          // Pretraga knjiga po autoru
          cout << "Unesite autora: ";
          string author;
          getline(cin, author);
          vector<Book> books = library.searchByAuthor(author);
          if (books.size() == 0) {
            cout << "Knjige nisu nadene" << endl;
          } else {
            for (int i = 0; i < books.size(); i++) {
              cout << "Naslov: " << books[i].title << endl;
              cout << "Autor: " << books[i].author << endl;
              cout << "Stranice: " << books[i].pages << endl;
              cout << "Zanr: " << books[i].genre << endl;
              cout << "Police: " << books[i].shelf << endl;
            }
          }
          break;
        }
        case 5: {
                    // Pretraga knjige po policama
                    library.listShelves();
          cout << "Unesite broj police: ";
          int shelf;
          cin >> shelf;
          cin.ignore();
          vector<Book> books = library.searchByShelf(shelf);
          if (books.size() == 0) {
            cout << "No books found" << endl;
          } else {
            for (int i = 0; i < books.size(); i++) {
              cout << "Naslov: " << books[i].title << endl;
              cout << "Autor: " << books[i].author << endl;
              cout << "Stranice: " << books[i].pages << endl;
              cout << "Zanr: " << books[i].genre << endl;
              cout << "Police: " << books[i].shelf << endl;
            }
          }
          break;
        }
        case 6: {
          // Ispis svih knjiga
          library.listBooks();
          break;
        }
        case 7: {
          // Quit
          return;
        }
        default: {
          cout << "Unos nije ispravan" << endl;
          break;
        }
      }
    }
  }
};


// Klasa radnik predstavlja radnika

class Worker {
public:
 void addBook(Library& library, Book book) {
    library.addBook(book);
  }

  // Ukloni knjigu
  void removeBook(Library& library, string title) {
    library.removeBook(title);
  }

  void menu(Library& library) {
    while (true) {
      cout << "Radnik Menu" << endl;
      cout << "-----------" << endl;
      cout << "1. Dodaj knjigu" << endl;
      cout << "2. Ukloni knjigu" << endl;
      cout << "3. Izlaz" << endl;
      cout << "Unos: ";

      int choice;
      cin >> choice;
      cin.ignore();

      switch (choice) {
        case 1: {
          // Dodaj knjigu
          cout << "Unesite naslov knjige: ";
          string title;
          getline(cin, title);
          cout << "Unesite autora knjige: ";
          string author;
          getline(cin, author);
          cout << "Unesite broj stranica knjige: ";
          int pages;
          cin >> pages;
          cin.ignore();
          cout << "Unesite broj police: ";
          int shelf;
          cin >> shelf;
          cin.ignore();
          cout << "Unesite zanr knjige: ";
          string genre;
          getline(cin, genre);
          Book book(title, author, pages, shelf, genre);
          addBook(library, book);
          cout << "Knjiga uspjesno dodana" << endl;
          break;
        }
        case 2: {
          // Ukloni knjigu
          cout << "Unesite naslov knjige: ";
          string title;
          getline(cin, title);
          removeBook(library, title);
          break;
        }
        case 3: {
          // Quit
          return;
        }
        default: {
          cout << "Unos nije ispravan" << endl;
          break;
        }
      }
    }
  }
};





// Pretraga knjiga po naslovu
void searchByTitle(Library& library) {
  cout << "Unesite naslov knjige koju trazite: ";
  string title;
  getline(cin, title);
  Book book = library.searchByTitle(title);
  if (book.title == "") {
    cout << "Knjiga nije nadena" << endl;
  } else {
    cout << book.title << " by " << book.author << endl;
  }
}

// Pretraga knjiga po autoru
void searchByAuthor(Library& library) {
  cout << "Unesite autora knjiga koje trazite: ";
  string author;
  getline(cin, author);
  vector<Book> books = library.searchByAuthor(author);
  if (books.size() == 0) {
    cout << "Knjige nisu nadene" << endl;
  } else {
    cout << books.size() << " knjige nadene:" << endl;
    for (int i = 0; i < books.size(); i++) {
      cout << books[i].title << endl;
    }
  }
}


int main() {
  Library library;

  while (true) {
    cout << "Main Menu" << endl;
    cout << "----------" << endl;
    cout << "1. Student" << endl;
    cout << "2. Radnik" << endl;
    cout << "3. Quit" << endl;
    cout << "Unos: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
      case 1: {
        // Student menu
        Student student;
        student.menu(library);
        break;
      }
      case 2: {
        // Worker menu
        Worker worker;
        worker.menu(library);
        break;
      }
      case 3: {
        // Quit
        return 0;
      }
      default: {
        cout << "Unos nije ispravan" << endl;
        break;
      }
    }
  }

  return 0;
}
