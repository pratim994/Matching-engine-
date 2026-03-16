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
        public:
            explicit MEOrderBook(TickerId ticker_id, Logger *logger, MatchingEngine *matching_engine);

            ~MEOrderBook();


            MEOrderBook() = delete;

            MEOrderBook(const MEOrderBook &) =  delete;


            MEOrderBook(const MEOrderBook &&) =  delete;

            MEOrderBook &operator = (const MEOrderBook &) = delete;

            MEOrderBook &&operator = (const MEOrderBook &&) = delete;

            auto MEOrderBook::add(ClientId client_id, OrderId client_order_id, TickerId ticker_id, Side side, Price 

                    price, Qty qty ) noexcept -> void;

            auto MEOrderBook::cancel(ClientId client_id, OrderId client_order_id, TickerId ticker_id) noexcept -> void;



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


        private:

            auto generateNewMarketOrderId() noexcept -> OrderId {

                return next_market_order_id_++;

            }

            auto priceToIndex(Price price) const noexcept {
                
                return (price% ME_MAX_PRICE_LEVELS);
            }

            auto getOrderAtPrice(Price price) const noexcept -> MEOrdersAtPrice{

                    return price_orders_at_price_.at(priceToIndex(price));
            }



        };

    }
}
