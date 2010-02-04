//
//  Person.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Person.h"
#import "Constants.h"


@implementation Person

@synthesize personID;
@synthesize relationshipTitle;
@synthesize thumbnailImage;
@synthesize firstName;
@synthesize lastName;
@synthesize fathers;
@synthesize mothers;
@synthesize siblings;
@synthesize spouses;
@synthesize children;
@synthesize parentArray;
@synthesize parent;

- (id)initWithCoder:(NSCoder *)coder {
	//self = [super initWithCoder:coder];
	
	personID = [[coder decodeObjectForKey:@"personID"] integerValue];
	
	self.relationshipTitle = [coder decodeObjectForKey:@"relationshipTitle"];
	self.thumbnailImage = [UIImage imageWithData:[coder decodeObjectForKey:@"thumbnailImage"]];
	self.firstName = [coder decodeObjectForKey:@"firstName"];
	self.lastName = [coder decodeObjectForKey:@"lastName"];
	
	self.fathers = [coder decodeObjectForKey:@"fathers"];
	self.mothers = [coder decodeObjectForKey:@"mothers"];
	self.siblings = [coder decodeObjectForKey:@"siblings"];
	self.spouses = [coder decodeObjectForKey:@"spouses"];
	self.children = [coder decodeObjectForKey:@"children"];
	
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeObject:[NSNumber numberWithInteger:personID] forKey:@"personID"];
	
	[coder encodeObject:relationshipTitle forKey:@"relationshipTitle"];
	[coder encodeObject:UIImagePNGRepresentation(thumbnailImage) forKey:@"thumbnailImage"];
	[coder encodeObject:firstName forKey:@"firstName"];
	[coder encodeObject:lastName forKey:@"lastName"];
	
	[coder encodeObject:fathers forKey:@"fathers"];
	[coder encodeObject:mothers forKey:@"mothers"];
	[coder encodeObject:siblings forKey:@"siblings"];
	[coder encodeObject:spouses forKey:@"spouses"];
	[coder encodeObject:children forKey:@"children"];
}

- (NSString *)compositeName {
	char nameOrder = [[[NSUserDefaults standardUserDefaults] objectForKey:@"nameOrderSelectedRow"] charValue];
	switch (nameOrder) {
		case FIRST_NAME_FIRST:
			return [firstName stringByAppendingFormat:@" %@", lastName];
			break;
		case LAST_NAME_FIRST:
			return [lastName stringByAppendingFormat:@", %@", firstName];
			break;
		case NO_SPACE:
			return [lastName stringByAppendingString:firstName];
			break;
		default:
			return nil;
			break;
	}
	return nil;
}

- (void)dealloc {
	[relationshipTitle release];
	[thumbnailImage release];
	[firstName release];
	[lastName release];
	
	[fathers release];
	[mothers release];
	[siblings release];
	[spouses release];
	[children release];
	[super dealloc];
}

@end
