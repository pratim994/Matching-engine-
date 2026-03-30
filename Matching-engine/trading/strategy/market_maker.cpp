#include "market_maker.h"

#include "trade_engine.h"


namespace Trading {

    MarketMarker:: MarketMarker(Common::Logger *logger, TradeEngine *trade_engine, const FeautureEngine *feature_engine,
    
        OrderManager *order_manager, const TradeEngineCfgHashMap &ticker_cfg)

        : feature_engine_(feature_engine) m order_manager_(order_manager) , logger_(logger),

        ticker_cfg(ticker_cfg) {

            trade_engine->algoOnOrderBookUpdate_ = [this](auto ticker_id, auto price, auto side , auto book){

                onOrderBookUpdate(ticker_id, price, side, book);

            }

                trade_engine->algoOnTradeUpdate_ =  [this](auto market_update, auto book){ onTradeUpdate(market_update, book);};

                trde_engine->algoOnOrderUpdate_ = [this](auto client_response){onOrderUpdate(client_response);};
        }

}