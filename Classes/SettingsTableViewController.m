//
//  SettingsTableViewController.m
//  FamilyTree
//
//  Created by Kyungil Kim on 1/3/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "SettingsTableViewController.h"
#import "Constants.h"

typedef enum {
	TREE_MODE,
	CALENDAR,
	LAST_NAME_ON,
	NAME_ORDER
} SECTION;

@implementation SettingsTableViewController

@synthesize delegate;
@synthesize treeModeSwitch;
@synthesize hebrewCalendarSwitch;
@synthesize lunarCalendarSwitch;
@synthesize lastNameOnTheTreeSwitch;

/*
- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    if (self = [super initWithStyle:style]) {
    }
    return self;
}
*/

- (void)loadPreviousSettings {
	previousValueOfTreeModeSwitch = [[NSUserDefaults standardUserDefaults] boolForKey:@"treeModeSwitchValue"];
	treeModeSwitch.on = previousValueOfTreeModeSwitch;
	previousValueOfHebrewCalenderSwitch = [[NSUserDefaults standardUserDefaults] boolForKey:@"hebrewCalendarSwitchValue"];
	hebrewCalendarSwitch.on = previousValueOfHebrewCalenderSwitch;
	previousValueOfLunarCalenderSwitch = [[NSUserDefaults standardUserDefaults] boolForKey:@"lunarCalendarSwitchValue"];
	lunarCalendarSwitch.on = previousValueOfLunarCalenderSwitch;
	previousValueOfLastNameOnTheTreeSwitch = [[NSUserDefaults standardUserDefaults] boolForKey:@"lastNameOnTheTreeSwitchValue"];
	lastNameOnTheTreeSwitch.on = previousValueOfLastNameOnTheTreeSwitch;
	previousValueOfNameOrderSelectedRow = [[[NSUserDefaults standardUserDefaults] objectForKey:@"nameOrderSelectedRow"] charValue];
	nameOrderSelectedRow = previousValueOfNameOrderSelectedRow;
}

- (void)returnToTree {
	BOOL reloadNames = NO;
	BOOL reloadTree = NO;
	
	if (previousValueOfTreeModeSwitch != treeModeSwitch.on) {
		[[NSUserDefaults standardUserDefaults] setBool:treeModeSwitch.on forKey:@"treeModeSwitchValue"];
		reloadTree = YES;
	}
	if (previousValueOfHebrewCalenderSwitch != hebrewCalendarSwitch.on) {
		[[NSUserDefaults standardUserDefaults] setBool:hebrewCalendarSwitch.on forKey:@"hebrewCalendarSwitchValue"];
	}
	if (previousValueOfLunarCalenderSwitch != lunarCalendarSwitch.on) {
		[[NSUserDefaults standardUserDefaults] setBool:lunarCalendarSwitch.on forKey:@"lunarCalendarSwitchValue"];
	}
	if (previousValueOfLastNameOnTheTreeSwitch != lastNameOnTheTreeSwitch.on) {
		[[NSUserDefaults standardUserDefaults] setBool:lastNameOnTheTreeSwitch.on forKey:@"lastNameOnTheTreeSwitchValue"];
		reloadNames = YES;
	}
	if (previousValueOfNameOrderSelectedRow != nameOrderSelectedRow) {
		[[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithChar:nameOrderSelectedRow] forKey:@"nameOrderSelectedRow"];
		if (lastNameOnTheTreeSwitch.on) {
			reloadNames = YES;
		}
	}
	
	[self.delegate tableViewController:self reloadNames:reloadNames reloadTree:reloadTree];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
	self.title = NSLocalizedString(@"Settings", nil);
	
	UIButton *treeButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, BUTTON_SIZE, BUTTON_SIZE)];
	[treeButton addTarget:self action:@selector(returnToTree) forControlEvents:UIControlEventTouchUpInside];
	NSString *imagePath = [[NSBundle mainBundle] pathForResource:@"TreeButton" ofType:@"png"];
	UIImage *image = [[UIImage alloc] initWithContentsOfFile:imagePath];
	[treeButton setBackgroundImage:image forState:UIControlStateNormal];
	[image release];
	
	UIBarButtonItem *buttonItem = [[UIBarButtonItem alloc] initWithCustomView:treeButton];
	[treeButton release];
	self.navigationItem.rightBarButtonItem = buttonItem;
	[buttonItem release];
	
	CGRect frame = CGRectMake(198.0, 8.0, 94.0, 27.0);
	treeModeSwitch = [[UISwitch alloc] initWithFrame:frame];
	hebrewCalendarSwitch = [[UISwitch alloc] initWithFrame:frame];
	lunarCalendarSwitch = [[UISwitch alloc] initWithFrame:frame];
	lastNameOnTheTreeSwitch = [[UISwitch alloc] initWithFrame:frame];
	
	[self loadPreviousSettings];
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
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	self.navigationItem.rightBarButtonItem = nil;
	self.treeModeSwitch = nil;
	self.hebrewCalendarSwitch = nil;
	self.lunarCalendarSwitch = nil;
	self.lastNameOnTheTreeSwitch = nil;
}


#pragma mark Table view methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 4;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	switch (section) {
		case TREE_MODE:
			return @"Tree Mode";
			break;
		case CALENDAR:
			return @"Birth & Death Days Conversion";
			break;
		case LAST_NAME_ON:
			return @"Name on the Tree"; 
			break;
		case NAME_ORDER:
			return @"Name Order"; 
			break;
		default:
			break;
	}
	return nil;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    switch (section) {
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 1;
			break;
		case 3:
			return 3;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	static NSString *CellIdentifier;
	UITableViewCell *cell;
	
	if (indexPath.section == NAME_ORDER) {
		CellIdentifier = @"Cell";
		
		cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
		if (cell == nil) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue2 reuseIdentifier:CellIdentifier] autorelease];
		}
		
		switch (indexPath.row) {
			case 0:
				cell.textLabel.text = @"first name";
				cell.detailTextLabel.text = @"John Appleseed";
				break;
			case 1:
				cell.textLabel.text = @"last name";
				cell.detailTextLabel.text = @"Appleseed, John";
				break;
			case 2:
				cell.textLabel.text = @"no space";
				cell.detailTextLabel.text = @"AppleseedJohn";
				break;
			default:
				break;
		}
		
		if (indexPath.row == nameOrderSelectedRow) {
			cell.accessoryType = UITableViewCellAccessoryCheckmark;
		} else {
			cell.accessoryType = UITableViewCellAccessoryNone;
		}
	} else {
		CellIdentifier = @"Switch_Cell";
		
		cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
		if (cell == nil) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
			cell.selectionStyle = UITableViewCellSelectionStyleNone;
		}
		
		UISwitch *switchCtl = nil;
		NSString *imagePath = nil; 
		UIImage *image = nil;
		
		switch (indexPath.section) {
			case TREE_MODE:
				imagePath = [[NSBundle mainBundle] pathForResource:@"Spouse" ofType:@"png"];
				image = [[UIImage alloc] initWithContentsOfFile:imagePath];
				cell.textLabel.text = @"Spouse's family";
				switchCtl = treeModeSwitch;
				break;
			case CALENDAR:
				if (indexPath.row == 0) {
					// Hebrew calendar
					imagePath = [[NSBundle mainBundle] pathForResource:@"Hebrew" ofType:@"png"];
					image = [[UIImage alloc] initWithContentsOfFile:imagePath];
					cell.textLabel.text = @"Hebrew calendar";
					switchCtl = hebrewCalendarSwitch;
				} else {
					// Lunar calendar
					imagePath = [[NSBundle mainBundle] pathForResource:@"Moon" ofType:@"png"];
					image = [[UIImage alloc] initWithContentsOfFile:imagePath];
					cell.textLabel.text = @"Lunar calendar";
					switchCtl = lunarCalendarSwitch;
				}
				break;
			case LAST_NAME_ON:
				imagePath = [[NSBundle mainBundle] pathForResource:@"Seal" ofType:@"png"];
				image = [[UIImage alloc] initWithContentsOfFile:imagePath];
				cell.textLabel.text = @"Last name";
				switchCtl = lastNameOnTheTreeSwitch;
				break;
			default:
				break;
		}
		cell.imageView.image = image;
		[image release];
		[cell.contentView addSubview:switchCtl];
	}
	
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
	
	if (indexPath.section == NAME_ORDER) {
		if (nameOrderSelectedRow == indexPath.row) {
			return;
		} else {
			UITableViewCell *previousCell = [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nameOrderSelectedRow inSection:indexPath.section]];
			previousCell.accessoryType = UITableViewCellAccessoryNone;
			UITableViewCell *newCell = [tableView cellForRowAtIndexPath:indexPath];
			newCell.accessoryType = UITableViewCellAccessoryCheckmark;
			nameOrderSelectedRow = indexPath.row;
		}
	}
    // Navigation logic may go here. Create and push another view controller.
	// AnotherViewController *anotherViewController = [[AnotherViewController alloc] initWithNibName:@"AnotherView" bundle:nil];
	// [self.navigationController pushViewController:anotherViewController];
	// [anotherViewController release];
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:YES];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/


/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/


- (void)dealloc {
	[treeModeSwitch release];
	[hebrewCalendarSwitch release];
	[lunarCalendarSwitch release];
	[lastNameOnTheTreeSwitch release];
    [super dealloc];
}


@end

