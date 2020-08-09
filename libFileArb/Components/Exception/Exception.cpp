#include "pch.h"
#include "libFileArb/Components/Exception/Exception.h"
#include "libFileArb/Components/Misc/Type.h"

namespace Utils
{
	string Exception::ClassNameAndWhat(const exception* e)
	{
      const string classNameAndWhat = *Type::GetName(*e) + ": " + e->what();
		return classNameAndWhat;
	}
}
