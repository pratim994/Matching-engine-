#include "trade_engine.h"


using namespace Trading {


    TradeEnigne::TradeEnigne(Common::ClientId client_id,
    
                            AlgoType algo_type,
                        
                            const TradeEngineCfg &ticker_cfg ,
                        
                            Exchange::ClientRequestLFQueue *client_request,
                        
                            Exchange::ClientResponseLFQueue *client_response ,

                            Exchange::MEMarketUpdateLFQueue *market_updates
                            ) :

                            client_id_(client_id) , outgoing_ogw_requests_(client_requests) , incoming_ogw_requests(client_responses) ,

                            incoming_md_updates_(market_updates) , logger_("trading_engine_" + std::to_string(client_id) + ".log"),

                            feauture_engine_(&logger_) ,

                            position_keeper_(&logger_),

                            order_manager_(&logger_, this , risk_manager_),

                            risk_manager_(&logger_, &position_keeper_ , ticker_cfg ) {

                                for(size_t  i = 0 ; i < ticker_order_book_.size() ; ++i) {

                                    ticker_orer_book_[i] = new MarketOrderBook(i, &logger_);

                                    ticker_order_book_[i]->setTradeEngine(this);
                                }

                                algoOnTradeUpdate_ = [this](auto ticker_id , auto price , auto side , auto book ){

                                    defaultAlgoOnTradeUpdate_ = [this](auto market_update, auto book){ defaultAlgoOnTradeUpdate(ticker_id , price , side, book); };


                                };

                                algoOnTradeUpdate_ = [this](auto ticker_id, auto book){ defaultAlgoOnTradeUpdate(market_update, book); };


                                algoOnOrderUpdate_= [this](auto client_response){ defaultAlgoOnTradeUpdate(client_response); };


                                if(algo_type == AlgoType::MAKER){

                                    mm_algo_ = new MarketMaker(&logger_, this, &feature_engine_, &order_manager_ , ticker_cfg );

                                }

                                for(TickerId i = 0; i < ticker_cgf.size(); ++i){
                                     logger_.log("%:% %() % Initialized % Ticker:% %.\n", __FILE__, __LINE__, __FUNCTION__,

                                   Common::getCurrentTimeStr(&time_str_),

                                     algoTypeToString(algo_type), i,

                                    ticker_cfg.at(i).toString());

                                }
                            }

                            TradeEnigne::~TradeEngine() {

                                run_ =  false;

                                using namespace  std::literals::chrono_literals;

                                std::this_thread::sleep_for(1s);

                                delete mm_algo_;

                                mm_algo_ = nullptr;

                                delete taker_algo_ ;

                                taker_algo_ = nullptr;

                                for(auto &order_book; ticker_order_book_){

                                    delete orer_book;

                                    order_book = nullptr;

                                }

                                outgoing_ogw_requests_ = nullptr;

                                incoming_md_updates_ = nullptr;

                                incoming_ogw_requests = nullptr;

                            }
    auto TradeEngine::SendClientRequest(const Exchange::MEClientRequest *client_request) noexcept -> void {

                logger_.log("%:% %() % Sending %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_),

                client_request->toString().c_str());

                auto next_write = outgoing_ogw_requests_->getNextToWriteTo();

                *next_write =  std::move(*client_request);

                outgoing_ogw_requests_->updateWriteIndex();
    }


    auto TradeEngine::run() noexcept -> void {

                logger_.log("%:% %() %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_));

                while(run_){
                        for (auto client_response = incoming_ogw_responses_->getNextToRead(); client_response; client_response = incoming_ogw_responses_->getNextToRead()) {

                            logger_.log("%:% %() % Processing %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_),

                             client_response->toString().c_str());

                    onOrderUpdate(client_response);

                    incoming_ogw_responses_->updateReadIndex();

                    last_events_time_ = Common::getCurrentNanos();


                }

                for(Auto market_updates  = incoming_md_updates_->getNextToRead(); market_update; market_update = incoming_md_updates_->getNextToRead() ){

                      logger_.log("%:% %() % Processing %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_),

                    market_update->toString().c_str());

                      ASSERT(market_update->ticker_id_ < ticker_order_book_.size(),

               "Unknown ticker-id on update:" + market_update->toString());

        ticker_order_book_[market_update->ticker_id_]->onMarketUpdate(market_update);

        incoming_md_updates_->updateReadIndex();

        last_event_time_ = Common::getCurrentNanos();

                }

                }
    }

    auto TradeEngine::algoOnOrderUpdate() noexcept -> void {

         logger_.log("%:% %() % ticker:% price:% side:%\n", __FILE__, __LINE__, __FUNCTION__,

                Common::getCurrentTimeStr(&time_str_), ticker_id, Common::priceToString(price).c_str(),

                Common::sideToString(side).c_str());

            position_keeper_.updateBBO(ticker_id, book->getBBO());

            feature_engine_.onOrderBookUpdate(ticker_id, price, side, book);

            algoOnOrderUpdate(ticker_id, price, side, book);

    }

    auto TradeEngine::algoOnTradeUpdate() noexcept -> void {

           logger_.log("%:% %() % %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_),

                market_update->toString().c_str());

            feauture_engine_.algoOnTradeUpdate(market_update, book);

            algoOnTradeUpdate_(market_update, book);

    }

    auto TradeEngine::onOrderUpdate(const Exchange::MEClientResponse *client_response) noexcept -> void{

         logger_.log("%:% %() % %\n", __FILE__, __LINE__, __FUNCTION__, Common::getCurrentTimeStr(&time_str_),

                client_response->toString().c_str());

        if(UNLIKELY(client_response->type_ == Exchange::ClientResponseType::FILLED))

            position_keeper_.add(client_response);

        algoOnOrderUpdate_(client_response);

    }
}