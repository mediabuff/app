#pragma once



typedef uint64_t  file_size;
typedef uint64_t  file_position;
typedef int64_t   file_offset;



class simple_memory;


CLASS_DECL_ca bool file_exists_dup(const char * path1);
#ifdef WINDOWS
CLASS_DECL_ca bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif
CLASS_DECL_ca vsstring get_file_md5(const char * file);
CLASS_DECL_ca bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_ca bool file_put_contents_dup(const char * path, const char * contents, ::count len = -1);
CLASS_DECL_ca bool file_put_contents_dup(const char * path, const simple_memory & memory);
CLASS_DECL_ca bool file_get_memory_dup(simple_memory & memory, const char * path);
CLASS_DECL_ca bool get_temp_file_name_dup(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_ca bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_ca uint64_t file_length_dup(const char * path);

CLASS_DECL_ca vsstring file_title_dup(const char * path);
CLASS_DECL_ca vsstring file_name_dup(const char * path);
CLASS_DECL_ca vsstring file_module_path_dup();


CLASS_DECL_ca bool file_is_equal_path(const char * pszPath1, const char * pszPath2);


CLASS_DECL_ca bool file_ftd_dup(const char * pszDir, const char * pszFile);
#ifdef WINDOWS
CLASS_DECL_ca void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_ca void file_read_gen_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str);
#else
CLASS_DECL_ca void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_ca void file_read_gen_string_dup(FILE * hfile, ::md5::md5 * pctx, vsstring & str);
#endif


#ifndef METROWIN
CLASS_DECL_ca bool PrintModules(vsstring & strImage, uint32_t processID, const char * pszDll );
CLASS_DECL_ca void dll_processes(simple_uint_array & dwa, stra_dup & straProcesses, const char * pszDll);
#endif

CLASS_DECL_ca bool file_copy_dup(const char * pszDup, const char * pszSrc, bool bOverwrite = true);


CLASS_DECL_ca void sprint_hex(char * sz, int32_t iValue);




CLASS_DECL_ca vsstring file_get_mozilla_firefox_plugin_container_path();


typedef HANDLE handle;

CLASS_DECL_ca handle create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_ca bool close_handle(handle h);
CLASS_DECL_ca vsstring get_sys_temp_path();


BEGIN_EXTERN_C


#ifdef WINDOWS

struct CLASS_DECL_ca _struct_FILE
{
   char *_ptr;
   int32_t   _cnt;
   char *_base;			//	Used to store HANDLE
   int32_t   _flag;
   int32_t   _file;
   int32_t   _charbuf;
   int32_t   _bufsiz;
   char *_tmpfname;
   int32_t   _err;
};

#define _FILE struct _struct_FILE

#define EOF (-1)
#define _FILE_TEXT		0x0001
#define _FILE_EOF		0x0002
#define _FILE_ERROR		0x0004


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  (&__iob_func_dup()[0])
#define stdout_dup (&__iob_func_dup()[1])
#define stderr_dup (&__iob_func_dup()[2])
#define _STDSTREAM_DUP_DEFINED
#endif
CLASS_DECL_ca _FILE *__iob_func_dup();

#else
#define _FILE FILE


#define EOF (-1)
#define _FILE_TEXT		FILE_TEXT
#define _FILE_EOF		FILE_EOF
#define _FILE_ERROR		FILE_ERROR


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  stdin
#define stdout_dup stdout
#define stderr_dup stderr
#define _STDSTREAM_DUP_DEFINED
#endif

#endif


CLASS_DECL_ca void _init_file_dup();

CLASS_DECL_ca _FILE * fopen_dup(const char *path, const char *attrs);
CLASS_DECL_ca int32_t fprintf_dup(_FILE *fp, const char *s, ...);
CLASS_DECL_ca int32_t fclose_dup(_FILE *fp);
CLASS_DECL_ca int32_t feof_dup(_FILE *fp);
CLASS_DECL_ca file_position fseek_dup(_FILE *str, file_offset offset, int32_t origin);
CLASS_DECL_ca long ftell_dup(_FILE *fp);
CLASS_DECL_ca size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_ca size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_ca char *fgets_dup(char *str, int32_t n, _FILE *s);
CLASS_DECL_ca int32_t fgetc_dup(_FILE *s);
CLASS_DECL_ca int32_t ungetc_dup(int32_t c,_FILE *s);
CLASS_DECL_ca int32_t ferror_dup(_FILE *s);
CLASS_DECL_ca int32_t fflush_dup(_FILE *s);


#ifdef WINDOWS
CLASS_DECL_ca _FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs);
CLASS_DECL_ca int32_t fwprintf_dup(_FILE *fp, const wchar_t *s, ...);
CLASS_DECL_ca wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s);
CLASS_DECL_ca wint_t fgetwc_dup(_FILE *s);
CLASS_DECL_ca wint_t ungetwc_dup(wint_t w, _FILE *s);
#endif


#ifdef WINDOWS
uint64_t fsize_dup(HANDLE h);
#else
uint64_t fsize_dup(FILE * fp);
#endif

END_EXTERN_C

