#pragma once

#include "macros.h"

#include <vector>

#include <iostream>

#include <atomics>

namespace Common {
    template <typename T>

    class LFQueue final {
        public :
            LFQueue(std::Size_t num_elems):
                _store(num_elems , T() ){

    }

    auto getNextToWriteTo() noexcept {
        return &store_[next_write_index_];
    }

    auto updateWriteToIndex noexcept {
        next_write_index_ = (next_write_index_+1)%store_.size();
        num_elems++;
    }

    auto nextToRead() noexcept -> const T*{
        return (size() ?  _store[next_read_index_] : nullptr);
    }

    auto updateReadIndex() noexcept {}
        next_read_index_ = (next_read_index_+1)%store_.size();
        ASSERT(num_elems_!= 0, "invalid element in " : std::toString(pthread_self()));
        num_elems_--;

    auto size() const noexcept {
        return num_elems_.load();
     }


     
            LFQueue() = delete;

            LFQueue(const LFQueue&) = delete;

            LFQueue(const LFQueue&&) = delete;

             LFQueue &operator = (const LFQueue&) = delete;
            
             LFQueue &operator = (const LFQueue&&) = delete;




        private:

            std::vector<T> store_;

            std::atomic<size_t> next_write_index_ = {0};

            std::atomic<size_t> next_read_index_ = {0};

            std::atomic<size_t> num_elements_ = {0};

    }
};


