//
//  RootViewController.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/2/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "RootViewController.h"

typedef enum {
	TREE_BUTTON,
	EVENTS_BUTTON
} BUTTON;

@implementation RootViewController

@synthesize toolbarItemsArray;
@synthesize toolbarItemsHomeArray;
@synthesize eventsTableViewController;

- (void)loadEventsTableView {
	EventsTableViewController *etvc = [[EventsTableViewController alloc] initWithNibName:@"EventsTableViewController" bundle:nil];
	self.eventsTableViewController = etvc;
	[etvc release];
	
	eventsTableViewController.tableView.center = self.view.center;
	[self.view addSubview:eventsTableViewController.tableView];
}

- (void)tableViewController:(UITableViewController *)tableViewController reloadNames:(BOOL)reloadNames reloadTree:(BOOL)reloadTree {
	[self dismissModalViewControllerAnimated:YES];
	
}

- (void)doneEditingTree {
	if (eventsTableViewController != nil) {
		[eventsTableViewController.tableView removeFromSuperview];
		[eventsTableViewController release];
		eventsTableViewController = nil;
	}
	[self setToolbarItems:toolbarItemsArray animated:YES];
}

- (void)changeToolbarOnEditing:(char)button {
	if (toolbarItemsHomeArray == nil) {
		NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"Home" ofType:@"png"];
		UIImage *image = [[UIImage alloc] initWithContentsOfFile:imagePath];
		UIBarButtonItem *home = [[UIBarButtonItem alloc] initWithImage:image 
																 style:UIBarButtonItemStylePlain 
																target:self 
																action:@selector(doneEditingTree)];
		[image release];
		
		UIBarButtonItem *flexibleSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																					   target:nil 
																					   action:nil];
		if (button == TREE_BUTTON) {
			toolbarItemsHomeArray = [[NSMutableArray alloc] initWithObjects:flexibleSpace, home, flexibleSpace, nil];
		} else if (button == EVENTS_BUTTON) {
			toolbarItemsHomeArray = [[NSMutableArray alloc] initWithObjects:flexibleSpace, home, nil];
		}
		
		[home release];
		[flexibleSpace release];
	} else {
		if (button == TREE_BUTTON) {
			if ([toolbarItemsHomeArray count] == 2) {
				UIBarButtonItem *flexibleSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																							   target:nil 
																							   action:nil];
				[toolbarItemsHomeArray addObject:flexibleSpace];
				[flexibleSpace release];
			}
		} else if (button == EVENTS_BUTTON) {
			if ([toolbarItemsHomeArray count] == 3) {
				[toolbarItemsHomeArray removeLastObject];
			}
		}
	}
	
	[self setToolbarItems:toolbarItemsHomeArray animated:YES];
}

- (void)editTree {
	[self changeToolbarOnEditing:TREE_BUTTON];
}

- (void)showEvents {
	[self changeToolbarOnEditing:EVENTS_BUTTON];
	[self loadEventsTableView];
}

- (void)captureTree {
	
}

- (void)loadFamilyNameGame {
	// Test for MyInfoTableViewController
	Person *person = [[Person alloc] init];
	person.lastName = @"Appleseed";
	person.firstName = @"John";
	
	MyInfoTableViewController *mitvc = [[MyInfoTableViewController alloc] initWithNibName:@"MyInfoTableViewController" bundle:nil];
	mitvc.delegate = self;
	mitvc.person = person;
	
	UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:mitvc];
	[mitvc release];
	nc.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
	[self presentModalViewController:nc animated:YES];
	[nc release];
}

- (void)showSettings {
	SettingsTableViewController *stvc = [[SettingsTableViewController alloc] initWithNibName:@"SettingsTableViewController" bundle:nil];
	stvc.delegate = self;
	UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:stvc];
	[stvc release];
	nc.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	[self presentModalViewController:nc animated:YES];
	[nc release];
}


- (void)viewDidLoad {
    [super viewDidLoad];
	
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
	NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"Settings" ofType:@"png"];
	UIImage *image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	UIBarButtonItem *settings = [[UIBarButtonItem alloc] initWithImage:image 
																 style:UIBarButtonItemStylePlain 
																target:self 
																action:@selector(showSettings)];
	[image release];
	
	imagePath = [[NSBundle mainBundle] pathForResource:@"Game" ofType:@"png"];
	image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	UIBarButtonItem *game = [[UIBarButtonItem alloc] initWithImage:image
																 style:UIBarButtonItemStylePlain 
																target:self 
																action:@selector(loadFamilyNameGame)];
	[image release];
	
	imagePath = [[NSBundle mainBundle] pathForResource:@"TreeToolbarButton" ofType:@"png"];
	image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	UIBarButtonItem *treeButton = [[UIBarButtonItem alloc] initWithImage:image 
																   style:UIBarButtonItemStylePlain 
																  target:self 
																  action:@selector(editTree)];
	[image release];
	
	imagePath = [[NSBundle mainBundle] pathForResource:@"PictureFrame" ofType:@"png"];
	image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	UIBarButtonItem *imageCapture = [[UIBarButtonItem alloc] initWithImage:image 
																 style:UIBarButtonItemStylePlain 
																target:self 
																action:@selector(captureTree)];
	[image release];
	
	imagePath = [[NSBundle mainBundle] pathForResource:@"Cake" ofType:@"png"];
	image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	UIBarButtonItem *events = [[UIBarButtonItem alloc] initWithImage:image 
																 style:UIBarButtonItemStylePlain 
																target:self 
																action:@selector(showEvents)];
	[image release];
	
	UIBarButtonItem *flexibleSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																				   target:nil 
																				   action:nil];
	
	toolbarItemsArray = [[NSArray alloc] initWithObjects:settings, flexibleSpace, game, flexibleSpace, 
						 treeButton, flexibleSpace, imageCapture, flexibleSpace, events, nil];
	[settings release];
	[game release];
	[treeButton release];
	[imageCapture release];
	[events release];
	[flexibleSpace release];
	
	[self setToolbarItems:toolbarItemsArray animated:NO];
}


/*
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
*/
/*
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
*/
/*
- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
}
*/
/*
- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
}
*/

/*
 // Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
 */

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
	self.toolbarItemsHomeArray = nil;
}

- (void)viewDidUnload {
	// Release anything that can be recreated in viewDidLoad or on demand.
	// e.g. self.myOutlet = nil;
	self.toolbarItemsArray = nil;
	[self setToolbarItems:nil animated:NO];
}


- (void)dealloc {
	[toolbarItemsArray release];
	[toolbarItemsHomeArray release];
    [super dealloc];
}


@end

