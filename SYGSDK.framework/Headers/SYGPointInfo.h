//
//  SYGPointInfo.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SYGXYInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface SYGPointInfo : NSObject
@property (nonatomic, assign) NSInteger x;
@property (nonatomic, assign) NSInteger y;
@property (nonatomic, assign) NSInteger page;
@property (nonatomic, assign) NSInteger pressureValue;
@property (nonatomic, assign) SYGDotStatus dotStatus;
@property (nonatomic, assign) long time;
- (instancetype)initWithX:(NSInteger)x y:(NSInteger)y page:(NSInteger)page pressureValue:(NSInteger)pressureValue time:(long)time dotStatus:(SYGDotStatus)dotStatus;
@end

NS_ASSUME_NONNULL_END
