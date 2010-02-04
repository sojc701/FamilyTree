//
//  FamilyTreeAppDelegate.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/2/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "FamilyTreeAppDelegate.h"
#import "RootViewController.h"


@implementation FamilyTreeAppDelegate

@synthesize window;
@synthesize navigationController;


#pragma mark -
#pragma mark Application lifecycle

- (void)applicationDidFinishLaunching:(UIApplication *)application {    
    
    // Override point for customization after app launch
	navigationController.navigationBarHidden = YES;
	navigationController.toolbarHidden = NO;
	navigationController.toolbar.barStyle = UIBarStyleBlackTranslucent;
	[window addSubview:[navigationController view]];
    [window makeKeyAndVisible];
}


- (void)applicationWillTerminate:(UIApplication *)application {
	// Save data if appropriate
}


#pragma mark -
#pragma mark Memory management

- (void)dealloc {
	[navigationController release];
	[window release];
	[super dealloc];
}


@end

