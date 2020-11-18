#pragma once
class Asserter;
class ErrnoTranslatorTests;

class ErrnoTranslator
{
   friend class ::ErrnoTranslatorTests;
private:
   // Function Callers
   using errno_t_FunctionType = errno_t(*)(char*, size_t, int);
   std::function<errno_t(char*, size_t, int)> _call_strerror_s;
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   ErrnoTranslator();
   virtual ~ErrnoTranslator();
   virtual string ErrnoValueToErrnoDescription(int errnoValue) const;
};
