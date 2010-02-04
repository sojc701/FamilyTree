//
//  Person.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Person : NSObject {
	NSInteger personID;
	
	NSString *relationshipTitle;
	UIImage *thumbnailImage;
	NSString *firstName;
	NSString *lastName;
	
	NSMutableArray *fathers;
	NSMutableArray *mothers;
	NSMutableArray *siblings;
	NSMutableArray *spouses;
	NSMutableArray *children;
	NSMutableArray *parentArray;
	Person *parent;
}

@property (nonatomic) NSInteger personID;
@property (nonatomic, copy) NSString *relationshipTitle;
@property (nonatomic, retain) UIImage *thumbnailImage;
@property (nonatomic, copy) NSString *firstName;
@property (nonatomic, copy) NSString *lastName;

@property (nonatomic, retain) NSMutableArray *fathers;
@property (nonatomic, retain) NSMutableArray *mothers;
@property (nonatomic, retain) NSMutableArray *siblings;
@property (nonatomic, retain) NSMutableArray *spouses;
@property (nonatomic, retain) NSMutableArray *children;
@property (nonatomic, assign) NSMutableArray *parentArray;
@property (nonatomic, assign) Person *parent;

- (NSString *)compositeName;

@end
