#pragma once

class String
{
public:
   static bool ContainsSubstring(string_view stringView, string_view substring);
   static bool CaseInsensitiveContainsSubstring(string_view stringView, string_view substring);
   static string ToLowercase(string_view str);
   static size_t ToSizeT(string_view str);

   template<typename... Types>
	static string ConcatStrings(Types&&... values)
	{
		string concatenatedString;
		string_view stringViews[] = { values... };
		size_t lengthOfAllStrings = 0;
		for (string_view stringView : stringViews)
		{
			const size_t stringViewSize = stringView.size();
			lengthOfAllStrings += stringViewSize;
		}
		concatenatedString.reserve(lengthOfAllStrings);
		for (string_view stringView : stringViews)
		{
			concatenatedString.append(stringView);
		}
		return concatenatedString;
	}

	template<typename... Types>
	static string ConcatValues(const Types&... values)
	{
		ostringstream oss;
		(oss << ... << values);
		string ossConcatenatedValues = oss.str();
		return ossConcatenatedValues;
	}

   String() = delete;
};
