//
//  SYGPackageData.h
//  SYGPen
//
//  Created by Bruce on 2019/1/7.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGCmdHandler.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SYGPackageDataCmdType) {
    SYGPackageDataCmdTypeInfo = 0x01,
    SYGPackageDataCmdTypeSend = 0x02,
    SYGPackageDataCmdTypeWrite = 0x03,
    SYGPackageDataCmdTypeNotyfy = 0x04,
    SYGPackageDataCmdTypeWritePackageBegin = 0b00,
    SYGPackageDataCmdTypeWritePackageEnd = 0x11,
    SYGPackageDataCmdTypeWritePackageIng = 0x01,
    SYGPackageDataCmdTypeQuery = 0x88,
    SYGPackageDataCmdTypeOperation = 0x89,
    SYGPackageDataCmdTypeWriteStart = 0xd0
};

@interface SYGPackageData : NSObject

- (instancetype)initWithData:(NSMutableData *)data;

- (void)handleCmd;

- (BOOL)isValidCmd;

+ (BOOL)isCompletePage:(NSMutableData *)data;

+ (NSData *)getQueryCmd;

+ (NSData *)getOfflineDataLengthCmdWithIsStartGet:(BOOL)isStartGet;

+ (NSData *)getLocalTime:(long)setTime;

+ (NSData *)batterySendCmdWithSeconds:(int)seconds;

+ (NSData *)batteryStatusCmd;

+ (NSData *)localTimeCmd:(long)time;

+ (NSData *)blePenInfoCmd;

@end

NS_ASSUME_NONNULL_END
