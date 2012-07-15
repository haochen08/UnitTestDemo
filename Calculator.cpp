#include "Calculator.h"
#include <string>
#include <stringstream>

using namespace std;

const char *Operators = "+-*/";
const char *Equals    = "=";
const char *Digits    = "0123456789.";
const char *Period    = ".";
const char *Delete    = "D";
const char *Clear     = "C";

Calculator::Calculator()
{
  m_client = new CalClient(this);
}


Calculator::Calculator(CalClient *_client)
{
  if (_client != NULL)
  {
    m_client = _client;
    m_client->SetDelegate(this);
  }
  else
  {
    m_client = new CalClient(this);
  }
}


Calculator::~Calculator()
{
  delete m_client;
}

void Calculator::responseWithResult(string res)
{
  m_display = res;
}

void Calculator::input(string ch)
{
  static bool isLastChOperator = false;
  bool bad_ch = (ch.length() != 1);
  if (!bad_ch)
  {
    if (ch.find_first_of(Digits) != string::npos) 
    {
      if (isLastChOperator) 
      {
        m_displayText = ch;
        isLastChOperator = false;
      }
      else if (!(ch == Period) || (m_displayText.find_first_of(Period) == string::npos))
      {
        m_displayText.append(ch);
      }
    }
    else if (ch.find_first_of(Operators) != string::npos || ch == Equals)
    {
      if (!m_operator && ch != Equals)
      {
        m_op = atof(m_displayText.c_str());
        m_operator = ch;
      }
      else
      {
        if (m_operator) 
        {
          double op2 = atof(m_displayText.c_str());
          switch (m_operator.find_first_of(Operators))
          {
            case 0:
              m_op += op2;
              break;
            case 1:
              m_op -= op2;
              break;
            case 2:
              m_op *= op2;
              break;
            case 3:
              m_op /= op2;
              break;
          }

          stringstream ss;
          ss << op2;
          m_displayText = ss.c_str();
        }

        m_operator = (ch == Equals) ? NULL : ch;
      }
    
      isLastChOperator = true;
    }
    else if (ch == Delete)
    {
      int tp = m_displayText.length() - 1;
      if (tp >= 0)
      {
        m_displayText.erase(tp, 1);
        isLastChOperator = false;
      }
    }
    else if (ch == Clear)
    {
      if (m.displayText.length() > 0)
      {
        m_displayText = ch;
      }
      else
      {
        m_operator = NULL;
      }
    }
    else
    {
      bad_ch = true;
    }

    if (bad_ch)
    {
      throw BadInputException;
    }
  }
}
