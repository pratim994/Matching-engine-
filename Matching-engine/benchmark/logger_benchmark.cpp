#include "common/logging.h"

#include "common/opt_logging.h"


std::string random_string(size_t length)
{

}

template<typename T>

size_t benchmarkLogging(T *logger){

}


int main(int, char **)
{
     
        using namespace std::literals::chrono_literals;
        
        {
            Common::Logger logger("logger_benchmark_original.log");

            const auto cycles = benchmarkLogging(&logger);

            std::cout << "ORIGINAL LOGGER" << cycles <<"CLOCKS CYCLES PER OPERATIONS." << std::endl;

            std::this_thread::sleep_for(10s);

        }

        {

            OptCommon::OptLogger opt_logger("logger_benchmarks_optimized.log");

            const auto cycles = benchmarkLogging(&opt_logger);

            std::cout << "OPTIMIZED LOGGER" << cycles << " CLOCK CYCLES PER OPERATION" << std::endl;

            std::this_thread::sleep_for(10s);


        }

        exit(EXIT_SUCCESS);


}