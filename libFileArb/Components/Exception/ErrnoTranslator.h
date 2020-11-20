#pragma once
class Asserter;
class ErrnoTranslatorTests;

class ErrnoTranslator
{
   friend class ::ErrnoTranslatorTests;
private:
   // Function Callers
#ifdef __linux__

#elif _WIN32
   using strerror_s_FunctionType = errno_t(*)(char*, size_t, int);
   std::function<errno_t(char*, size_t, int)> _call_strerror_s;
#endif
   // Constant Components
   unique_ptr<const Asserter> _asserter;
public:
   ErrnoTranslator();
   virtual ~ErrnoTranslator();
   virtual string ErrnoValueToErrnoDescription(int errnoValue) const;
};
