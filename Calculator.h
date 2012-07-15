#include "CalClient.h"
class Calculator : public ICalClientCallback
{
  public:
    Calculator();
    Calculator(CalClient *_client);
    ~Calculator();
    void input(std:string ch);
    std::string getDisplayText();

    // interface ICalClientCallback
    virtual void responseWithResult(std:string res);

  private:
    std::string m_displayText;
    std::string m_op;
    int m_operand;
    CalClient *m_client;
}
