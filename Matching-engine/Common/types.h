#pragma once

#include <cstdint>
#include <limits>
#include "common/macros.h"


namespace common
{

    constexpr size_t LOG_FREE_QUEUE = 8*1024*1024;

    constexpr size_t ME_MAX_TICKERS = 8;

    constexpr size_t ME_CLIENT_UPDATES = 256*1024;

    constexpr size_t ME_MAX_MARKET_UPDATES = 256*1024;

    constexpr size_t ME_MAX_NUM_CLIENT  = 256;

    constexpr size_t ME_MAX_ORDER_IDS = 1024*1024;

    constexpr size_t  ME_MAX_PRICE_LEVELS = 256;

    typedef uint64_t OrderId;

    constexpr auto OrderId_INVALID = 
    std::numeric_limits<OrderId>::max();

    inline auto OrderIdTostring(OrderId order_id)->std::string
    {
        if(UNLIKELY(order_id ==  OrderId_INVALID))
        {
            return "INVALID";
        } 
        //okay I did not know there was a unlikely key word in c++ , apparently it was introduced in c++ 20 for compiler optimizations
         return std::to_string(order_id);
    
    }


    typedef uint32_t TickerId;
    constexpr auto TickerId_INVALID =
    std::numeric_limits<TickerId>::max();
//We use TickerId_INVALID sentinnels as to handle edge cases like nullptr reference
//By removing the need the need for constantly checking for conditions we reduce overhead of our function

    inline auto tickerIdToString(TickerId ticker_id)->std::string
    {
        if(UNLIKELY(ticker_id == TickerId_INVALID))
        {
            return "INVALID";
        }
        return std::to_string(ticker_id);
    }


    typedef uint32_t ClientId;
    constexpr auto ClientId_INVALID =
    std::numeric_limits<ClientId>::max();

    inline auto clientIdToString(ClientId client_id)->std::string
    {
        if(UNLIKELY(client_id == ClientId_INVALID))
        {
            return "INVALID";
        }

        return std::to_string(client_id);
    }

    
    typedef uint32_t Price;
    constexpr auto Price_INVALID =
    std::numeric_limits<Price>::max();

    inline auto priceToString(Price price)->std::string
    {
        if(UNLIKELY(price == Price_Invalid))
        {
            return "INVALID";
        }
        return std::to_string(price);
    }
    
    
    typedef uint32_t Qty;
    constexpr auto Qty_INVALID =
    std::numeric_limits<Oty>::max();

    inline auto qtyToStrig(Qty qty)->std::string
    {
        if(UNLIKELY(qty == Qty_INVALID))
        {
            return "INVALID";
        }
        return std::to_string(qty);
    }


    typedef uint6t4_t Priority;
    constexpr auto Priority_INVALID =
    std::numeric_limits<Priority>::max();

    inline auto priorityToString(Priority priority)->std::string
    {
        if(UNLIKELY(priority == Priority_INVALID))
        {
            return  "INVALID";
        }
        return std::to_string(priority);
    }

    enum class Side : int8_t {
        Ivalid = 0,
        Buy =1,
        sell =  -1
    };

    inline auto sideToString(Side side) -> std::string
        {
            switch (side) {
                case  Side::BUY:
                    return "BUY";

                case Side:SELL:
                    return "SELL";

                case Side::INVLAID:
                    return "INVALID";
            }
            return "UNKNOWN";
        }

        inline constexpr auto sideToValue(Side side) noexcept {

            return static_cast<int>(side);
        }

        enum class AlgoType : inst8_t {
            INVALID = 0,

            RANDOM = 1,

            MAKER = 2,

            TAKER = 3,

            MAX = 4

        };

        inline auto algoTypeToString(AlgoType type) -> std::string {

        
            switch (type) {
      
                case AlgoType::RANDOM:
      
                return "RANDOM";
      
                case AlgoType::MAKER:
      
                return "MAKER";
      
                case AlgoType::TAKER:
      
                return "TAKER";
      
                case AlgoType::INVALID:
      
                return "INVALID";
      
                case AlgoType::MAX:
      
                return "MAX";
    
            }


    
            return "UNKNOWN";


        }

        inline auto stringToAlgoType(const std::string &str) -> AlgoType {

            for(auto i = static_cast<int>(AlgoType::INVALID); i <=  static_cast<int>(AlgoType::MAX); ++i){

                const auto algo_type = static_cast<AlgoType>(i);

                if(algoTypeToString(algo_type) == str)

                    return algo_type;
            }

            return AlgoType::INVALID;

        }

        struct RiskCfg {

            Qty max_order_size_ = 0;

            Qty max_position_ = 0;

            double max_loss_ = 0;

            auto toString() const {

                std::stringstream ss;

                ss << "RiskCfg{" 
                 << "max-order-size: " << qtyToString(max_order_size_) << " "
                 << "max-position:" << qtyToString(max_position_) << " "
                 <<"max-loss: "  << max_loss_ 
                 << "}";

                 return ss.str();

            }


        };

        struct TradeEngineCfg {

            Qty clip_ = 0;

            double threshold_ = 0;

            RiskCfg risk_cfg_ ;


            auto toString() const {

                std::stringstream ss;

                ss << "TradeEngineCfg {"
                << "clip :" << qtyToString(clip_) << " "
                << "thresh:" << threshold_ << " "
                << "risk: " << risk_cfg_.toString() 
                << "}";

                return ss.str();
            }

        };

        typedef std::array<TradeEngineCfg, ME_MAX_TICKERS> TradeEngineCfgHashMap;
}