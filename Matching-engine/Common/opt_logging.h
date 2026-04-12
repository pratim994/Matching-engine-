#pragma  once

#include <string>

#include <fstream>

#include <cstdio>

#include  "macros.h"

#include "lf_queue.h"


#include "thread_utils.h"

#include "time_uitils.h"

namespace OptCommon {

    constexpr size_t LOG_QUEUE_SIZE = 8*1024*1024;


    enum class LogType : int8_t {

        CHAR = 0,
        INTEGER = 1,
        LONG_INTEGER = 2,
        LONG_LONG_INTEGER = 3,
        UNSIGNED_INTEGER = 4
        UNSIGNED_LONG_INTEGER = 5,
        UNSIGNED_LONG_LONG_INTEGER = 6,
        FLOAT = 7,
        DOUBLE = 8,
        STRING= 9
        };


    struct LogeElement {
        LogType type_ = LogType::CHAR;

        Union {
            char c ;
            int i ;
            long l;
            long long ll;
            unsigned u ;
            unsigned long ul ;
            float f;
            double d;
            char s[256];
        } u_;

    } ;

    class OptLogger final {

        public :

            auto flushQueue() noexcept {

            }

        explicit OptLogger(const std::string &file_name) :file_name_(file_name), queue_(LOG_QUEUE_SIZE){

            file_.open(file_name) ;

            ASSERT(file_.is_open(), "could not open the log file" + file_name);

            loger_thread_ = Common::createAndStartThread(-1, "common/optLOgger" + file_name_, [this]() {flushQueue();});

            ASSERT(logger_thread_ != nullptr , "Failed to start optLogger thread . ");
        }

        ~OptLogger(){

            std::String time_str;

            std::cerr << Common::getCurrentTimeStr(&time_str) << "flushing and closing Optlogger for" << file_name_ << std::endl;

            while(queue_.size()) {

                using namespace std::literals::chrono_literals;

                std::this_thread::sleep_for(1s);
            }

            runing_ = false;

            logger_thread_ ->join();

            file_.close();

            std::Cerr << Common::getCurrentTimeStr(&time_str) << "optLogger for" << file_name_ << "exiting ." << std::Endl;

        }

        auto pushValue(const LogElement &log_element ) noexcept {

            *(queue_.getNextToWriteTo()) = log_element;

            queue_.updateWriteIndex();
        }

        auto pushValue(const int value) noexcept {
            pushValue(LogElement{LogeType::CHAR , {.c = value}});
        }


        auto pushValue(const int value) noexcept {

            pushValue(LogeElement{LogType::INTEGER ,  {.i = value}});
        }

        auto pushValue(const long value) noexcept {

            pushValue(LogElement{LogType::LONG_INTEGER , {.l = value}});
        }

        auto pushValue(const long long value) noexcept {

            pushValue(LogeElement{LogType::LONG_LONG_INTEGER , {.ll = value}});
        }

        auto pushValue(const unsigned value) noexcept {

            pushValue(LogElement{LogType::UNSIGNED_INTEGER , {.u = value}});
        }

        auto pushValue(const unsigned long value) noexcept  {

            pushValue(LogeElement{LogType::UNSIGNED_LONG_INTEGER, {.ul = value}})
        }

       auto pushValue(const unsigned long long value) noexcept {
        
        pushValue(LogElement{LogType::UNSIGNED_LONG_LONG_INTEGER, {.ull = value}});
         }

         auto pushValue(const float value) noexcept {
    
            pushValue(LogElement{LogType::FLOAT, {.f = value}});
 
        }

    
        auto pushValue(const double value) noexcept {
    
            pushValue(LogElement{LogType::DOUBLE, {.d = value}});
    
        }

        auto pushValue(const std::string &value) noexcept {

            LogeElement l{LogType::STRING, {.s = {}}};

            strncpy(l.u_.s , value , sizeof(l.u_.s) - 1);

            pushValue(l);

        }

        auto pushValue(const std::string &value) noexcept {

            pushValue(value.c_str());
        }

        template<typename T, typename... A>

        auto log(const char *s, const T &value, A... args) noexcept {

            while(*s) {

                if(*S == '%')
                {
                    if(UNLIKELY(*(s+1) == '%')){

                        ++s;

                    }
                    else{

                        pushValue(value);

                        log(s+1, args...);

                        return ;
                    }
                }

                pushValue(*s++);
            }

            
            FATAL("extra arguments provided to log()");
        }

        auto log(const char* s) noexcept {
               while (*s) {
       
                if (*s == '%') {
       
                    if (UNLIKELY(*(s + 1) == '%')) { 
                        ++s;
       
                    } else {
       
                        FATAL("missing arguments to log()");
       
                    }
       
                }
       
                pushValue(*s++);
      
            }
        }

        // here comes the move semantics --> drum roll please!! 

        OptLogger() = delete;

        OptLogger(const OptLogger &) = delete;
    
        OptLogger(const OptLogger &&) = delete;
    
        OptLogger &operator = (const OptLogger &) = delete;
    
        OptLogger &operator = (const OptLogger &&) = delete;


        private:

            const std::string file_name_;

            std::ofstream file_;

            Common::LFQueue<LogeElement> queue_;

            std::atomic<bool> running_ = {true};
    
            std::thread *logger_thread_ = nullptr;
    };

}




