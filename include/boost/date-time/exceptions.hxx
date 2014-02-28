// file      : odb/boost/date-time/exceptions.hxx
// copyright : Copyright (c) 2005-2013 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_BOOST_DATE_TIME_EXCEPTIONS_HXX
#define ODB_BOOST_DATE_TIME_EXCEPTIONS_HXX

#include <odb/pre.hxx>

#include <odb/boost/exception.hxx>
#include <odb/boost/details/export.hxx>

namespace odb
{
  namespace boost
  {
    namespace date_time
    {
      struct LIBODB_BOOST_EXPORT special_value: exception
      {
        virtual const char*
        what () const throw ();
      };

      struct LIBODB_BOOST_EXPORT value_out_of_range: exception
      {
        virtual const char*
        what () const throw ();
      };
    }
  }
}

#include <odb/post.hxx>

#endif // ODB_BOOST_DATE_TIME_EXCEPTIONS_HXX
