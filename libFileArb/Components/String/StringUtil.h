#pragma once

namespace Utils
{
	class String
	{
	public:
      static bool ContainsSubstring(std::string_view stringView, std::string_view substring);
      static bool CaseInsensitiveContainsSubstring(std::string_view stringView, std::string_view substring);

      template<typename T, typename... Ts>
		static std::string Concat(const T& value, const Ts&... values)
		{
			std::ostringstream oss;
			oss << value;
			DoConcat(&oss, values...);
         const std::string result = oss.str();
			return result;
		}

      template<typename T, typename... Ts>
		static void DoConcat(std::ostringstream* outOss, const T& value, const Ts&... values)
		{
			(*outOss) << value;
			DoConcat(outOss, values...);
		}

      template<typename T, typename... Ts>
		static void DoConcat(std::ostringstream* outOss, const T& value)
		{
			(*outOss) << value;
		}

		template<typename... T>
		static void DoConcat(std::ostringstream*)
		{
		}
   private:
      static std::string ToAllLowercase(std::string_view str);
	};
}
