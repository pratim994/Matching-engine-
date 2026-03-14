#pragma once

#include <array>

#include "Common/types.h"

#include <sstream>


using namespace Common;


namespace Exchange {
    struct MEOrder {
        TickerId ticker_id_ = TickerId_INVALID;

        ClientId client_id_ = ClientId_INVALID;

        OrderId client_order_id_ = OrderId_INVALID;

        OrderId market_order_id_ = OrderId_INVALID;

        Side side_ = Side::INVALID;

        Qty qty_ = Qty_INVALID;

        Priority priority_ = Priority_INVALID;
        
        MEOrder *prev_order_ = nullptr;

        MEOrder *next_order_ = nullptr;


        MEOrder() = default;


        MEOrder( TickerId ticker_id, ClientId client_id, OrderId client_order_id, OrderId market_order_id ,Side side,
        Price price, Qty qty, Priority priority, MEOrder *prev_order, MEOrder *next_order  ) noexcept :
            
            ticker_id_(ticker_id),

            client_id_(client_id),

            client_order_id_(client_order_id),

            market_order_id_(market_order_id),

            side_(side),

            qty_(qty),

            priority_(priority)

            prev_order_(prev_order),

            next_order_(next_order) {}

            auto toString() const -> std::string;
            

    };

    typedef std::array<MEOrder* , ME_MAX_ORDER_IDS> OrderHashMap;

    Typedef std::array<OrderHashMap, ME_MAX_NUM_CLIENTS> ClientOrderHashMap;


    struct MEOrdersAtPrice {
        Side side_ = Side::INVALID;
        Price price_ = Price_INVALID;

        MEOrder *first_me_order_ = nullptr;
        
        
        MEOrdersAtPrice *prev_entry_ = nullptr ;
        MEOrdersAtPrice *next_entry_ = nullptr;

        MEOrdersAtPrice() = default;

        MEOrdersAtPrice(Side side, Price price, MEOrder *first_me_order, MEOrdersAtPrice *prev_entry, MEOrdersAtPrice *next_entry) : 
        side_(side), price_(price), first_me_order_(first_me_order), prev_entry_(prev_entry) , next_entry_(next_entry) {}

            auto toString() cosnt {
                std::stringstream ss;

                ss << "MEOrdersAtPrice[" 
                << "Side :" << sideToString(side_) << " " 
                <<"Price :" <<priceToString(price_) << " "
                << "first_order_me :" <<  (first_me_order_ ? first_me_order_->toString() : "null") << " "
                << "prev_entry :" << priceToString(prev_entry_ ? prev_entry_->price_ : Price_INVALID) <<" " 
                << "next_entry :" << priceToString(next_entry_ ? next_entry_->price_ : Price_INVALID) << " ]";

                return ss.str();

            }
        };

        typedef std::array<MEOrdersAtPrice *, ME_MAX_PRICE_LEVELS> OrdersAtPriceHashMap;


}