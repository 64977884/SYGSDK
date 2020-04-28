//
//  SYGBleBatteryStatus.h
//  SYGSDK
//
//  Created by Bruce on 2019/4/22.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SYGBleBatteryLevel) {
    SYGBleBatteryLevelFull = 0,
    SYGBleBatteryLevel2,
    SYGBleBatteryLevel3,
    SYGBleBatteryLevelLow
};

@interface SYGBleBatteryStatus : NSObject

@end

NS_ASSUME_NONNULL_END
