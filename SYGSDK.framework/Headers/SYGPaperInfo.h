//
//  SYGPaperInfo.h
//  SYGBluetoothTestDemo
//
//  Created by Bruce on 2019/8/21.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SYGNoteBookSpec.h"
NS_ASSUME_NONNULL_BEGIN

@interface SYGPaperInfo : NSObject
@property (nonatomic, copy) NSString *codeGroup;
@property (nonatomic, assign) CGFloat width;
@property (nonatomic, assign) CGFloat height;
/// 页码ID
@property (nonatomic, copy) NSString *paperId;
@property (nonatomic, assign) NSInteger logicalStart;
@property (nonatomic, assign) NSInteger pageIdxBegin;
@property (nonatomic, assign) NSInteger pageIdxEnd;
@property (nonatomic, assign) NSInteger paperNum;
@property (nonatomic, copy) NSString *paperSpecName;
@property (nonatomic, copy) NSString *verifyKey;
@property (nonatomic, assign) NSInteger sort;

@property (nonatomic, copy) NSString *userId;

/// 本地页码信息
@property (nonatomic, strong) SYGNoteBookSpec *noteBookSpec;
@property (nonatomic, copy) NSString *bookCode;

/// 书本ID 本地则为加密后的paperId
@property (nonatomic, copy) NSString *userAppliedPaperId;

/// 根据其中一个页码查询总页数
@property (nonatomic, assign) NSInteger  pageTotal;

@end

NS_ASSUME_NONNULL_END
