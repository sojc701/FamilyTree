//
//  RootViewController.h
//  FamilyTree
//
//  Created by Kyungil Kim on 1/2/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "SettingsTableViewController.h"
#import "EventsTableViewController.h"
#import "MyInfoTableViewController.h"
#import "Person.h"

@interface RootViewController : UIViewController 
<SettingsTableViewControllerDelegate, MyInfoTableViewControllerDelegate> {
	NSArray *toolbarItemsArray;
	NSMutableArray *toolbarItemsHomeArray;
	EventsTableViewController *eventsTableViewController;
}

@property (nonatomic, retain) NSArray *toolbarItemsArray;
@property (nonatomic, retain) NSMutableArray *toolbarItemsHomeArray;
@property (nonatomic, retain) EventsTableViewController *eventsTableViewController;

@end
