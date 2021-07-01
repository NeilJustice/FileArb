#pragma once
class FCloseDeleterTests;

class FCloseDeleter
{
   friend class FCloseDeleterTests;
private:
   // Function Pointers
   function<int(FILE*)> _call_fclose;
public:
   FCloseDeleter();
   void operator()(FILE* rawFilePointer) const;
};
