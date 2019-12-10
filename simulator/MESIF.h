/*
 * Implementation specific to the MESIF protocol
 *
 * Author:
 *   Shivani Prasad
 *
 */


#include "SnoopingCache.h"

#ifndef _MESIF_H_
#define _MESIF_H_

class MESIF : public SnoopingCache {
public:
    MESIF(int cache_id);

private:
    static void *request_worker(void *arg);
    static void *response_worker(void *arg);
    static void handle_request(MESIF *obj, std::string op,
                                     unsigned long addr);

};




#endif

