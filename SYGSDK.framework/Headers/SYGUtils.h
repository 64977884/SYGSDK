//
//  SYGUtils.h
//  SYGWorkHelper
//
//  Created by Bruce on 2019/10/9.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SYGUtils : NSObject

+ (long)convertByteData:(NSData *)data startI:(long)startI endI:(long)endI initData:(long)initData;

+ (NSString *)DESDecrypt:(NSString *)decryptStr;

+ (NSData *)DESDecryptWithKey:(NSString *)keyStr iv:(NSString *)ivStr originData:(NSData *)originData;

+ (NSData *)dataFromHexStringWithOriginData:(NSData *)originData;

+ (NSString *)hexStringWithOriginData:(NSData *)originData;

@end

NS_ASSUME_NONNULL_END
