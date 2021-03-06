#include "framework.h"


namespace file
{


   reader::reader()
   {
   }

   reader::~reader()
   {
   }


   memory_size_t reader::read(void * lpBuf, memory_size_t nCount)
   {
      
      ::exception::throw_interface_only(get_app());
      
      return 0;

   }

   file_position_t reader::find(const void * pFind, memory_size_t size, const file_position_t * limit)
   {
      byte * signature = (byte *) pFind;
      memory_size_t signatureSize = size;
      uint64_t resPos = 0;
      byte_buffer byteBuffer2;
      byteBuffer2.SetCapacity(signatureSize);
      if(FAILED(read_false(this, byteBuffer2, signatureSize)))
         throw simple_exception(get_app());

      if (memcmp(byteBuffer2, signature, signatureSize) == 0)
         return resPos;

      const uint32_t kBufferSize = (1 << 16);
      byte_buffer byteBuffer;
      byteBuffer.SetCapacity(kBufferSize);
      byte *buffer = byteBuffer;
      memory_size_t numPrevBytes = signatureSize - 1;
      memcpy(buffer, (const byte *)byteBuffer2 + 1, numPrevBytes);
      resPos = 1;
      for (;;)
      {
         if (limit != NULL)
            if (resPos > *limit)
               throw simple_exception(get_app());
         do
         {
            memory_size_t numReadBytes = kBufferSize - numPrevBytes;
            memory_size_t processedSize;
            processedSize = read(buffer + numPrevBytes, numReadBytes);
            numPrevBytes += processedSize;
            if (processedSize == 0)
               throw simple_exception(get_app());
         }
         while (numPrevBytes < signatureSize);
         uint32_t numTests = (uint32_t) (numPrevBytes - signatureSize + 1);
         for (uint32_t pos = 0; pos < numTests; pos++)
         {
            byte b = signature[0];
            for (; buffer[pos] != b && pos < numTests; pos++);
            if (pos == numTests)
               break;
            if (memcmp(buffer + pos, signature, signatureSize) == 0)
            {
               resPos += pos;
               return resPos;
            }
         }
         resPos += numTests;
         numPrevBytes -= numTests;
         memmove(buffer, buffer + numTests, numPrevBytes);
      }

   }

   void reader::transfer_to(writer & writer, memory_size_t uiBufMax)
   {


      if(get_internal_data() && get_internal_data_size() > 0)
      {

         if(writer.increase_internal_data_size(get_internal_data_size()) && writer.get_internal_data() != NULL)
         {
            
            if(writer.get_internal_data() == get_internal_data())
               return;

            memmove(((byte *) writer.get_internal_data()) + writer.get_position() + get_internal_data_size(), ((byte *) writer.get_internal_data()) + writer.get_position(), writer.get_internal_data_size() - get_internal_data_size());
            memcpy(((byte *) writer.get_internal_data()) + writer.get_position(), get_internal_data(), get_internal_data_size());
            writer.seek(get_internal_data_size(), seek_current);

         }
         else
         {
            
            writer.write(get_internal_data(), get_internal_data_size());

         }

         return;

      }

      uiBufMax = MAX(8 * 1024, uiBufMax);
      memory_size_t uiBufMin = uiBufMax / 8;
      memory_size_t uiBufSize = uiBufMax;
      memory_size_t uiBufInc = uiBufSize;
      memory_size_t uiRead;
      memory_size_t uiSize = writer.get_internal_data_size();

      while(writer.increase_internal_data_size(uiBufInc) && writer.get_internal_data() != NULL)
      {
         memmove(((byte *) writer.get_internal_data()) + writer.get_position() + uiBufInc, ((byte *) writer.get_internal_data()) + writer.get_position(), uiBufInc);
         uiRead = read(((byte *) writer.get_internal_data()) + writer.get_position(), uiBufSize);
         writer.seek(uiRead, seek_current);
         uiBufSize -= uiRead;
         if(uiBufSize < uiBufMin)
         {
            uiBufSize   = uiBufMax;
            uiBufInc    = uiBufSize;
         }
      }

      if(uiBufSize > 0)
      {
         memmove(((byte *) writer.get_internal_data()) + writer.get_position(), ((byte *) writer.get_internal_data()) + writer.get_position() + uiBufSize, uiBufSize);
         writer.increase_internal_data_size(-(memory_offset_t)uiBufSize);
      }

      memory buf;
      buf.allocate(uiBufMax);
      if(buf.get_data() == NULL)
         throw "no memory";
      try
      {
         while(true)
         {
            uiRead = read(buf, buf.get_size());
            writer.write(buf, uiRead);
            if(uiRead <= 0)
            {
               return;
            }
            uiSize += uiRead;
         }
      }
      catch(...)
      {

      }

   }


   file_position_t reader::get_position() const
   {
      ::exception::throw_interface_only(get_app());
      return 0;
   }


   static const memory_size_t kBlockSize = ((uint32_t)1 << 31);


   HRESULT read(reader * preader, void * data, memory_size_t * processedSize)
   {
      memory_size_t size = *processedSize;
      *processedSize = 0;
      while (size != 0)
      {
         memory_size_t curSize = MIN(size, kBlockSize);
         memory_size_t processedSizeLoc;
         HRESULT res = S_OK;
         try
         {
            processedSizeLoc = preader->read(data, curSize);
         }
         catch(...)
         {
            res = E_FAIL;
         }
         *processedSize += processedSizeLoc;
         data = (void *)((byte *)data + processedSizeLoc);
         size -= processedSizeLoc;
         RINOK(res);
         if (processedSizeLoc == 0)
            return S_OK;
      }
      return S_OK;
   }

   HRESULT read_false(reader * preader, void * data, memory_size_t size)
   {
      memory_size_t processedSize = size;
      RINOK(read(preader, data, &processedSize));
      return (size == processedSize) ? S_OK : S_FALSE;
   }

   HRESULT read_fail(reader * preader, void * data, memory_size_t size)
   {
      memory_size_t processedSize = size;
      RINOK(read(preader, data, &processedSize));
      return (size == processedSize) ? S_OK : E_FAIL;
   }
  


} // namespace file




