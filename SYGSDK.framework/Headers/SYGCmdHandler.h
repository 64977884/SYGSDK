//
//  SYGCmdHandler.h
//  SYGSDK
//
//  Created by Bruce on 2019/4/19.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGOfflineStatusManager.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString * const SYGWriteBeginNotification;
extern NSString * const SYGWritingNotification;
extern NSString * const SYGWriteEndNotification;
extern NSString * const SYGOfflineStatusNotification;
extern NSString * const SYGOfflineDataLengthNotification;
extern NSString * const SYGBatteryStatusNotification;

@interface SYGCmdHandler : NSObject

@property (nonatomic, strong, readonly) NSData *paraData;

- (instancetype)initWithData:(NSData *)data;

- (void)execute;

@end

NS_ASSUME_NONNULL_END
