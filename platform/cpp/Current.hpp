class Current
{
private:
  
  float m_x;    //wspolrzedne
  float m_y;    //

  int m_z;
  
public:

  Current();
  
  int checkX(float x, int line);   //sprawdzamy czy
  int checkY(float y, int line);   //nie przekroczono zakresu

  float getX();
  float getY();
  int   getZ();
  
  void setX(float x);
  void setY(float y);
  void setZ(int z);
  
  void setCurrent(float x, float y);

  void reset();
  
};
