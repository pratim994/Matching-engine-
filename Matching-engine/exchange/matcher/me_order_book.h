#pragma once

#include "common/types.h"

#include "common/mem_pool.h"

#include "common/logging.h"

#include "order_server/client_response.h"

#include "market_data/market_update.h"

#include "me_order.h"

using namespace Common;


namespace Exchange {
    class MatchingEngine;

    class MEOrderBook final {
        private:
            TickerId ticker_id_ = TickerId_INVALID;

            MatchingEngine *matching_engine_ = nullptr;

            ClientOrderHashMap cid_oid__order;

            MemPool<MEOrdersAtPrice> orders_at_price_pool_;

            MEOrdersAtPrice *bids_by_price_ = nullptr;

            MEOrdersAtPrice *asks_by_price = nullptr;

            OrdersAtPriceHashMap price_orders_at_price_;

            MemPool<MEOrder> order_pool_;
-
            MEClientRespone  client_response_;

            MEMarketUpdate market_update_;

            OrderId next_market_order_id_ = 1;

            std::string time_str_;
            Logger *logger_ = nullptr;

            typedef std::array<MEOrderBook *, ME_MAX_TICKERS_>
        
            OrderBookHashMap;
        };

    }
}
