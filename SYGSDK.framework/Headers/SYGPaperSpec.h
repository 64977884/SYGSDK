//
//  SYGPaperSpec.h
//  SYGPen
//
//  Created by Bruce on 2019/1/10.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGNoteBookSpec.h"
#import <CoreGraphics/CoreGraphics.h>
#import "SYGPaperXYInfo.h"
#import "SYGPointInfo.h"
typedef NS_ENUM(NSUInteger, SYGPaperType) {
    SYGPaperTypeA4 = 1,
    SYGPaperTypeA5 = 2,
    SYGPaperTypeA4T = 3,
    SYGPaperTypeSo = 4
};

NS_ASSUME_NONNULL_BEGIN

@interface LogicPage : NSObject
@property (nonatomic, assign) NSInteger dotType; //0:落笔 1:移动中 2:抬笔结束
@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) NSInteger page;
@property (nonatomic, copy) NSString *logicPageId;
@property (nonatomic, strong) SYGNoteBookSpec *noteBookSpec;
- (instancetype)initWithX:(CGFloat)x Y:(CGFloat)y page:(NSInteger)page logicPageId:(NSString *)logicPageId noteBookSpec:(SYGNoteBookSpec *)noteBookSpec;
@end

@interface PaperDivide : NSObject

@property (nonatomic, assign) CGFloat width;
@property (nonatomic, assign) CGFloat height;
@property (nonatomic, assign) NSInteger rowNum;
@property (nonatomic, assign) NSInteger columnNum;
@property (nonatomic, assign) NSInteger paperType;

@property (nonatomic, assign) NSInteger codeNumX;
@property (nonatomic, assign) NSInteger codeNumY;

- (instancetype)initWithWidth:(CGFloat)width height:(CGFloat)height rowNum:(NSInteger)rowNum columnNum:(NSInteger)columnNum paperType:(NSInteger)paperType;

@end

@interface RealPage : NSObject

@property (nonatomic, assign) NSInteger page;
@property (nonatomic, assign) NSInteger paperType;
@property (nonatomic, assign) NSInteger pageIdx;

- (instancetype)initWithPage:(NSInteger)page paperType:(NSInteger)paperType pageIdx:(NSInteger)pageIdx;

@end

@interface SYGPaperSpec : NSObject
@property (nonatomic, strong, readonly) PaperDivide *paperDivide;
@property (nonatomic, strong) RealPage *realPage;

- (instancetype)initWithRealPage:(NSInteger)page;
- (LogicPage *)toLogicPageWithX:(NSInteger)x Y:(NSInteger)y;
- (SYGPaperXYInfo *)getPaperXYInfoWithPointInfo:(SYGPointInfo *)pointInfo;
@end

NS_ASSUME_NONNULL_END
