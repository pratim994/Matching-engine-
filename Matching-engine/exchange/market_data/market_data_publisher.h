#pragma once

#include <functional>

#include "market_data/snapshot_sythesize.h"


namespace Exchange {

    class MarketDataPublisher {

        public:

            MarketDataPublisher(MEMarkedtUpdateLFQueue *market_updates, const std::string &iface,
            
                const std::string &snapshot_ip, int snaphot_port,
            
                cosnt std::string &increment_ip ,  int increment_port);

                ~MarketDataPublisher();

                stop();

                using namespace std::literals::chrono_literals;

                std::this_thread::sleep_for(5s);


                delete snapshot_synthesizer_ ;

                snapshot_synthesizer_ = nullptr;



    }

    auto start() -> void {

        run_ = true;

        ASSERT(Common::createAndStartThrea(-1, "Exchange/MarketDataPublisher", [this]() { run();}) != nullptr, "Failed to start MarketData Thread");

        snapshot_synthesizer_ ->start();
    }

    auto stop() -> void {

        run_ = false;

        snapshot_synthesizer_->stop();

    }


    auto run noexcept -> void;

    MarketDataPublisher() = delete;


    MarketDataPublisher(const MarketDataPublisher &) = delete;


    MarketDataPublisher(const MarketDataPublisher &&) = delete;


    MarketDataPublisher &operator = (const MarketDataPublisher &) = delete;



    MarketDataPublisher &operator=( const MarketDataPublisher &&) = delete;


    private:

        size_t next_inc_seq_num_ = 1;

        MEMarkedtUpdateLFQueue *outgoing_md_updates_ = nullptr;

        MDPMarketUpdateLFQueue snapshot_md_updates_;

        volatile bool run_  =  false;

        std::string time_str_;

        Logger logger_;

        Common::McastSocket incremental_socket_;
}


