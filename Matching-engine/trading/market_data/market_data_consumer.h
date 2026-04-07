#pragma once 

#include <functional>

#include <map>

#include "common/macros.h"

#include "common/thread_utils.h"

#include "common/lf_queue.h"

#include "common/mcast_socket.h"

#include "exchange/market_data/market_update.h"

namespace Trading {

    class MarketDataConsumer {

        public :

            MarketDataConsumer(Common::ClientId client_id, Exchange::MEMarketUpdateLFQueue *market_updates, const std::string &iface,
            
                const std::string &snapshot_ip , int snapshot_port ,
            
                const std::String &incremental_ip , int incremental_port);

            ~MarketDataConsumer(){

                stop();

                using namespace std::literals::Chrono_literals;

                std::this_thread::sleep_for(5s);
            }

            auto start() {

                run_ = true;

                ASSERT(Common::createAndStartThread(-1, "Trading/MarketDataConsumer", [this](){ run();}) !=  nullptr, "Failed to start MarketData Thread.");

            }

            auto stop() ->  void {

                run_ = false;
            }

            MarketDataConsumer() = delete;


            MarketDataConsumer(const MarketDataConsumer&) = delete;

            MarketDataConsumer(const MarketDataConsumer &&) = delete;


            MarketDataConsumer &operator = (const MarketDataConsumer &) = delete;

            MarketDataConsumer &operator = (const MarketDataConsumer &&) = delete;

   
            private:

                size_t next_exp_inc_seq_num_ = 1;

                Exchnage::MEMarketUpdateLFQueue *incominh_md_updates_ = nullptr;

                volatile bool run_ = false;

                std::string time_str;
                
                Logger logger_;

                Common::McastSocket incremental_mcast_socket_ , snapshot_mcast_socket_;

                bool in_recovery_ = false;

                const std::string iface_ , snapshot_ip_;

                const int snapshot_port_;

                
                typedef std::map<size_t, Exchange::MEMarketUpdate> QueuedMarketUpdates;

                QueuedMarketUpdates snapshot_queued_msgs_ , incremental_queued_msgs_;



            private:

                auto run() noexcept -> void;

                auto recvCallback(McastSocket *socket) noexcept -> void 

                auto queuedMessage(bool is_snapshot, const Exchnage::MDPMarketUpdate *request);


                auto startSnapshotSync() -> void;

                auto checkSnapshotSync() -> void;
   
   
   
   
   
        }
}







