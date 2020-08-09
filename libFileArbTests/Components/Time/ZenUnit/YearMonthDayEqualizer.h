#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<date::year_month_day>
   {
      static void AssertEqual(
         const date::year_month_day& expectedYearMonthDay,
         const date::year_month_day& actualYearMonthDay)
      {
         ARE_EQUAL(expectedYearMonthDay.year(), actualYearMonthDay.year());
         ARE_EQUAL(expectedYearMonthDay.month(), actualYearMonthDay.month());
         ARE_EQUAL(expectedYearMonthDay.day(), actualYearMonthDay.day());
      }
   };
}
