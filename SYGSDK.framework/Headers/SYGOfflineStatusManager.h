//
//  SYGOfflineStatusManager.h
//  SYGSDK
//
//  Created by Bruce on 2019/4/19.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SYGOfflineStatus) {
    SYGOfflineStatusDefault = 0,        //默认
    SYGOfflineStatusTransitting,        //传输中
    SYGOfflineStatusFinished            //结束
};

@interface SYGOfflineStatusManager : NSObject

+ (instancetype)sharedManager;

@property (nonatomic, assign) NSInteger j;
@property (nonatomic, assign) SYGOfflineStatus offlineStatus;

@end

NS_ASSUME_NONNULL_END
