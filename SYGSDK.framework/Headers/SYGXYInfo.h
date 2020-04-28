//
//  SYGXYInfo.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SYGDotStatus) {
    SYGDotStatusDown = 0,  //落笔
    SYGDotStatusMove,      //移动
    SYGDotStatusUp         //抬笔
};

@interface SYGXYInfo : NSObject
@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) CGFloat originalX;
@property (nonatomic, assign) CGFloat originalY;
@property (nonatomic, assign) NSInteger page;
@property (nonatomic, assign) NSInteger originalPage;
@property (nonatomic, assign) SYGDotStatus dotStatus;
@property (nonatomic, assign) NSInteger pressureValue;
@property (nonatomic, assign) long time;
- (instancetype)initWithX:(CGFloat)x y:(CGFloat)y page:(NSInteger)page;
- (instancetype)initWithX:(CGFloat)x y:(CGFloat)y page:(NSInteger)page dotStatus:(SYGDotStatus)dotStatus;
- (instancetype)initWithX:(CGFloat)x y:(CGFloat)y originalX:(CGFloat)originalX originalY:(CGFloat)originalY page:(NSInteger)page originalPage:(NSInteger)originalPage;
@end

NS_ASSUME_NONNULL_END
