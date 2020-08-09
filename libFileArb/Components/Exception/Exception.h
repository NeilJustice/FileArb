#pragma once

namespace Utils
{
	class Exception
	{
	public:
		static string ClassNameAndWhat(const exception* e);
	};
}
