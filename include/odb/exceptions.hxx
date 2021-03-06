// file      : odb/exceptions.hxx
// copyright : Copyright (c) 2009-2013 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_EXCEPTIONS_HXX
#define ODB_EXCEPTIONS_HXX

#include <odb/pre.hxx>

#include <string>

#include <odb/forward.hxx>    // odb::core
#include <odb/exception.hxx>

#include <odb/details/export.hxx>

namespace odb
{
  struct LIBODB_EXPORT null_pointer: exception
  {
    virtual const char*
    what () const throw ();
  };

  // Transaction exceptions.
  //
  struct LIBODB_EXPORT already_in_transaction: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT not_in_transaction: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT transaction_already_finalized: exception
  {
    virtual const char*
    what () const throw ();
  };

  // Session exceptions.
  //
  struct LIBODB_EXPORT already_in_session: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT not_in_session: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT session_required: exception
  {
    virtual const char*
    what () const throw ();
  };

  // Database operations exceptions.
  //
  struct LIBODB_EXPORT recoverable: exception
  {
  };

  struct LIBODB_EXPORT connection_lost: recoverable
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT timeout: recoverable
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT deadlock: recoverable
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT object_not_persistent: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT object_already_persistent: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT object_changed: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT result_not_cached: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT database_exception: exception
  {
  };

  // Polymorphism support exceptions.
  //
  struct LIBODB_EXPORT abstract_class: exception
  {
    virtual const char*
    what () const throw ();
  };

  struct LIBODB_EXPORT no_type_info: exception
  {
    virtual const char*
    what () const throw ();
  };

  // Prepared query support exceptions.
  //
  struct LIBODB_EXPORT prepared_already_cached: exception
  {
    prepared_already_cached (const char* name);
    ~prepared_already_cached () throw ();

    const char*
    name () const
    {
      return name_;
    }

    virtual const char*
    what () const throw ();

  private:
    const char* name_;
    std::string what_;
  };

  struct LIBODB_EXPORT prepared_type_mismatch: exception
  {
    prepared_type_mismatch (const char* name);
    ~prepared_type_mismatch () throw ();

    const char*
    name () const
    {
      return name_;
    }

    virtual const char*
    what () const throw ();

  private:
    const char* name_;
    std::string what_;
  };

  // Schema catalog exceptions.
  //
  struct LIBODB_EXPORT unknown_schema: exception
  {
    unknown_schema (const std::string& name);
    ~unknown_schema () throw ();

    const std::string&
    name () const
    {
      return name_;
    }

    virtual const char*
    what () const throw ();

  private:
    std::string name_;
    std::string what_;
  };

  namespace common
  {
    using odb::null_pointer;

    using odb::already_in_transaction;
    using odb::not_in_transaction;
    using odb::transaction_already_finalized;

    using odb::already_in_session;
    using odb::not_in_session;
    using odb::session_required;

    using odb::recoverable;
    using odb::deadlock;
    using odb::connection_lost;
    using odb::timeout;
    using odb::object_not_persistent;
    using odb::object_already_persistent;
    using odb::object_changed;
    using odb::result_not_cached;
    using odb::database_exception;

    using odb::abstract_class;
    using odb::no_type_info;

    using odb::unknown_schema;
  }
}

#include <odb/post.hxx>

#endif // ODB_EXCEPTIONS_HXX
