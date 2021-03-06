#include "framework.h"
//#include "macos.h"


#include <sys/stat.h>
#include <ctype.h>


struct PROCESS_INFO_t
{
   string csProcess;
   uint32_t dwImageListIndex;
};


bool _ui_get_executable_path(char * psz, uint32_t * puiSize);


namespace ios
{
   
   
   file_system::file_system(::aura::application *  papp) :
   ::object(papp),
   ::file::system(papp)
   {
      
   }
   
   
   file_system::~file_system()
   {
      
   }
   
   
   var file_system::length(const string & pszPath, ::aura::application * papp)
   {
      
      var varRet;
      
      
      struct stat stat;
      
      if(::stat(pszPath, &stat)  == -1)
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = stat.st_size;
      }
      
      return varRet;
      
   }
   
   
   
   
   bool file_system::initialize()
   {
      
      string str = getenv("HOME");
      
      ::file::path strRelative = ::dir::element();
      
      string strUserFolderShift;
      
      if(App(get_app()).handler()->m_varTopicQuery.has_property("user_folder_relative_path"))
      {
         
         strUserFolderShift = strRelative / App(get_app()).handler()->m_varTopicQuery["user_folder_relative_path"].get_string();
         
      }
      else
      {
         
         strUserFolderShift = strRelative;
         
      }
      
      m_strUserFolder = str / "ca2" / strUserFolderShift;
      
      return true;
      
   }
   
   
   
   bool file_system::update_module_path()
   {
      
      string str;
      
      char * lpsz = str.GetBufferSetLength(1024);
      
      uint32_t size = 1024;
      
      if(_ui_get_executable_path(lpsz, &size))
      {
         
         str.ReleaseBuffer();
         
      }
      else
      {
         
         lpsz = str.GetBufferSetLength(size);
         
         if(_ui_get_executable_path(lpsz, &size))
         {
            
            str.ReleaseBuffer();
            
         }
         else
         {
            
            return false;
            
         }
         
      }
      
      m_pathModule = str;
      
      m_pathCa2Module = ca2_module_dup();
      
      return true;
      
   }
   
   
   
   ::file::file_sp file_system::get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp)
   {
      
      ::file::file_sp spfile;
      
      spfile = ::file::system::get_file(varFile,nOpenFlags,pfesp,papp);
      
      if(spfile.is_set())
      {
         
         return spfile;
         
      }
      
      return NULL;
      
   }
   
} // namespace ios










