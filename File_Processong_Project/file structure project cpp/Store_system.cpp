#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

class Goods {
  public:
     char name[20];
     int num, price;
};
void add_to_store() {
     ofstream add("store.txt", ios::app);
      Goods pr;  char c;
     do {
          cout <<"Enter product name, quantity and it's price: ";
          cin >> pr.name >> pr.num >> pr.price; 
          add.write((char*)& pr, sizeof(pr));  
          cout <<"\n";        
          cout <<"Do you want to add another goods:(y/n)  ";
          cin >> c;
          cout <<"\n\n";
     } while (c == 'y');
     add.close();
     for (size_t i = 0; i < 40; i++) cout<<"*";
     cout <<"\n\n";   
}
void Show_store(){
     Goods pr; string read;
     ifstream show; show.open("store.txt", ios::in);
     if (show.is_open()) {
          show.read((char*)& pr, sizeof(pr));  
          cout <<"Pruduct\t\tquantity\tprice\n\n";
          while (!show.eof()) {
               cout << pr.name <<"\t\t"<< pr.num <<"\t\t"<< pr.price <<"\n\n";
               show.read((char*)& pr, sizeof(pr));
          } 
          show.close();
     } else cout <<"Can't Access store file\n\n";
     for (size_t i = 0; i < 40; i++) cout<<"*";
    cout <<"\n\n"; 
}
void search_on_store() {
    int tc = 0;     Goods pr;
    ifstream search;     char s[10];
    cout << "Enter a product name to search for:  ";   cin >> s;
    bool found = false ;
    search.open("store.txt", ios::in);
    if(search.is_open()) {
       search.read((char*)& pr , sizeof(pr)) ;
       while(!search.eof()){
          if(strcmp(s, pr.name) == 0) {     tc++;
               if(tc == 1)   cout <<"Pruduct\t\tquantity\tprice\n\n";
               cout << pr.name <<"\t\t"<< pr.num <<"\t\t"<< pr.price <<"\n\n";
               found = true ;
          }  search.read((char*)& pr , sizeof(pr));
       }  if(!found) cout << "product not found!\n\n" ;
       search.close();
    } else cout <<"Can't Access store file\n\n";
    for (size_t i = 0; i < 40; i++) cout<<"*";
     cout <<"\n\n"; 
}
void edit_store() {
    int tc = 0;     Goods pr;
    fstream edit;  char str[10];
    cout <<"Enter a product name to update it: ";
    cin >> str;    bool found = false; cout <<"\n";
    edit.open("store.txt", ios::in|ios::out);
    if(edit.is_open()) {
        edit.read((char*)& pr, sizeof(pr)) ;
        while(!edit.eof()) {
            if(strcmp(str, pr.name) == 0){
                cout << "Enter the new product name for : "<< str <<"\t: ";
                cin >> pr.name; cout <<"\n";
                cout << "Enter the new quantity of product for : "<< str <<"\t: ";
                cin >> pr.num; cout <<"\n";
                cout << "Enter the new price for : "<< str <<"\t: ";
                cin >> pr.price; cout <<"\n";
                int curpos = edit.tellg();
                int stusize = sizeof(pr);
                edit.seekp(curpos-stusize , ios::beg);
                edit.write((char*)& pr, sizeof(pr));
                edit.seekg(curpos-stusize, ios::beg) ;
                edit.read((char*)& pr, sizeof(pr)) ;
                tc++;
                if(tc==1)   cout <<"Pruduct\t\tquantity\tprice\n\n";
                cout << pr.name <<"\t\t"<< pr.num <<"\t\t"<< pr.price <<"\n\n";
                found = true ;
            }  edit.read((char*)& pr , sizeof(pr)) ;
        } if(!found) cout << "product not found!\n\n";
        edit.close() ;
    }   else cout <<"Can't Access store file\n\n";
    for (size_t i = 0; i < 40; i++) cout<<"*";
     cout <<"\n\n";
}
void deleted_product(){
    Goods pr; ifstream fin;
    ofstream fout;  char str[10] ;
    cout << "Enter a name of pruduct to deleted : ";
    cin >> str;  cout <<"\n";  bool found = false;
    fin.open("store.txt", ios::in);
    fout.open("tmp.txt",ios::out) ;
    if(fin.is_open()){
        fin.read((char*)& pr, sizeof(pr)) ;
        while(!fin.eof()) {
            if(strcmp(str, pr.name) != 0) fout.write((char*)& pr , sizeof(pr));
            if(strcmp(str, pr.name)==0) found = true;
            fin.read((char*)& pr , sizeof(pr));
        }
        if(!found) cout <<"product not found !\n\n";
        else cout <<"product delete successfly !\n\n";
        fin.close();
        fout.close();
        remove("store.txt") ;
        rename("tmp.txt","store.txt") ;
    } else cout <<"Can't Access store file\n\n";
    for (size_t i = 0; i < 40; i++) cout<<"*";
    cout <<"\n\n";
}
int main(void) {
    cout <<"Hello, vendor !\nWelecome to store management system\n\n";
    for (size_t i = 0; i < 40; i++) cout<<"*";
    cout <<"\n\n";
    cout <<"What do you want to do\n\n";
    char s; do { int n;
          cout <<"1.add product to store ?!\n\n";
          cout <<"2.show all product on the store ?!\n\n";
          cout <<"3.search for product on the store ?!\n\n";
          cout <<"4.edit product on the store ?!\n\n";
          cout <<"5.delet product from store ?!\n\n";
          cout <<"Plesce Enter number of your option: ";
          cin >> n; cout <<"\n";
          if(n==1) add_to_store();
          else if (n==2) Show_store();  
          else if (n==3) search_on_store();
          else if (n==4) edit_store();
          else if (n==5) deleted_product();
          else cout <<"wrong option !\n";
          cout <<"Do you want to do another action:(y/n)  ";
          cin >> s;
          for (size_t i = 0; i < 40; i++) cout<<"-";
          cout <<"\n\n";
    } while (s == 'y');
    cout <<"Thank you for using our system, Good luck !\n";
}
