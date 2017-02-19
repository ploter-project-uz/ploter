#include "commands.hpp"
#include "commands.cpp"

void Parser::parser(ifstream &fin, int line)
{
  char buf[MAX_CHARS_PER_LINE];
  fin.getline(buf, MAX_CHARS_PER_LINE);
  split(token, buf, is_any_of(DELIMITER), token_compress_on); //tworzymy tokeny
  if(token.back() == "") //jezeli na koncu linii sa dodatkowe spacje, usuwamy ostatni token ktory jest pusty
    token.pop_back();

  //sprawdzamy czy wartosci parametrow nie zawieraja liter
  int j,i;
  for(i = 0; i < token.size(); i++) {
    for(j = 1; j < token[i].size(); j++) {
      if(!isdigit(token[i][j]) && token[i][j] != '.') {
        cout << "Nieprawidlowa wartosc: " << token[i] << " w linii nr " << line+1 << endl;
        exit(1);
      }
    }
  }
}

vector<string> Parser::getCopyOfVector() 
{
  return token;
}




void Command::allParametrs(char* parametrs, vector<string> token, int n)
{
  //jezeli podano nieprawidlowy parametr, wypisujemy blad
  char *pch;
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));
    if(pch == NULL) {
      cout << "Nieznany parametr: " << token[i] << " w linii nr: " << n+1 << endl;
      exit(1);
    }
  }
}


void Command::requiredParametr(char* parametrs, vector<string> token, int n)
{
  //jezeli nie podano wymaganego parametru, wypisujemy blad
  char *pch;
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));
    if(pch != NULL) {
      return;
    }
  }
  cout << "Brak wymaganych parametrow w linii nr: " << n+1 << endl;
  exit(1);
}


map<char,float> Command::initialize(vector<string> token)
{
  map<char, float> mapa;
  for(int i = 1; i < token.size(); i++) {
    mapa[tolower(token[i][0])] = atof(&token[i][1]);
  }
  return mapa;
}


int main() {
  ifstream fin;
  vector<string> token;
  int n = 0;
  vector<Command*> polecenie;
  Parser tokenizer;
  fin.open("gcode.txt");
  if(!fin.good())
    return 1;

  while(true) {
    tokenizer.parser(fin, n);
    if(fin.eof()) break;
    token = tokenizer.getCopyOfVector();
    polecenie.push_back(Factory::getCommand(token[0],n)); 
    polecenie[n]->validator(token, n); 
    polecenie[n]->createCommand(token);
    n++;
  }
 
  for(int i = 0; i < polecenie.size(); i++)
    polecenie[i]->execute();
}



