#include "framework.h"


namespace html
{


   namespace impl
   {


      void image::_001OnDraw(data * pdata)
      {

         ::draw2d::graphics * pgraphics = pdata->m_pgraphics;

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pdata->m_imagea[m_iImage]->m_spdib->defer_realize(pgraphics);

            pgraphics->BitBlt((int32_t)get_x(), (int32_t)get_y(), (int32_t)get_cx(), (int32_t)get_cy(),
               pdata->m_imagea[m_iImage]->m_spdib->get_graphics(), 0, 0, SRCCOPY);

         }

      }


      void image::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         elemental::implement_phase1(pdata, pelemental);
         if (pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            m_iImage = pdata->get_image_index(pelemental->m_propertyset["src"]);
            m_cxMax = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cx;
            m_cxMin = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cy;
         }
      }


      bool image::layout_phase1(data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            single_lock lockImage(pdata->m_imagea[m_iImage]->m_pmutex);

            if (lockImage.lock(duration::zero()))
            {
               m_box.set_cxy(pdata->m_imagea[m_iImage]->m_spdib->size());
            }
            else
            {
               m_box.set_cxy(0, 0);
            }

         }

         return true;

      }


      void image::layout_phase3(data * pdata)
      {

         elemental::layout_phase3(pdata);
         /*if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            single_lock lockImage(&pdata->m_imagea[m_iImage]);

            if (lockImage.lock(duration::zero()))
            {
               pdata->m_layoutstate3.m_cx = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cx;
               if (pdata->m_imagea[m_iImage]->m_spdib->m_size.cy > pdata->m_layoutstate3.m_cya.last())
               {
                  pdata->m_layoutstate3.m_cya.last() = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cy;
               }
            }
            else
            {
               pdata->m_layoutstate3.m_cx = 0;
               pdata->m_layoutstate3.m_cya.last() = 0;
            }

            m_box.set_cxy(pdata->m_imagea[m_iImage]->m_spdib->size());

         }
         */
      }


   } // namespace impl


} // namespace html_impl


