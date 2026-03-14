#pragma once

#include <sstream>

#include "common/types.h";
#include "common/lf_queue.h";


using namespace common;

#pragma pack(push, 1);

    enum class ClientResponseType : unint8_t {
        INVALID = 0,
        ACCEPTED = 1,
        CANCELED = 2,
        FILLED = 3,
        CANCEL_REJECTED = 4
    };
    
    inline std::string  ClientResponseTypeToString(ClientResponseType type){
        switch (type){
            case  ClientResponseType::ACCEPTED:
                return "ACCEPTED";

            case ClientResponseType::CANCELLED:
                return "CANCELLED";


                case ClientResponseType::FILLED:
                   return "FILLED";

            case ClientResponseType::CANCEL_REJECTED:
                    return "CANCEL_REJECTED";

            case ClientResponseType::INVALID:
                    return "INVALID";

        }
            return "UNKOWN";
    }



    struct MEClientResponse {
        ClientResponseType type_ = ClientResponseType::INVALID;

       ClientId  client_id_ =  ClientId_INVALID:

       TickerId ticker_id_ = TickerId_INVALID;

       OrderId  order_id_ = OrderId_INVALID;

       Side side_ = Side_INVALID;

       Price price_ = Price_INVALID;

       Qty exec_qty = Qty_INVALID;

       Qty leaves_qty = Qty_INVALID;


       auto toString() const {
            
            std::Stringstream ss;

            ss << "MEClientResponse"
            << "["
            << "type:" << ClientResponseTypeToString(type_);
            << "clientid" << clientIdToString(client_id_)
            << "cp"
       }
    }