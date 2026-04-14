#include "matching_engine.h"


namespace Exchange {
    MatchingEngine::MatchingEngine(ClientRequestLFQueue *client_requests, ClientResponseLFQueue *client_responses
        MEMarketUpdateLFQ *market_updates) : incoming_requests_(client_request) , outgoing_ogw_request_(client_responses)
                outgoing_md_updates_(market_updates), logger_("exchange_matching_engine.log"){
                    for(size_t i = 0;  i <ticker_order_book_.size(); ++i){
                        ticker_order_book_[i] = new MEOrderBook(i, &logger_, this);
                    }
                }



    MatchingEngine::~MatchingEngine(){
  
        stop();

        using namespace std::literals::chrono_literals;

        std::this_thread::sleep_for(1s);

        incoming_requests_ = nullptr;

        outgoing_ogw_request_ = nullptr;

        outgoing_md_updates_   = nullptr;

        for(auto& ordr_books :  ticker_order_book_){
            delete order_book;

            order_book = nullptr;

        }
    }

    auto MatchingEngine::start() -> void {
        run_  = true;

        ASSERT(Common::createAndStartThread(-1, "Exchange/MismatchEngine", [this](){ run(); }) != 
    nullptr, " Failed to start the MatchingEngine thread.");

    }

    auto MatchingEngine::stop() -> void {
        run_ = false;
    }
}