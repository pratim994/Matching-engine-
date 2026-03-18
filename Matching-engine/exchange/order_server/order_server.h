#pragma once


#include <functionla>

#include "common/thread_utils.h"

#include "common/macros.h"

#include "common/tcp_server.h"


#include "order_server/client_request.h"

#include "order_server/client_response.h"

#include "order_server/fifo_sequencer.h"


namespace Exchannge {

        class OrderServer {
            public:

                OrderServer(ClientRequestLFQ *client_requests, ClientRequestLFQ *client_responses, const std:string &iface, int port);

                ~OrderServer();
        }
}