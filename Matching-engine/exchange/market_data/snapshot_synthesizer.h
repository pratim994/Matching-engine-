#pragma once

#include "common/types.h"

#include "common/thread_utils.h"

#include "common/lf_queue.h"

#include "common/macros.h"


#include "common/mscast.h"

#include "common/mem_pool.h"

#include "common/logging.h"

#include "market_data/market_update.h"

#include "market_data/me_order.h"

using namespace Common;


namespace Exchange {

    class SnapShotSynthesizer {

            public:

                SnapShotSynthesizer(MDPMarketUpdateLFQueue *market_updates, const std::string &iface
                        ,const std::string &snapshot_ip, int snapshot_port);

                ~SnapShotSynthesizer();

                auto start() -> void;

                auto stop() -> void;

                auto addToSnapShot(const MDPMarketUpdate *market_update);

                auto publishSnapshot();

                auto run() -> void;

                SnapShotSynthesizer () = delete;
    
                    
                SnapShotSynthesizer (const SnapShotSynthesizer &) = delete;

                
                SnapShotSynthesizer (const SnapShotSynthesizer &&) = delete;
                    

                SnapShotSynthesizer &operator=  (const SnapShotSynthesizer &) = delete;

                SnapShotSynthesizer &operator = (const SnapShotSynthesizer &&) = delete;


            private:

                    MDPMarketUpdateLFQueue *snapshot_md_updates_ = nullptr;
                    
                    Logger logger_;

                    volatile bool run_ = false;

                    std::string time_str_;

                    McastSocket snapshot_socket_;

                    std::array<std::array<MEMarketUpdate *, ME_MAX_ORDER_IDS> , ME_MAX_TICKERS> ticker_orders_;

                    size_t last_inc_seq_num_ = 0;

                    Nanos last_snapshot_time_ = 0;


                    MemPool<MEMarketUpdate> order_pool_;

            };
}










