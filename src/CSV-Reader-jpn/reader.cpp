#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ifstream ip("sentences.txt");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

  string id1;
  string id2;
  string jpnSentence;
  string engSentence;
  string jpnReading;

  while(ip.good()){

    getline(ip,id1,'\t');
    getline(ip,id2,'\t');
    getline(ip,jpnSentence,'\t');
    getline(ip,engSentence,'\t');
    getline(ip,jpnReading,'\n');

    std::cout << "ID: "<<id1<< " "<<id2 << '\n';
    std::cout << "Japanese: "<<jpnSentence << '\n';
    std::cout << "English: "<<engSentence << '\n';
    std::cout << "Reading: "<<jpnReading << '\n';
    std::cout << "-------------------" << '\n';
  }

  ip.close();
}
