//
//  SYGBlePenInfo.h
//  SYGWorkHelper
//
//  Created by Bruce on 2019/10/11.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SYGBlePenInfo : NSObject

@property (nonatomic, copy) NSString *deviceSeq;
@property (nonatomic, copy) NSString *appVersion;
@property (nonatomic, copy) NSString *bleVersion;

@end

NS_ASSUME_NONNULL_END
