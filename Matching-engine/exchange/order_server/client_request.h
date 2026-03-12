
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

    inline std::string clienntRequestTypeToString(ClientRequestType type)
    {
            switch (type)
            {
                case ClientRequestType::NEW:
                    return "NEW";


                case ClientRequestType::CANCEL:
                    return "Cancel";


                case ClientRequeestType::INVALID:
                    return "INVALID";
            }
            return  "UNKNOWN";
    }

}