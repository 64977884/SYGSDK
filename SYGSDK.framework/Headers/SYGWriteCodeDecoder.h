//
//  SYGWriteCodeDecoder.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGWriteCodeSpec.h"
#import "SYGPaperInfo.h"
#import "SYGPaperXYInfo.h"
#import "SYGPointInfo.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString * const SYGPaperExpiredNotification;

@interface SYGWriteCodeDecoder : NSObject

@property (nonatomic, assign) BOOL isHavePaperResource;
@property (nonatomic, assign) BOOL isValidPaperResource;
///码纸数组
@property (nonatomic, copy) NSArray *supportedRectangles;
- (void)configSupportedRectangles:(NSArray<SYGPaperInfo *> *)supportedRectangles;
- (NSArray<SYGWriteCodeSpec *> *)getSpecWithPage:(NSInteger)page;
- (NSArray<SYGPaperInfo *> *)getRectanglesWithPage:(NSInteger)page;
- (SYGPaperXYInfo *)decodeWithPointInfo:(SYGPointInfo *)pointInfo;
- (SYGPaperXYInfo *)localDecoderWithPointInfo:(SYGPointInfo *)pointInfo;

@end

NS_ASSUME_NONNULL_END
