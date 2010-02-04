//
//  PreviousPerson.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "PreviousPerson.h"


@implementation PreviousPerson

@synthesize personID;
@synthesize generation;
@synthesize side;
@synthesize generalTitle;
@synthesize distance;
//@synthesize displayed;

@synthesize fathers;
@synthesize mothers;
@synthesize brothers;
@synthesize sisters;
@synthesize spouses;
@synthesize sons;
@synthesize daughters;
@synthesize parentArray;

- (id)initWithCoder:(NSCoder *)coder {
	personID = [[coder decodeObjectForKey:@"personID"] intValue];
	generation = [[coder decodeObjectForKey:@"generation"] intValue];
	side = [[coder decodeObjectForKey:@"side"] intValue];
	generalTitle = [[coder decodeObjectForKey:@"generalTitle"] intValue];
	distance = [[coder decodeObjectForKey:@"distance"] intValue];
	
	//displayed = [coder decodeBoolForKey:@"displayed"];
	
	self.fathers = [coder decodeObjectForKey:@"fathers"];
	self.mothers = [coder decodeObjectForKey:@"mothers"];
	self.brothers = [coder decodeObjectForKey:@"brothers"];
	self.sisters = [coder decodeObjectForKey:@"sisters"];
	self.spouses = [coder decodeObjectForKey:@"spouses"];
	self.sons = [coder decodeObjectForKey:@"sons"];
	self.daughters = [coder decodeObjectForKey:@"daughters"];
	
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:[NSNumber numberWithInt:personID] forKey:@"personID"];
	[coder encodeObject:[NSNumber numberWithInt:generation] forKey:@"generation"];
	[coder encodeObject:[NSNumber numberWithInt:side] forKey:@"side"];
	[coder encodeObject:[NSNumber numberWithInt:generalTitle] forKey:@"generalTitle"];
	[coder encodeObject:[NSNumber numberWithInt:distance] forKey:@"distance"];
	
	//[coder encodeBool:displayed forKey:@"displayed"];
	
	[coder encodeObject:fathers forKey:@"fathers"];
	[coder encodeObject:mothers forKey:@"mothers"];
	[coder encodeObject:brothers forKey:@"brothers"];
	[coder encodeObject:sisters forKey:@"sisters"];
	[coder encodeObject:spouses forKey:@"spouses"];
	[coder encodeObject:sons forKey:@"sons"];
	[coder encodeObject:daughters forKey:@"daughters"];
}

- (void)dealloc {
	[fathers release];
	[mothers release];
	[brothers release];
	[sisters release];
	[spouses release];
	[sons release];
	[daughters release];
	[super dealloc];
}


@end
