//
//  CBPeripheralRSSI.h
//  SYGSDK
//
//  Created by Bruce on 2019/4/23.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface CBPeripheralRSSI : NSObject
@property (nonatomic, strong) CBPeripheral *peripheral;
@property (nonatomic, strong) NSNumber *RSSI;
@end

NS_ASSUME_NONNULL_END
