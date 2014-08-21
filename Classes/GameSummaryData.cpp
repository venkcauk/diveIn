//
//  GameSummaryData.cpp
//  diveIn
//
//  Created by Venkatesh Shivashanmugam on 17/08/14.
//
//

#include "GameSummaryData.h"


GameSummaryData::GameSummaryData(int meters, int coins, int pearl) {
    
    totalMeters = meters;
    totalCoins = coins;
    totalPearl = pearl;
}

void GameSummaryData::reset() {
    totalMeters = 0;
    totalCoins = 0;
    totalPearl = 0;
}
