#include<string>

#include<vector>

class Current;
class StepperControl;

class G0: public Command
{
private:
  float m_x;
  float m_y;
  int m_z;

public:
  void validate(const std::vector<std::string> &token, int n);
  void createCommand(const std::vector<std::string> &token, Current *cordinate);
  void checkParameters(Current *cordinate, int line);
  void draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void execute(StepperControl *stepper, Current *cordinate);
};

class G2: public Command
{
private:
  float m_x;
  float m_y;
  int m_z;
  float m_i;
  float m_j;

public:
  void validate(const std::vector<std::string> &token, int n);
  void createCommand(const std::vector<std::string> &token, Current *cordinate);
  void checkParameters(Current *cordinate, int line);
  void draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void execute(StepperControl *stepper, Current *cordinate);
};

class G3: public Command
{
private:
  float m_x;
  float m_y;
  int m_z;
  float m_i;
  float m_j;

public:
  void validate(const std::vector<std::string> &token, int n);
  void createCommand(const std::vector<std::string> &token, Current *cordinate);
  void checkParameters(Current *cordinate, int line);
  void draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void execute(StepperControl *stepper, Current *cordinate);
};


