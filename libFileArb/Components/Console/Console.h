#pragma once
class ConsoleTests;

namespace Utils
{
	class Console
	{
      friend class ::ConsoleTests;
	public:
      virtual ~Console();
		virtual void Write(string_view message) const;
		virtual void Write(int value) const;
		virtual void WriteLine() const;
		virtual void WriteLine(int value) const;
		virtual void WriteLine(string_view message) const;
	};
}
