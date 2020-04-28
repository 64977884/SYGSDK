//
//  SYGNoteBookSpec.h
//  SYGPen
//
//  Created by Bruce on 2019/1/10.
//  Copyright © 2019 Bruce. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NoteType : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *noteTypeId;
@property (nonatomic, copy) NSString *res;
@property (nonatomic, copy) NSString *bookRes;

@property (nonatomic, copy) NSArray *noteTypeArray;

- (NoteType *)getNoteTypeWithId:(NSString *)noteTypeId;

- (NoteType *)getNoteTypeWithName:(NSString *)name;

@end

@interface SYGNoteBookSpec : NSObject

@property (nonatomic, copy, readonly) NSString *noteBookId;
@property (nonatomic, assign, readonly) NSInteger startPage;
@property (nonatomic, assign, readonly) NSInteger endPage;
@property (nonatomic, assign, readonly) NSInteger paperSpec;
@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, copy) NSArray *supportedNoteArray;
- (SYGNoteBookSpec *)getNoteBookSpecWithLp:(NSInteger)lp paperSpec:(NSInteger)paperSpec;

@end

NS_ASSUME_NONNULL_END
