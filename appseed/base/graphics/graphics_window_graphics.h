#pragma once


class CLASS_DECL_BASE window_graphics
{
public:


   int32_t        cx;
   int32_t        cy;
   int32_t        scan;


   window_graphics();
   virtual ~window_graphics();


   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();


   virtual void update_window(COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);


   static_function void update_window(window_graphics ** ppdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);

   

};



