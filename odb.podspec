Pod::Spec.new do |s|
  s.name         = "odb"
  s.version      = "2.2.2"
  s.summary      = "A C++ Object-Relational Mapping"
  s.description  = <<-DESC
                   ODB is an open-source, cross-platform, and cross-database
                   object-relational mapping (ORM) system for C++. It allows you to
                   persist C++ objects to a relational database without having to
                   deal with tables, columns, or SQL and without manually writing
                   any mapping code. ODB supports MySQL, SQLite, PostgreSQL,
                   Oracle, and Microsoft SQL Server relational databases as well
                   as C++98/03 and C++11 language standards. It also comes with
                   optional profiles for Boost and Qt which allow you to seamlessly
                   use value types, containers, and smart pointers from these
                   libraries in your persistent C++ classes. 
                   DESC
  s.homepage     = "http://www.codesynthesis.com/products/odb"
  s.license      = 'GPL2'
  s.author       = { "waTeim" => "truthset@gmail.com" }
  s.source       = { :git => "https://github.com/waTeim/odb.git", :tag => s.version.to_s }
  s.platform     = :osx, '10.6'
  s.requires_arc = false
  s.vendored_libraries = 'lib/*.a'
  s.source_files = 'src/*.h'
  s.public_header_files = 'include/**/*.{h,hxx,txx,ixx}'
  s.preserve_paths = 'src','include','include/compilers','include/compilers/vc','include/details','include/details/meta','include/details/posix','include/details/shared-ptr','include/tr1'
end
