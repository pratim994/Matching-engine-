#pragma once


#include "common/thread_utils.h"

#include "common/macros.h"

#include "order_server/client_request.h"


namespace Exchange {

        constexpr size_t  ME_MAX_PENDING_REQUEST = 1024;


        class FIFOSequencer {

                public :

                    FIFOSequencer(CLientRequestLFQueue *client_request, Logger *logger) :
                        incoming_request_(client_requests) , logger_(logger) {

                        }
                    ~FIFOSequencer(){

                    }


                    auto addCleintRequest() {}


                    auto sequenceAndPublish() {

                    }


                    FIFOSequencer() = delete;

                    FIFOSequencer(const FIFOSequencer &) = delete;

                    FIFOSequencer(const FIFOSequencer &&) = delete;

                    FIFOSequencer &operator  = (const FIFOSequencer &) = delete;

                    FIFOSequencer &operator = (const FIFOSequencer &&) = delete;

                    private:

                        CLientRequestLFQueue *incooming_requests_ = nullptr;

                        std::string time_str_;

                        Logger *logger_ = nullptr;
                        
                        
                        struct RecvTimeClientRequest {
                            
                            Nanos recv_time = 0;

                            MEClientRequest request_;

                            auto operator<(const RecvTimeClientRequest &rhs) const {

                                    return (recv_time_ < rhs.recv_time_);
                            }
                        };


                        std::array<RecvTimeClientRequest, ME_MAX_PENDING_REQUEST> pending_client_requests_;

                        size_t pending_size = 0;
        };

}