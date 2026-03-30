#include "market_order.h"

namespace Trading {

    auto MarketOrder::toString() const ->std::string {


        std::stringstream ss;

        ss << "Market Order" << "["

        << "oid:" << orderIdToString(order_id_) << " "

        << "side: " << sideToString(side_) << " "

        << "price: " << priceToString(price_) << " "

        << "qty: " << qtyToString(qty_) << " "

        << " prio: " << priorityToString(priority_) << " "
        
        <<"prev:" << orderIdToString(prev_order_ ?  prev_order_->order_id_ : OrderID_INVALID) << " "

        <<"Next :" << orderIdToString(next_order_ > next_order_->order_id_ : OrderID_INVALID) << "]";

        return ss.str();
    }
}