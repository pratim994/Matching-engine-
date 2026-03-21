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

                auto start() -> void;

                auto stop() -> void;


                auto run noexcept {

                        logger_.log("%:% %() %\n" , __FILE__, __LINE__ , __FUNCTION__ , Common::getCurrentTimeStr(&time_str_));

                        while(run_){

                                tcp_server_.poll();

                                tcp_server_.sendAndRecv();

                                for(auto client_response = outgoing_responses_->getNextToRead();
                        
                                        outgoing_responses_->size() && client_response;
                                
                                        client_reponse = outgoing_responses_->getNextToRead()){

                                                auto &next_outgoing_seq_num = cid_next_outgoing_seq_num_[client_response->client_id];

                                                  logger_.log("%:% %() %\n" , __FILE__, __LINE__ , __FUNCTION__ , Common::getCurrentTimeStr(&time_str_),\
                                                        
                                                client_reponse->client_id_ , next_outgoing_seq_num, client_reponse->toString());

                                                ASSERT(cid_tcp_socket_[client_response->client_id_] != nullptr ,
                                                        
                                                        "Dont have a TCPsocket for ClieintId:" + std::to_string(client_rsponse->client_id_));

                                                        cid_tcp_socket_[client_response->client_id_]->send(&next_out_going_seq_num, sizeof(next_out_going_seq_num));


                                                        cid_tcp_socket_[client_response->client_id_]->send(&next_out_going_seq_num, sizeof(MEClientResponse));


                                                        outgoing_responses_->updateIndex();

                                                        ++next_out_going_seq_num;

                                        }
                        }
                }

                auto recvCallback(TCPSocket *socket, Nanos rx_time) noexcept {

                        logger_.log("%:% %() % recieved  Socket:% len:% rx:%\n", __FILE__, __LINE__, __FUNCTION__,
                                
                                Common::getCurrentTimeStr(&time_str_), socket->socket_fd_, socket->next_rcv_valid_index, rx_time);


                        if(socket->next_rcv_valid_index_ >= sizeof(OMCleintRequest)) {

                                size_t i = 0 ;

                                for(; i + sizeof(OMClientRequest) <= socket->nextt_rcv_rcv_valid_index_; i += sizeof(OMClientRequest)) {

                                        auto request = reinterpret_cast<const OMClientRequest *>(sockeet->inbound_.data()+i);

                                        if(UNLIKELY(cid_tcp_socket_[request->me_client_request_.client_id_] == nullptr)){

                                                        cid_tcp_socket_[request->me_client_request_.client_id_] = socket;

                                        }

                                        if(cid_tcp_socket_[request->me_client_request_.client_id_] != socket ) {

                                                logger_.log("%:% %() % Recived clientRequest from clientid:% on different socket :% expected:%\n",
                                                
                                                        __FILE__, __LINE__ ,__FUNCTION__, Common::getCurrentTimeStr(&time_str_), request->me_client_request_.client_id_, socket->socket_fd_ ,
                                                        
                                                        cid_tcp_socket_[request->me_client_request_.client_id_]->socket_fd_);

                                                        continue;
                                        }

                                        auto &next_out_going_seq_num = cid_next_exp_seq_num_[request->me_client_request_.client_id_];

                                        if(request->seq_num_ != next_exp_seq_num) {

                                                        logger_.log("%:% %() % Incorrect sequence number. ClientId:% seqNUm expected:% recieved:%\n", 
                                                        
                                                        __FILE__, __LINE__, __FUNCTION__,
                                                        
                                                        Common::getCurrentTimeStr(&time_str_), request->me_client_request_.client_id_, next_exp_seq_num, request->seq_num_);

                                                        continue;
                                        }

                                        ++next_exp_seq_num;

                                        fifo_sequencer_.addClientRequest(rx_time_,request->me_client_request_);


                                }

                                memcpy(socket->inbound_data_.data(), socket->inbound_data()+i,  socket->next_rcv_valid_index - i);

                                socket->next_rcv_valid_index_ -= i;
                        }
                }

                auto recvFinishedCallabck() noexcept {
                        fifo_sequencer_.sequenceAndPublish();
                }


                OrderServer() = delete;

                OrderServer(const OrderServer &) =  delete;

                OrderServer(cosnt OrderServer &&) = delete;
                
                 OrderServer &operator = (const OrderServer &) =  delete;
       
                
                OrderServer &operator = (const OrderServer &&) =  delete;
       
      private:
                const std::string iface_;

                const int port_ = 0;

                ClientResponseLFQueue *outgoing_responses_ = nullptr;

                volatile bool run_ = false;

                std::string time_str_;

                Logger logger_;


                std::array<size_t ,  ME_MAX_NUM_CLIENTS> cid_next_outgoing_seq_num_;
        
                
                std::array<size_t ,  ME_MAX_NUM_CLIENTS> cid_next_exp_seq_num_;

                std::array<Common::TCPSocket *, ME_MAX_NUM_CLIENTS> cid_tcp_socket_;

                Common::TCPServer tcp_server_;


                FIFOSequencer fifo_sequencer_;
       
                };

        


}