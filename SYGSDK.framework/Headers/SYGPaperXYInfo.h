//
//  SYGPaperXYInfo.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGXYInfo.h"
#import "SYGPaperInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface SYGPaperXYInfo : NSObject
@property (nonatomic, strong) SYGPaperInfo *paperInfo;
@property (nonatomic, strong) SYGXYInfo *xyInfo;
- (instancetype)initWithPaperInfo:(SYGPaperInfo *)paperInfo xyInfo:(SYGXYInfo *)xyInfo;
@end

NS_ASSUME_NONNULL_END
