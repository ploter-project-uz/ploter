void Command::testAllParameters(char* parametrs, const vector<string> &token, int n)
{
  //jezeli podano nieprawidlowy parametr, wypisujemy blad
  char *pch;
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));
    if(pch == NULL) {
      cout << "Unknown parameter: " << token[i] << " in line number " << n+1 << endl;
      exit(1);
    }
  }
}


int Command::testRequiredParameter(char* parametrs, const vector<string> &token, int n)
{
  //jezeli nie podano wymaganego parametru, wypisujemy blad
  char *pch;
  for(int i = 1; i < token.size(); i++) {
    pch = strchr(parametrs, tolower(token[i][0]));
    if(pch != NULL) {
      return 0;
    }
  }
  cout << "Required parameters in line number " << n+1 << " not found" << endl;
  exit(1);
}


map<char,float> Command::initialize(const vector<string> &token)
{
  map<char, float> mapa;
  for(int i = 1; i < token.size(); i++) {
    mapa[tolower(token[i][0])] = atof(&token[i][1]);
  }
  return mapa;
}



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
        string error = "Invalid value: " + token[i] + " in line number: ";
        throw error;
      }
    }
  }
}

vector<string> Parser::getCopyOfVector() 
{
  return token;
}


class G0: public Command
{
private:
  float x;
  float y;
  float z;

public:
  //jezeli jakis parametr ma miec wartosc domyslna inna niz 0 nalezy wywolac 
  //konstruktor i zainicijalizowac pole

  void validate(const vector<string> &token, int n) {

    //wszystkie dopuszczalne parametry
    testAllParameters((char*)"xyz", token, n);

    //wymagane parametry, w tym wypadku x lub y, jezeli maja byc wymagane x i y to
    //nalezy wywolac funkcje dwukrotnie, najpierw z 'x', a pozniej z 'y'
    testRequiredParameter((char*)"xy", token, n); 
  }

  void createCommand(const vector<string> &token) {
    map<char, float> mapa;
    mapa = initialize(token); //pobieramy tablice asocjacyjna 
    x = mapa['x'];            
    y = mapa['y'];           //jezeli jakis parametr ma miec inna wartosc domyslna
    z = mapa['z'];           //niz 0 to jego przypisanie umieszczamy 
                             //w  if(mapa.find('[nazwa_pola]') != mapa.end()) 
  }

  void execute() {
    cout << "G00 X=" << x << " Y=" << y << " Z=" << z << endl;
  }
};


class G2 : public Command 
{
private:
  float x;
  float y;
  float z;
  float r;

public:
  void validate(const vector<string> &token, int n) {
    testAllParameters((char*)"xyzr", token, n);
    testRequiredParameter((char*)"xy", token, n);
    testRequiredParameter((char*)"r", token, n);
  }
  
  void createCommand(const vector<string> &token) {
    map<char, float> mapa;
    mapa = initialize(token);
    x = mapa['x'];
    y = mapa['y'];
    z = mapa['z'];
    r = mapa['r'];
  }
  
  void execute() {
    cout << "G02 X=" << x << " Y=" << y << " Z=" << z << " R=" << r << endl; 
  }
  friend class G3;
};


class G3 : public Command 
{
private:
  float x;
  float y;
  float z;
  float r;

public:
  void validate(const vector<string> &token, int n) {
    testAllParameters((char*)"xyzr", token, n);
    testRequiredParameter((char*)"xy", token, n);
    testRequiredParameter((char*)"r", token, n);  
  }
  
  void createCommand(const vector<string> &token) {
    map<char, float> mapa;
    mapa = initialize(token);
    x = mapa['x'];
    y = mapa['y'];
    z = mapa['z'];
    r = mapa['r'];
  }
  void execute() {
    cout << "G03 X=" << x << " Y=" << y << " Z=" << z << " R=" << r << endl;
  }
};


//shared_ptr<Command>
Command::SPtr Factory::getCommand(const string &token, int n) 
{
  //std::unique_ptr<Command> UPtr;
  string ss = "Unknown command " + token + " in line number ";

  if(token.size() > 3) {
    cout << ss << n+1 << endl;
    exit(1);
  }
  int number = atoi(&token[1]);
  if(tolower(token[0]) == 'g') {   
    switch (number) {
      case 0:
        //return new G0;
        return make_shared<G0>();
        break;
      case 2:
        //return new G2;
        return make_shared<G2>();
        break;
      case 3:
        //return new G3;
        return make_shared<G3>();
        break;
      default:
        cout << ss << n+1 << endl;
        exit(1);
    }
  }
  else if(tolower(token[0]) == 'm') {
    switch (number) {
      default:
        cout << ss << n+1 << endl;
        exit(1);
    }
  }
  else {
    cout << ss << n+1 << endl;
    exit(1);
  }
}


