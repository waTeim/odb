// file      : odb/statement.hxx
// copyright : Copyright (c) 2005-2013 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_STATEMENT_HXX
#define ODB_STATEMENT_HXX

#include <odb/pre.hxx>

#include <odb/forward.hxx> // connection

#include <odb/details/export.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  class LIBODB_EXPORT statement: public details::shared_base
  {
  private:
    statement (const statement&);
    statement& operator= (const statement&);

  public:
    typedef odb::connection connection_type;

    virtual const char*
    text () const = 0;

    virtual connection_type&
    connection ()  = 0;

    virtual
    ~statement () = 0;

  protected:
    statement () {}
  };
}

#include <odb/post.hxx>

#endif // ODB_MYSQL_STATEMENT_HXX
