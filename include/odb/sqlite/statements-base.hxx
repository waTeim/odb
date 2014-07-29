// file      : odb/sqlite/statements-base.hxx
// copyright : Copyright (c) 2005-2013 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_STATEMENTS_BASE_HXX
#define ODB_SQLITE_STATEMENTS_BASE_HXX

#include <odb/pre.hxx>

#include <odb/details/shared-ptr.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx> // connection

#include <odb/sqlite/details/export.hxx>

namespace odb
{
  namespace sqlite
  {
    class LIBODB_SQLITE_EXPORT statements_base: public details::shared_base
    {
    public:
      typedef sqlite::connection connection_type;

      connection_type&
      connection ()
      {
        return conn_;
      }

    public:
      virtual
      ~statements_base ();

    protected:
      statements_base (connection_type& conn)
        : conn_ (conn)
      {
      }

    protected:
      connection_type& conn_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_SQLITE_STATEMENTS_BASE_HXX
