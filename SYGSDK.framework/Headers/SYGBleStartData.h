//
//  SYGBleStartData.h
//  SYGSDK
//
//  Created by Bruce on 2019/4/22.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SYGBleStartData : NSObject
@property (nonatomic, assign) long beginTime;
@property (nonatomic, assign) long beginTimeS;
@property (nonatomic, assign) long beginTimeMS;
@property (nonatomic, assign) long offlineDataLength;
@end

NS_ASSUME_NONNULL_END
