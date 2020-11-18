#pragma once
class ErrnoTranslatorTests;

class ErrnoTranslator
{
   friend class ::ErrnoTranslatorTests;
private:
   std::function<const char* (int)> _call_strerror;
public:
   ErrnoTranslator();
   virtual ~ErrnoTranslator() = default;
   virtual string ToReadable(int errnoValue);
};
