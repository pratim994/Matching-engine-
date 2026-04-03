#include "risk_manager.h"

#include "order_manager.h"

namespace Trading {

    RiskManager::RiskManager(Common::Logger *logger, const Position_keeper *position_keeper, const TradeEngineCfgHashMap &ticker_cfg)

        : logger_(logger) {

            for(TickerId i = 0; i < ME_MAX_TICKERS; ++i){

                ticker_risk.at(i).position_info_ = position_keeper->getPositionInfo(i);

                ticker_risk.at(i).risk_cfg_  = ticker_cfg[i].risk_cfg_;
            }
        }
}