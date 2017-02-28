#include "commands.hpp"

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
  string buf;
  getline(fin, buf);
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
  float m_x;
  float m_y;
  float m_z;

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
    map<char, float> parameters;
    parameters = initialize(token); //pobieramy tablice asocjacyjna 
    m_x = parameters['x'];            
    m_y = parameters['y'];           //jezeli jakis parametr ma miec inna wartosc domyslna
    m_z = parameters['z'];           //niz 0 to jego przypisanie umieszczamy 
                             //w  if(parameters.find('[nazwa_pola]') != parameters.end()) 
  }

  void execute() {
    cout << "G00 X=" << m_x << " Y=" << m_y << " Z=" << m_z << endl;
  }
};


class G2 : public Command 
{
private:
  float m_x;
  float m_y;
  float m_z;
  float m_r;

public:
  void validate(const vector<string> &token, int n) {
    testAllParameters((char*)"xyzr", token, n);
    testRequiredParameter((char*)"xy", token, n);
    testRequiredParameter((char*)"r", token, n);
  }
  
  void createCommand(const vector<string> &token) {
    map<char, float> parameters;
    parameters = initialize(token);
    m_x = parameters['x'];
    m_y = parameters['y'];
    m_z = parameters['z'];
    m_r = parameters['r'];
  }
  
  void execute() {
    cout << "G02 X=" << m_x << " Y=" << m_y << " Z=" << m_z << " R=" << m_r << endl; 
  }
};


class G3 : public Command 
{
private:
  float m_x;
  float m_y;
  float m_z;
  float m_r;

public:
  void validate(const vector<string> &token, int n) {
    testAllParameters((char*)"xyzr", token, n);
    testRequiredParameter((char*)"xy", token, n);
    testRequiredParameter((char*)"r", token, n);  
  }
  
  void createCommand(const vector<string> &token) {
    map<char, float> parameters;
    parameters = initialize(token);
    m_x = parameters['x'];
    m_y = parameters['y'];
    m_z = parameters['z'];
    m_r = parameters['r'];
  }
  void execute() {
    cout << "G03 X=" << m_x << " Y=" << m_y << " Z=" << m_z << " R=" << m_r << endl;
  }
};


//shared_ptr<Command>
Command::SPtr Factory::getCommand(const string &token, int n) 
{
  //std::unique_ptr<Command> UPtr;
  string ss = "Unknown command " + token + " in line number ";

  if(token.size() > COMMAND_SIZE) {
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


