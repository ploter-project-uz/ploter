class G0: public Command
{
private:
  float x;
  float y;
  float z;

public:
  //jezeli jakis parametr ma miec wartosc domyslna inna niz 0 nalezy wywolac 
  //konstruktor i zainicijalizowac pole

  void validator(vector<string> token, int n) {

    //wszystkie dopuszczalne parametry
    allParametrs((char*)"xyz", token, n);

    //wymagane parametry, w tym wypadku x lub y, jezeli maja byc wymagane x i y to
    //nalezy wywolac funkcje dwukrotnie, najpierw z 'x', a pozniej z 'y'
    requiredParametr((char*)"xy", token, n); 
  }

  void createCommand(vector<string> token) {
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
  void validator(vector<string> token, int n) {
    allParametrs((char*)"xyzr", token, n);
    requiredParametr((char*)"xy", token, n);
    requiredParametr((char*)"r", token, n);
  }
  
  void createCommand(vector<string> token) {
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
  void validator(vector<string> token, int n) {
    allParametrs((char*)"xyzr", token, n);
    requiredParametr((char*)"xy", token, n);
    requiredParametr((char*)"r", token, n);  
  }
  
  void createCommand(vector<string> token) {
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

Command* Factory::getCommand(string token, int n) 
{
  string ss = "Nieznane polecenie: " + token + " w linii nr " + std::to_string(n+1) + "\n";

  if(token.size() > 3) {
    cout << ss;
    exit(1);
  }
  int number = atoi(&token[1]);
  if(tolower(token[0]) == 'g') {   
    switch (number) {
      case 0:
        return new G0;
        break;
      case 2:
        return new G2;
        break;
      case 3:
        return new G3;
        break;
      default:
        cout << ss;
        exit(1);
    }
  }
  else if(tolower(token[0]) == 'm') {
    switch (number) {
      default:
        cout << ss;
        exit(1);
    }
  }
  else {
    cout << ss;
    exit(1);
  }
}


