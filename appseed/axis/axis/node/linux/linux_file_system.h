#pragma once


namespace linux
{



   class CLASS_DECL_LINUX file_system :
      public ::file::system
   {
   public:


      class CLASS_DECL_LINUX path :
        public ::file::system::path
      {
      public:
         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);
      };

      class file_system::path m_path;


      file_system(sp(::axis::application) papp);

      path & path();

      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, sp(::axis::application) app);
      virtual void move(const char * pszNew, const char * psz);
      virtual void del(const char * psz);
      virtual string copy(const char * psz, sp(::axis::application) papp);
      virtual string paste(const char * pszLocation, const char * path, sp(::axis::application) papp);

      virtual void trash_that_is_not_trash(const char * psz, sp(::axis::application) papp);
      virtual void trash_that_is_not_trash(stringa & stra, sp(::axis::application) papp);

      virtual string title_(const char * path);
      virtual string name_(const char * path);
      virtual string extension(const char * path);

      virtual var length(const char * path);

      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, sp(::axis::application) papp);

      virtual bool exists(const char * path, sp(::axis::application) papp);
      virtual bool exists(const string & path, sp(::axis::application) papp);

      void  get_ascendants_path(const char * lpcsz, stringa & stra);
      void  get_ascendants_name(const char * lpcsz, stringa & stra);


      string time(sp(::axis::application) papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(sp(::axis::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(sp(::axis::application) papp, const char * pszId);

      virtual ::file::buffer_sp time_square_file(sp(::axis::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::file::buffer_sp get(const char * name, sp(::axis::application) papp);


      int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      bool mk_time(const char * lpcszcandidate);

      string as_string(var varFile, sp(::axis::application) papp);
      string as_string(var varFile, var & varQuery, sp(::axis::application) papp);
      void as_memory(var varFile, primitive::memory_base & mem, sp(::axis::application) papp);
      void lines(stringa & stra, var varFile, sp(::axis::application) papp);

      bool put_contents(var varFile, const void * pvoidContents, count count, sp(::axis::application) papp);
      bool put_contents(var varFile, const char * lpcszContents, sp(::axis::application) papp);
      bool put_contents(var varFile, ::file::reader & reader, sp(::axis::application) papp);
      bool put_contents(var varFile, primitive::memory & mem, sp(::axis::application) papp);
      bool put_contents_utf8(var varFile, const char * lpcszContents, sp(::axis::application) papp);

      bool is_read_only(const char * psz);

      string sys_temp(const char * pszName, const char * pszExtension, sp(::axis::application) papp);
      string sys_temp_unique(const char * pszName);


      string replace_extension(const char * pszFile, const char * pszExtension);
      void set_extension(string & str, const char * pszExtension);


   };


} // namespace ca2


