#include "framework.h"


namespace user
{


   tab_callback::tab_callback()
   {

   }

   tab_callback::~tab_callback()
   {

   }

   bool tab_callback::_001IsAddTab(tab * ptab, ::index iTab)
   {
      
      UNREFERENCED_PARAMETER(ptab);
      UNREFERENCED_PARAMETER(iTab);

      return false;

   }

   void tab_callback::_001OnTabClick(tab * ptab, ::index iTab)
   {
      
      ptab->_001SelectTab(iTab);

   }

   void tab_callback::_001OnTabClose(tab * ptab, ::index iTab)
   {
      
      ptab->_001CloseTab(iTab);

   }

   sp(::user::interaction) tab_callback::_001GetTabWnd(::index iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
      return NULL;
   }

   void tab_callback::_001OnShowTab(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001OnDropTab(::index iTab, e_position eposition)
   {
      UNREFERENCED_PARAMETER(iTab);
      UNREFERENCED_PARAMETER(eposition);
   }

   void tab_callback::_001DropTargetWindowInitialize(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowRelay(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowFinalize(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }


} // namespace ca

