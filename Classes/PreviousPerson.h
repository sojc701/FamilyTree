//
//  PreviousPerson.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface PreviousPerson : NSObject {
	int personID;
	int generation; // The number representing the generation compared to me.
	// Grandchildren = -2, children = -1, Me = 0, parents = 1, and etc.
	int side; // Presents me side = 0, father side = 1, mother side = 2, sibling side = 3, spouse side = 4, children side = 5
	int generalTitle;
	int distance; // Distance from Me.
	// Me and my spouse = 1, person and person's spouse have the same distance.
	// For example, dad, mom, siblings, and siblings' spouses = 2
	
	//BOOL displayed;
	
	NSMutableArray *fathers;
	NSMutableArray *mothers;
	NSMutableArray *brothers;
	NSMutableArray *sisters;
	NSMutableArray *spouses;
	NSMutableArray *sons;
	NSMutableArray *daughters;
	NSMutableArray *parentArray;
}

@property int personID;
@property int generation;
@property int side;
@property int generalTitle;
@property int distance;
//@property BOOL displayed;
@property (nonatomic, retain) NSMutableArray *fathers;
@property (nonatomic, retain) NSMutableArray *mothers;
@property (nonatomic, retain) NSMutableArray *brothers;
@property (nonatomic, retain) NSMutableArray *sisters;
@property (nonatomic, retain) NSMutableArray *spouses;
@property (nonatomic, retain) NSMutableArray *sons;
@property (nonatomic, retain) NSMutableArray *daughters;
@property (nonatomic, assign) NSMutableArray *parentArray;

@end
