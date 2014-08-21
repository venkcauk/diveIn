//
//  GameSummaryData.h
//  diveIn
//
//  Created by Venkatesh Shivashanmugam on 17/08/14.
//
//

#ifndef __diveIn__GameSummaryData__
#define __diveIn__GameSummaryData__

#include <iostream>

class GameSummaryData {
    
    public :
    int totalMeters;
    int totalCoins;
    int totalPearl;
    
    GameSummaryData(int meters, int coins, int pearl);
    void reset();
};

#endif /* defined(__diveIn__GameSummaryData__) */
