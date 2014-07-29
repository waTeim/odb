// file      : odb/sqlite/statement.hxx
// copyright : Copyright (c) 2005-2013 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_SQLITE_STATEMENT_HXX
#define ODB_SQLITE_STATEMENT_HXX

#include <odb/pre.hxx>

#include <sqlite3.h>

#include <string>
#include <cstddef> // std::size_t
#include <cstring> // std::strlen, std::memcpy
#include <cassert>

#include <odb/statement.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/auto-handle.hxx>

#include <odb/sqlite/details/export.hxx>

namespace odb
{
  namespace sqlite
  {
    class connection;

    class LIBODB_SQLITE_EXPORT statement: public odb::statement
    {
    public:
      typedef sqlite::connection connection_type;

      virtual
      ~statement () = 0;

      sqlite3_stmt*
      handle () const
      {
        return stmt_;
      }

      virtual const char*
      text () const;

      virtual connection_type&
      connection ()
      {
        return conn_;
      }

    protected:
      statement (connection_type& conn, const std::string& text)
        : conn_ (conn)
      {
        init (text.c_str (), text.size ());
      }

      statement (connection_type& conn, const char* text)
        : conn_ (conn)
      {
        init (text, std::strlen (text));
      }

      statement (connection_type& conn,
                 const char* text,
                 std::size_t text_size)
        : conn_ (conn)
      {
        init (text, text_size);
      }

    protected:
      void
      bind_param (const bind*, std::size_t count);

      // Extract row columns into the bound buffers. If the truncated
      // argument is true, then only truncated columns are extracted.
      // Return true if all the data was extracted successfully and
      // false if one or more columns were truncated.
      //
      bool
      bind_result (const bind*, std::size_t count, bool truncated = false);

      // Active state.
      //
    protected:
      bool
      active () const
      {
        return active_;
      }

      void
      active (bool active)
      {
        assert (active);

        if (!active_)
        {
          list_add ();
          active_ = true;
        }
      }

      void
      reset ()
      {
        if (active_)
        {
          sqlite3_reset (stmt_);
          list_remove ();
          active_ = false;
        }
      }

    protected:
      friend class sqlite::connection;

      connection_type& conn_;
      auto_handle<sqlite3_stmt> stmt_;

      bool active_;

    private:
      void
      init (const char* text, std::size_t text_size);

      // Doubly-linked list of active statements.
      //
    private:
      void
      list_add ()
      {
        next_ = conn_.statements_;
        conn_.statements_ = this;

        if (next_ != 0)
          next_->prev_ = this;
      }

      void
      list_remove ()
      {
        (prev_ == 0 ? conn_.statements_ : prev_->next_) = next_;

        if (next_ != 0)
          next_->prev_ = prev_;

        prev_ = 0;
        next_ = this;
      }

      // prev_ == 0 means we are the first element.
      // next_ == 0 means we are the last element.
      // next_ == this means we are not on the list (prev_ should be 0).
      //
      statement* prev_;
      statement* next_;
    };

    class LIBODB_SQLITE_EXPORT generic_statement: public statement
    {
    public:
      generic_statement (connection_type&, const std::string& text);
      generic_statement (connection_type&, const char* text);
      generic_statement (connection_type&,
                         const char* text,
                         std::size_t text_size);

      unsigned long long
      execute ();

    private:
      generic_statement (const generic_statement&);
      generic_statement& operator= (const generic_statement&);

    private:
      bool result_set_;
    };

    class LIBODB_SQLITE_EXPORT select_statement: public statement
    {
    public:
      select_statement (connection_type& conn,
                        const std::string& text,
                        binding& param,
                        binding& result);

      select_statement (connection_type& conn,
                        const char* text,
                        binding& param,
                        binding& result);

      select_statement (connection_type& conn,
                        const std::string& text,
                        binding& result);

      select_statement (connection_type& conn,
                        const char* text,
                        binding& result);

      // Common select interface expected by the generated code.
      //
    public:
      enum result
      {
        success,
        no_data,
        truncated
      };

      void
      execute ();

      // Load next row columns into bound buffers.
      //
      result
      fetch ()
      {
        return next () ? load () : no_data;
      }

      // Reload truncated columns into bound buffers.
      //
      void
      refetch ()
      {
        reload ();
      }

      // Free the result set.
      //
      void
      free_result ();

      // More fine-grained SQLite-specific interface that splits fetch()
      // into next() and load().
      //
    public:
      // Return false if there is no more rows. You should call next()
      // until it returns false or, alternatively, call free_result ().
      // Otherwise the statement will remain unfinished.
      //
      bool
      next ();

      result
      load ();

      void
      reload ();

    private:
      select_statement (const select_statement&);
      select_statement& operator= (const select_statement&);

    private:
      bool done_;
      binding* param_;
      binding& result_;
    };

    struct LIBODB_SQLITE_EXPORT auto_result
    {
      explicit auto_result (select_statement& s): s_ (s) {}
      ~auto_result () {s_.free_result ();}

    private:
      auto_result (const auto_result&);
      auto_result& operator= (const auto_result&);

    private:
      select_statement& s_;
    };

    class LIBODB_SQLITE_EXPORT insert_statement: public statement
    {
    public:
      insert_statement (connection_type& conn,
                        const std::string& text,
                        binding& param);

      insert_statement (connection_type& conn,
                        const char* text,
                        binding& param);

      // Return true if successful and false if the row is a duplicate.
      // All other errors are reported by throwing exceptions.
      //
      bool
      execute ();

      unsigned long long
      id ();

    private:
      insert_statement (const insert_statement&);
      insert_statement& operator= (const insert_statement&);

    private:
      binding& param_;
    };

    class LIBODB_SQLITE_EXPORT update_statement: public statement
    {
    public:
      update_statement (connection_type& conn,
                        const std::string& text,
                        binding& param);

      update_statement (connection_type& conn,
                        const char* text,
                        binding& param);

      unsigned long long
      execute ();

    private:
      update_statement (const update_statement&);
      update_statement& operator= (const update_statement&);

    private:
      binding& param_;
    };

    class LIBODB_SQLITE_EXPORT delete_statement: public statement
    {
    public:
      delete_statement (connection_type& conn,
                        const std::string& text,
                        binding& param);

      delete_statement (connection_type& conn,
                        const char* text,
                        binding& param);

      unsigned long long
      execute ();

    private:
      delete_statement (const delete_statement&);
      delete_statement& operator= (const delete_statement&);

    private:
      binding& param_;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_SQLITE_STATEMENT_HXX
