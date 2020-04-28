//
//  SYGLogger.h
//  SYGWorkHelper
//
//  Created by Bruce on 2019/10/12.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SYGBleManager.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT void SYGLog(NSString *format, ...) NS_FORMAT_FUNCTION(1,2);

@interface SYGLogger : NSObject

@end

NS_ASSUME_NONNULL_END
