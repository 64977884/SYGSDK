//
//  SYGWriteCodeSpec.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface SYGWriteCodeSpec : NSObject
@property (nonatomic, assign) CGFloat width;
@property (nonatomic, assign) CGFloat height;
- (instancetype)initWithWidth:(CGFloat)width height:(CGFloat)height;
- (CGFloat)getDividedWidth;
- (CGFloat)getDividedHeight;
- (CGFloat)countIdxWithX:(CGFloat)x y:(CGFloat)y;
- (double)countNumWithNum:(CGFloat)num;
- (double)getDividedLengthWithNum:(CGFloat)num;
- (double)getCodeNumX;
- (double)getCodeNumY;
- (double)mmtoPxWithDpi:(NSInteger)dpi mm:(CGFloat)mm;
@end

NS_ASSUME_NONNULL_END
