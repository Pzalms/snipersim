#ifndef __DRAM_CACHE
#define __DRAM_CACHE

#include "dram_cntlr_interface.h"
#include "subsecond_time.h"
#include "cache.h"
#include "queue_model.h"

class DramCache : public DramCntlrInterface
{
   public:
      DramCache(core_id_t core_id, UInt32 cache_block_size, DramCntlrInterface *dram_cntlr);
      ~DramCache();

      virtual SubsecondTime getDataFromDram(IntPtr address, core_id_t requester, Byte* data_buf, SubsecondTime now);
      virtual SubsecondTime putDataToDram(IntPtr address, core_id_t requester, Byte* data_buf, SubsecondTime now);

   private:
      UInt32 m_cache_block_size;
      SubsecondTime m_data_access_time;
      SubsecondTime m_tags_access_time;
      ComponentBandwidth m_data_array_bandwidth;

      DramCntlrInterface* m_dram_cntlr;
      Cache* m_cache;
      QueueModel* m_queue_model;
      UInt64 m_reads, m_writes;
      UInt64 m_read_misses, m_write_misses;

      std::pair<bool, SubsecondTime> doAccess(Cache::access_t access, IntPtr address, core_id_t requester, Byte* data_buf, SubsecondTime now);
      SubsecondTime accessDataArray(Cache::access_t access, core_id_t requester, SubsecondTime t_start);
};

#endif // __DRAM_CACHE