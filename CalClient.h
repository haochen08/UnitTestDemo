class ICalClientCallback;
class CalClient
{
  public:
  CalClient(ICalClientCallback *delegate);
  ~CalClient();

  void setDelegate(ICalClientCallback *delegate) { m_delegate = delegate; }
  void calculate(int p1, int p2, std::string op);

  private:
  ICalClientCallback *m_delegate;
};

class ICalClientCallback
{
  public:
  virtual void responseWithResult(std::string res) = 0;
}
