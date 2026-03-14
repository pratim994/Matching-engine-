
//Lock free queue 


#pragma once

#include <sstream>

#include  "Common/types.h"
#include  "Common/lf_queue.h"

using namespace Common;


namespace Exchange 
{
    #pragma pack(push, 1);

    enum class ClientRequestType : uint8_t {
        INVALID = 0, 
        NEW = 1, 
        CANCEL = 2
    };

    inline std::string clientRequestTypeToString(ClientRequestType type)
    {
            switch (type)
            {
                case ClientRequestType::NEW:
                    return "NEW";


                case ClientRequestType::CANCEL:
                    return "Cancel";


                case ClientRequestType::INVALID:
                    return "INVALID";
            }
            return  "UNKNOWN";
    }

    struct MEClientRequestType{
        ClientRequestType type_ = ClientRequestType::INVALID;

        ClientId client_id_ = ClientId_INVALID;

        TickerId ticker_id_ = TickerId_INVALID;
         
        OrderId order_id_ = OrderId_INVALID;

        Side side_ = Side_INVALID;

        Price price_ = Price_INVALID;

        Qty qty_ = Qty_INVALID;

      auto toString() const 
      {
        std::stringstrem ss;
        ss << "MEClientRequest";
        <<"[]"
        << "type:" << clientRequestTypeToString(type_);
        <<"client:" << clientRequestTypeToString(client_id_) 
        << "ticker_id" << clientRequestTypeToString(ticker_id_);
        << "order id" << clientRequestTypeToString(order_id_);
        << "side_" << clientRequestTypeToString(side_);
        << "price" << clientRequestTypeToString(price_);
        << "qty_" << clientRequestTypeToString(qty_);
        << "]";
        return ss.str();

        
      }
    };

   #pragma pack(pop)
   
   typedef LFQueue<MEClientRequest> ClientRequestLfQueue; 

}